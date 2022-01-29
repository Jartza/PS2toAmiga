/*
 * PS2 to Amiga keyboard converter for ATTiny85.
 * 
 * Uses PS2KeyAdvanced Arduino library to read the PS2 keyboard, which is why you need to
 * use Arduino to compile this (and install PS2KeyAdvanced via library manager, see
 * https://www.arduino.cc/reference/en/libraries/ps2keyadvanced/)
 * 
 * Use Boards manager to install ATTinyCore (https://github.com/SpenceKonde/ATTinyCore)
 * Settings: 16MHz internal RC osc, enable millis, select chip ATTiny85.
 * 
 * Code itself is a mix of Arduino-style and low-level AVR code, as this was made to be
 * quick'n'dirty solution.
 * 
 * (C) 2022 by Jari Tulilahti / Firebay Refurb.
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 *   USA 
 */

#include "inc/avr_common.h"
#include "inc/convert_table.h"
#include <avr/delay.h>
#include <PS2KeyAdvanced.h>

// PS2 keyboard pins defined as Arduino pins for PS2KeyAdvanced
#define PS2_DATA 0 // ATTiny85 pin 5
#define PS2_CLK  2 // ATTiny85 pin 7

// Other pins defined as plain AVR macros instead of DigitalWrite()
#define AMI_CLK  PB3 // Amiga CLK ATTiny85 pin 2
#define AMI_DATA PB4 // Amiga DATA ATTiny85 pin 3
#define AMICLK_DIR BITP(DDRB, AMI_CLK)
#define AMICLK_OUT BITP(PORTB, AMI_CLK)
#define AMICLK_IN BITP(PINB, AMI_CLK)
#define AMIDATA_DIR BITP(DDRB, AMI_DATA)   
#define AMIDATA_OUT BITP(PORTB, AMI_DATA)
#define AMIDATA_IN BITP(PINB, AMI_DATA)

// Macro to send single bit to Amiga KBD lines
#define SENDBIT() do { \
    _delay_us(20); \
    AMIDATA_DIR = code & 0x80 ? DIR_OUT : DIR_IN; \
    _delay_us(20); \
    AMICLK_DIR = DIR_OUT; \
    _delay_us(18); \
    AMICLK_DIR = DIR_IN; \
    code <<= 1; \
} while(0)

uint16_t c;
uint8_t reset_state = 0;
PS2KeyAdvanced keyboard;

// Wait for ACK from Amiga. Just busy looping long enough...
// The ACK happens when DATA line goes low within 143ms, but
// it also must come up soonafter...
static inline bool amiga_wait_ack()
{
  bool ack = false;

  // Scientifically calculated to be long enough time to wait for ACK (143ms) :D
  for (uint32_t i = 0; i < 288000; i++)
  {
    if (AMIDATA_IN == LEVEL_LOW)
    {
      ack = true;
      break;
    }
  }

  // Exit early if no ACK
  if (!ack) return false;

  // Wait for line to come up again, or give up
  for (uint32_t i = 0; i < 288000; i++)
  {
    if (AMIDATA_IN == LEVEL_HIGH) return true;
  }

  // Timeout
  return false;
}

// Resync with Amiga now
void amiga_resync()
{
  bool ack = false;

  // Repeat syncing until we finally get into sync
  while (!ack)
  {
    // Wait for DATA to rise up
    while (AMIDATA_IN == LEVEL_LOW);    

    // Notify computer we have data coming by pulsing DATA line briefly
    AMIDATA_DIR = DIR_OUT;
    _delay_us(18);
    AMIDATA_DIR = DIR_IN;
    _delay_us(118);
   
    // Just clock single 1 bit to line
    AMIDATA_DIR = DIR_OUT;
    _delay_us(20);
    AMICLK_DIR = DIR_OUT; 
    _delay_us(20);
    AMICLK_DIR = DIR_IN;
    _delay_us(20);
    AMIDATA_DIR = DIR_IN;
    ack = amiga_wait_ack();
  }
}

// Force reset of Amiga
void amiga_reset()
{
  // Pull CLK low
  AMICLK_DIR = DIR_OUT;

  // At least 500ms needed for reset, use 600ms to be sure
  // We can use busyloop delay here as we're resetting
  // the machine anyway, clearing the buffer and resetting
  // also the PS2 keyboard
  _delay_ms(600);

  // Release CLK line
  AMICLK_DIR = DIR_IN;

  // Empty keybpard buffer
  while (keyboard.available())
  {
    uint8_t c = keyboard.read();
  }

  // Simultaneously reset the PS2 keyboard
  keyboard.resetKey();
  amiga_resync();
}

// Send keycode to Amiga KBD pins, return ACK
bool amiga_send_code(uint8_t code, uint8_t pressed)
{
  // Shift Amiga code left and insert pressed status as last bit
  code <<= 1;
  code = code | pressed;

  // Notify computer we have data coming by pulsing DATA line briefly
  AMIDATA_DIR = DIR_OUT;
  _delay_us(20);
  AMIDATA_DIR = DIR_IN;
  _delay_us(100); // Actually 120us but SENDBIT begins with 20us delay

  // Unrolled sending of bits with macro.
  SENDBIT();
  SENDBIT();
  SENDBIT();
  SENDBIT();
  SENDBIT();
  SENDBIT();
  SENDBIT();
  SENDBIT();

  // Finally raise the DATA line
  _delay_us(20);
  AMIDATA_DIR = DIR_IN;

  // Wait for ACK
  bool ack = amiga_wait_ack();
  if (ack) return true;

  // No ACK, need to resync and return false after
  amiga_resync();
  return false;
}

// Initialize everything here
void setup()
{
  // Configure Amiga KBD pins to be inputs by default
  // but set the output status as low. Then we can either
  // float or pull down the pin by switching the data
  // direction register
  AMICLK_DIR = DIR_IN;
  AMICLK_OUT = LEVEL_LOW;
  AMIDATA_DIR = DIR_IN;
  AMIDATA_OUT = LEVEL_LOW;

  // Let us sleep a second as sometimes when plugging the keyboard
  // in, the KDB lines seem to fluctuate a bit
  _delay_ms(1000);
  
  // Wait for Amiga KBD lines to be pulled up
  while(AMIDATA_IN == LEVEL_LOW | AMICLK_IN == LEVEL_LOW);

  // Sync keyboard with Amiga and send
  // power-up stream.
  amiga_resync();
  amiga_send_code(0x7E, 0x01);
  amiga_send_code(0x7F, 0x00);

  // Configure the PS2 library
  keyboard.begin(PS2_DATA, PS2_CLK);
  keyboard.resetKey();
  keyboard.setNoRepeat(1);
}

// Main loop
void loop( )
{
  // Check if we have new keycodes available in buffer
  if (keyboard.available())
  {
    // Read the next keycode from buffer
    c = keyboard.read();

    // Translate keycode to Amiga version
    uint8_t ami_c = ps2amiga[c & 0xFF];
    
    // Send the translated keycode to Amiga KBD lines
    // If code is 0xFF, do nothing. Extract pressed
    // bit from status bit 15.
    uint8_t pressed = c >> 15;

    // Keep the pressed state of CTRL-"Amiga"-"Amiga" (Win- or menu-key = Amiga-key) in memory
    // and perform Amiga reset if all three keys are pressed simultaneously.
    if (ami_c == 0x63) reset_state = (reset_state & 0b110) | pressed;        // CTRL
    if (ami_c == 0x66) reset_state = (reset_state & 0b101) | (pressed << 1); // Left Amiga
    if (ami_c == 0x67) reset_state = (reset_state & 0b011) | (pressed << 2); // Right Amiga

    // Reset Amiga if needed
    if (reset_state == 0x07)
    {
      reset_state = 0;
      amiga_reset();
    }
    else if (ami_c != 0xFF) // Ignore 0xFF, that's non-active key
    {
      // Try sending the key until success
      bool ack = false;
      while (!ack)
      {
        ack = amiga_send_code(ami_c, pressed);          
      }
    }
  }
}
