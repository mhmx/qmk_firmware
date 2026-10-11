#pragma once

// 16 MHz crystal (the board default is 8 MHz)
#define STM32_HSECLK 16000000

// VIA/dynamic keymap: reserve EEPROM space for 5 macros only
#define DYNAMIC_KEYMAP_MACRO_COUNT 5
