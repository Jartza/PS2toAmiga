/*
 * PS2 to Amiga keyboard converter for ATTiny85.
 * 
 * Translation table from PS2KeyAdvanced codes to Amiga keycodes.
 * For Amiga keycodes, see https://wiki.amigaos.net/w/images/1/12/LibFig34-2.png
 * PS2 keyboard codes are as comments in table.
 * 
 * (C) 2022 by Jari Tulilahti. Licensed under LGPL, see LICENSE for more info.
 */
#pragma once

// Table to convert from PS2KeyAdvanced to Amiga keycode. 0xFF = Don't send anything
const uint8_t ps2amiga[2][161] PROGMEM =
{
  { // Keymap when Scroll Lock is OFF (default)
    0xFF,    // 0x00
    0xFF,    // 0x01 NUM_L
    0xFF,    // 0x02 SCROLL_L
    0x62,    // 0x03 CAPS_L
    0xFF,    // 0x04 PRTSCR
    0xFF,    // 0x05 PAUSE
    0x60,    // 0x06 L_SHIFT
    0x61,    // 0x07 R_SHIFT
    0x63,    // 0x08 L_CTRL
    0x63,    // 0x09 R_CTRL
    0x64,    // 0x0A L_ALT
    0x65,    // 0x0B R_ALT
    0x66,    // 0x0C L_GUI
    0x67,    // 0x0D R_GUI
    0x67,    // 0x0E MENU
    0xFF,    // 0x0F BREAK
    0xFF,    // 0x10 SYSRQ
    0x5F,    // 0x11 HOME
    0xFF,    // 0x12 END
    0xFF,    // 0x13 PGUP
    0xFF,    // 0x14 PGDN
    0x4F,    // 0x15 L_ARROW
    0x4E,    // 0x16 R_ARROW
    0x4C,    // 0x17 UP_ARROW
    0x4D,    // 0x18 DN_ARROW
    0xFF,    // 0x19 INSERT
    0x46,    // 0x1A DELETE
    0x45,    // 0x1B ESC
    0x41,    // 0x1C BS
    0x42,    // 0x1D TAB
    0x44,    // 0x1E ENTER
    0x40,    // 0x1F SPACE
    0x0F,    // 0x20 KP0
    0x1D,    // 0x21 KP1
    0x1E,    // 0x22 KP2
    0x1F,    // 0x23 KP3
    0x2D,    // 0x24 KP4
    0x2E,    // 0x25 KP5
    0x2F,    // 0x26 KP6
    0x3D,    // 0x27 KP7
    0x3E,    // 0x28 KP8
    0x3F,    // 0x29 KP9
    0x3C,    // 0x2A KP_DOT
    0x43,    // 0x2B KP_ENTER
    0x5E,    // 0x2C KP_PLUS
    0x4A,    // 0x2D KP_MINUS
    0x5D,    // 0x2E KP_TIMES
    0x5C,    // 0x2F KP_DIV
    0x0A,    // 0x30 0
    0x01,    // 0x31 1
    0x02,    // 0x32 2
    0x03,    // 0x33 3
    0x04,    // 0x34 4
    0x05,    // 0x35 5
    0x06,    // 0x36 6
    0x07,    // 0x37 7
    0x08,    // 0x38 8
    0x09,    // 0x39 9
    0x2A,    // 0x3A APOS
    0x38,    // 0x3B COMMA
    0x0B,    // 0x3C MINUS
    0x39,    // 0x3D DOT
    0x3A,    // 0x3E DIV
    0x0C,    // 0x3F KP_EQUAL
    0x00,    // 0x40 SINGLE
    0x20,    // 0x41 A
    0x35,    // 0x42 B
    0x33,    // 0x43 C
    0x22,    // 0x44 D
    0x12,    // 0x45 E
    0x23,    // 0x46 F
    0x24,    // 0x47 G
    0x25,    // 0x48 H
    0x17,    // 0x49 I
    0x26,    // 0x4A J
    0x27,    // 0x4B K
    0x28,    // 0x4C L
    0x37,    // 0x4D M
    0x36,    // 0x4E N
    0x18,    // 0x4F O
    0x19,    // 0x50 P
    0x10,    // 0x51 Q
    0x13,    // 0x52 R
    0x21,    // 0x53 S
    0x14,    // 0x54 T
    0x16,    // 0x55 U
    0x34,    // 0x56 V
    0x11,    // 0x57 W
    0x32,    // 0x58 X
    0x15,    // 0x59 Y
    0x31,    // 0x5A Z
    0x29,    // 0x5B SEMI
    0x0D,    // 0x5C BACK
    0x1A,    // 0x5D OPEN_SQ
    0x1B,    // 0x5E CLOSE_SQ
    0x0C,    // 0x5F EQUAL
    0xFF,    // 0x60 KP_COMMA
    0x50,    // 0x61 F1
    0x51,    // 0x62 F2
    0x52,    // 0x63 F3
    0x53,    // 0x64 F4
    0x54,    // 0x65 F5
    0x55,    // 0x66 F6
    0x56,    // 0x67 F7
    0x57,    // 0x68 F8
    0x58,    // 0x69 F9
    0x59,    // 0x6A F10
    0x66,    // 0x6B F11
    0x67,    // 0x6C F12
    0xFF,    // 0x6D F13
    0xFF,    // 0x6E F14
    0xFF,    // 0x6F F15
    0xFF,    // 0x70 F16
    0xFF,    // 0x71 F17
    0xFF,    // 0x72 F18
    0xFF,    // 0x73 F19
    0xFF,    // 0x74 F20
    0xFF,    // 0x75 F21
    0xFF,    // 0x76 F22
    0xFF,    // 0x77 F23
    0xFF,    // 0x78 F24
    0xFF,    // 0x79 NEXT_TR
    0xFF,    // 0x7A PREV_TR
    0xFF,    // 0x7B STOP
    0xFF,    // 0x7C PLAY
    0xFF,    // 0x7D MUTE
    0xFF,    // 0x7E VOL_UP
    0xFF,    // 0x7F VOL_DN
    0xFF,    // 0x80 MEDIA
    0xFF,    // 0x81 EMAIL
    0xFF,    // 0x82 CALC
    0xFF,    // 0x83 COMPUTER
    0xFF,    // 0x84 WEB_SEARCH
    0xFF,    // 0x85 WEB_HOME
    0xFF,    // 0x86 WEB_BACK
    0xFF,    // 0x87 WEB_FORWARD
    0xFF,    // 0x88 WEB_STOP
    0xFF,    // 0x89 WEB_REFRESH
    0xFF,    // 0x8A WEB_FAVOR
    0x30,    // 0x8B EUROPE2
    0xFF,    // 0x8C POWER
    0xFF,    // 0x8D SLEEP
    0xFF,    // 0x8E
    0xFF,    // 0x8F
    0xFF,    // 0x90 WAKE
    0xFF,    // 0x91 INTL1
    0xFF,    // 0x92 INTL2
    0xFF,    // 0x93 INTL3
    0xFF,    // 0x94 INTL4
    0xFF,    // 0x95 INTL5
    0xFF,    // 0x96 LANG1
    0xFF,    // 0x97 LANG2
    0xFF,    // 0x98 LANG3
    0xFF,    // 0x99 LANG4
    0xFF,    // 0x9A
    0xFF,    // 0x9B
    0xFF,    // 0x9C
    0xFF,    // 0x9D
    0xFF,    // 0x9E
    0xFF,    // 0x9F
    0xFF,    // 0xA0 LANG5
  },
  { // Keymap when Scroll Lock is ON
    0xFF,    // 0x00
    0xFF,    // 0x01 NUM_L
    0xFF,    // 0x02 SCROLL_L
    0x62,    // 0x03 CAPS_L
    0xFF,    // 0x04 PRTSCR
    0xFF,    // 0x05 PAUSE
    0x60,    // 0x06 L_SHIFT
    0x61,    // 0x07 R_SHIFT
    0x63,    // 0x08 L_CTRL
    0x64,    // 0x09 R_CTRL
    0x66,    // 0x0A L_ALT
    0x67,    // 0x0B R_ALT
    0x66,    // 0x0C L_GUI
    0x67,    // 0x0D R_GUI
    0x67,    // 0x0E MENU
    0xFF,    // 0x0F BREAK
    0xFF,    // 0x10 SYSRQ
    0x5F,    // 0x11 HOME
    0xFF,    // 0x12 END
    0xFF,    // 0x13 PGUP 
    0xFF,    // 0x14 PGDN
    0x4F,    // 0x15 L_ARROW
    0x4E,    // 0x16 R_ARROW
    0x4C,    // 0x17 UP_ARROW
    0x4D,    // 0x18 DN_ARROW
    0xFF,    // 0x19 INSERT
    0x46,    // 0x1A DELETE
    0x45,    // 0x1B ESC
    0x41,    // 0x1C BS
    0x42,    // 0x1D TAB
    0x44,    // 0x1E ENTER
    0x40,    // 0x1F SPACE
    0x0F,    // 0x20 KP0
    0x1D,    // 0x21 KP1
    0x1E,    // 0x22 KP2
    0x1F,    // 0x23 KP3
    0x2D,    // 0x24 KP4
    0x2E,    // 0x25 KP5
    0x2F,    // 0x26 KP6
    0x3D,    // 0x27 KP7
    0x3E,    // 0x28 KP8
    0x3F,    // 0x29 KP9
    0x3C,    // 0x2A KP_DOT
    0x43,    // 0x2B KP_ENTER
    0x5E,    // 0x2C KP_PLUS
    0x4A,    // 0x2D KP_MINUS
    0x5D,    // 0x2E KP_TIMES
    0x5C,    // 0x2F KP_DIV
    0x0A,    // 0x30 0
    0x01,    // 0x31 1
    0x02,    // 0x32 2
    0x03,    // 0x33 3
    0x04,    // 0x34 4
    0x05,    // 0x35 5
    0x06,    // 0x36 6
    0x07,    // 0x37 7
    0x08,    // 0x38 8
    0x09,    // 0x39 9
    0x2A,    // 0x3A APOS
    0x38,    // 0x3B COMMA
    0x0B,    // 0x3C MINUS
    0x39,    // 0x3D DOT
    0x3A,    // 0x3E DIV
    0x0C,    // 0x3F KP_EQUAL
    0x00,    // 0x40 SINGLE
    0x20,    // 0x41 A
    0x35,    // 0x42 B
    0x33,    // 0x43 C
    0x22,    // 0x44 D
    0x12,    // 0x45 E
    0x23,    // 0x46 F
    0x24,    // 0x47 G
    0x25,    // 0x48 H
    0x17,    // 0x49 I
    0x26,    // 0x4A J
    0x27,    // 0x4B K
    0x28,    // 0x4C L
    0x37,    // 0x4D M
    0x36,    // 0x4E N
    0x18,    // 0x4F O
    0x19,    // 0x50 P
    0x10,    // 0x51 Q
    0x13,    // 0x52 R
    0x21,    // 0x53 S
    0x14,    // 0x54 T
    0x16,    // 0x55 U
    0x34,    // 0x56 V
    0x11,    // 0x57 W
    0x32,    // 0x58 X
    0x15,    // 0x59 Y
    0x31,    // 0x5A Z
    0x29,    // 0x5B SEMI
    0x0D,    // 0x5C BACK
    0x1A,    // 0x5D OPEN_SQ
    0x1B,    // 0x5E CLOSE_SQ
    0x0C,    // 0x5F EQUAL
    0xFF,    // 0x60 KP_COMMA
    0x50,    // 0x61 F1
    0x51,    // 0x62 F2
    0x52,    // 0x63 F3
    0x53,    // 0x64 F4
    0x54,    // 0x65 F5
    0x55,    // 0x66 F6
    0x56,    // 0x67 F7
    0x57,    // 0x68 F8
    0x58,    // 0x69 F9
    0x59,    // 0x6A F10
    0x46,    // 0x6B F11
    0x5F,    // 0x6C F12
    0xFF,    // 0x6D F13
    0xFF,    // 0x6E F14
    0xFF,    // 0x6F F15
    0xFF,    // 0x70 F16
    0xFF,    // 0x71 F17
    0xFF,    // 0x72 F18
    0xFF,    // 0x73 F19
    0xFF,    // 0x74 F20
    0xFF,    // 0x75 F21
    0xFF,    // 0x76 F22
    0xFF,    // 0x77 F23
    0xFF,    // 0x78 F24
    0xFF,    // 0x79 NEXT_TR
    0xFF,    // 0x7A PREV_TR
    0xFF,    // 0x7B STOP
    0xFF,    // 0x7C PLAY
    0xFF,    // 0x7D MUTE
    0xFF,    // 0x7E VOL_UP
    0xFF,    // 0x7F VOL_DN
    0xFF,    // 0x80 MEDIA
    0xFF,    // 0x81 EMAIL
    0xFF,    // 0x82 CALC
    0xFF,    // 0x83 COMPUTER
    0xFF,    // 0x84 WEB_SEARCH
    0xFF,    // 0x85 WEB_HOME
    0xFF,    // 0x86 WEB_BACK
    0xFF,    // 0x87 WEB_FORWARD
    0xFF,    // 0x88 WEB_STOP
    0xFF,    // 0x89 WEB_REFRESH
    0xFF,    // 0x8A WEB_FAVOR
    0x30,    // 0x8B EUROPE2
    0xFF,    // 0x8C POWER
    0xFF,    // 0x8D SLEEP
    0xFF,    // 0x8E
    0xFF,    // 0x8F
    0xFF,    // 0x90 WAKE
    0xFF,    // 0x91 INTL1
    0xFF,    // 0x92 INTL2
    0xFF,    // 0x93 INTL3
    0xFF,    // 0x94 INTL4
    0xFF,    // 0x95 INTL5
    0xFF,    // 0x96 LANG1
    0xFF,    // 0x97 LANG2
    0xFF,    // 0x98 LANG3
    0xFF,    // 0x99 LANG4
    0xFF,    // 0x9A
    0xFF,    // 0x9B
    0xFF,    // 0x9C
    0xFF,    // 0x9D
    0xFF,    // 0x9E
    0xFF,    // 0x9F
    0xFF,    // 0xA0 LANG5
  }
};
