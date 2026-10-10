// Copyright 2023 linlin012 (@linlin012)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#if defined(RGB_MATRIX_ENABLE)
const is31fl3743a_led_t PROGMEM g_is31fl3743a_leds[IS31FL3743A_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |          G location
 *   |  |          |          B location
 *   |  |          |          | */
    {0, SW1_CS1,   SW1_CS2,   SW1_CS3},   // 0  Esc
    {0, SW2_CS1,   SW2_CS2,   SW2_CS3},   // 1  1
    {0, SW3_CS1,   SW3_CS2,   SW3_CS3},   // 2  2
    {0, SW4_CS1,   SW4_CS2,   SW4_CS3},   // 3  3
    {0, SW5_CS1,   SW5_CS2,   SW5_CS3},   // 4  4
    {0, SW6_CS1,   SW6_CS2,   SW6_CS3},   // 5  5
    {0, SW7_CS1,   SW7_CS2,   SW7_CS3},   // 6  6
    {0, SW8_CS1,   SW8_CS2,   SW8_CS3},   // 7  7
    {0, SW9_CS1,   SW9_CS2,   SW9_CS3},   // 8  8
    {0, SW10_CS1,  SW10_CS2,  SW10_CS3},  // 9  9
    {0, SW11_CS1,  SW11_CS2,  SW11_CS3},  // 10 0
    {0, SW1_CS16,  SW1_CS17,  SW1_CS18},  // 11 -
    {0, SW2_CS16,  SW2_CS17,  SW2_CS18},  // 12 =
    {0, SW3_CS16,  SW3_CS17,  SW3_CS18},  // 13 Backspace

    {0, SW1_CS4,   SW1_CS5,   SW1_CS6},   // 14 Tab
    {0, SW2_CS4,   SW2_CS5,   SW2_CS6},   // 15 Q
    {0, SW3_CS4,   SW3_CS5,   SW3_CS6},   // 16 W
    {0, SW4_CS4,   SW4_CS5,   SW4_CS6},   // 17 E
    {0, SW5_CS4,   SW5_CS5,   SW5_CS6},   // 18 R
    {0, SW6_CS4,   SW6_CS5,   SW6_CS6},   // 19 T
    {0, SW7_CS4,   SW7_CS5,   SW7_CS6},   // 20 Y
    {0, SW8_CS4,   SW8_CS5,   SW8_CS6},   // 21 U
    {0, SW9_CS4,   SW9_CS5,   SW9_CS6},   // 22 I
    {0, SW10_CS4,  SW10_CS5,  SW10_CS6},  // 23 O
    {0, SW11_CS4,  SW11_CS5,  SW11_CS6},  // 24 P
    {0, SW4_CS16,  SW4_CS17,  SW4_CS18},  // 25 [
    {0, SW5_CS16,  SW5_CS17,  SW5_CS18},  // 26 ]
    {0, SW6_CS16,  SW6_CS17,  SW6_CS18},  // 27 Backslash

    {0, SW1_CS7,   SW1_CS8,   SW1_CS9},   // 28 Caps Lock
    {0, SW2_CS7,   SW2_CS8,   SW2_CS9},   // 29 A
    {0, SW3_CS7,   SW3_CS8,   SW3_CS9},   // 30 S
    {0, SW4_CS7,   SW4_CS8,   SW4_CS9},   // 31 D
    {0, SW5_CS7,   SW5_CS8,   SW5_CS9},   // 32 F
    {0, SW6_CS7,   SW6_CS8,   SW6_CS9},   // 33 G
    {0, SW7_CS7,   SW7_CS8,   SW7_CS9},   // 34 H
    {0, SW8_CS7,   SW8_CS8,   SW8_CS9},   // 35 J
    {0, SW9_CS7,   SW9_CS8,   SW9_CS9},   // 36 K
    {0, SW10_CS7,  SW10_CS8,  SW10_CS9},  // 37 L
    {0, SW11_CS7,  SW11_CS8,  SW11_CS9},  // 38 ;
    {0, SW7_CS16,  SW7_CS17,  SW7_CS18},  // 39 '
    {0, SW8_CS16,  SW8_CS17,  SW8_CS18},  // 40 ENTER

    {0, SW1_CS10,  SW1_CS11,  SW1_CS12},  // 41 Left  Shift
    {0, SW2_CS10,  SW2_CS11,  SW2_CS12},  // 42 Z
    {0, SW3_CS10,  SW3_CS11,  SW3_CS12},  // 43 X
    {0, SW4_CS10,  SW4_CS11,  SW4_CS12},  // 44 C
    {0, SW5_CS10,  SW5_CS11,  SW5_CS12},  // 45 V
    {0, SW6_CS10,  SW6_CS11,  SW6_CS12},  // 46 B
    {0, SW7_CS10,  SW7_CS11,  SW7_CS12},  // 47 N
    {0, SW8_CS10,  SW8_CS11,  SW8_CS12},  // 48 M
    {0, SW9_CS10,  SW9_CS11,  SW9_CS12},  // 49 ,
    {0, SW10_CS10, SW10_CS11, SW10_CS12}, // 50 .
    {0, SW11_CS10, SW11_CS11, SW11_CS12}, // 51 /
    {0, SW9_CS16,  SW9_CS17,  SW9_CS18},  // 52 Right Shift

    {0, SW1_CS13,  SW1_CS14,  SW1_CS15},  // 53 Left  Ctrl
    {0, SW2_CS13,  SW2_CS14,  SW2_CS15},  // 54 Left  Win
    {0, SW3_CS13,  SW3_CS14,  SW3_CS15},  // 55 Left  Alt
    {0, SW4_CS13,  SW4_CS14,  SW4_CS15},  // 56 Left  Space
    {0, SW5_CS13,  SW5_CS14,  SW5_CS15},  // 57 Encoder
    {0, SW5_CS13,  SW5_CS14,  SW5_CS15},  // 58 Big   Space
    {0, SW6_CS13,  SW6_CS14,  SW6_CS15},  // 59 Right Space
    {0, SW7_CS13,  SW7_CS14,  SW7_CS15},  // 60 Right Alt
    {0, SW8_CS13,  SW8_CS14,  SW8_CS15},  // 61 App|Menu
    {0, SW9_CS13,  SW9_CS14,  SW9_CS15},  // 62 Right Ctrl
    {0, SW10_CS13, SW10_CS14, SW10_CS15}  // 63 FN
};

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    // Объявил на уровне кеймапа via с другим цветом, поэтому здесь отключено

    //if (host_keyboard_led_state().caps_lock) {
    //    RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_INDEX, 255, 0, 255);
    //    //RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_INDEX, 255, 255, 255);
    //} else {
    //    if (!rgb_matrix_get_flags()) {
    //        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_INDEX, 0, 0, 0);
    //    }
    //}

    // Конец комментария

    return false;
}

void suspend_power_down_kb(void) {
    gpio_write_pin_low(IS31FL3743A_SDB_PIN);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    gpio_write_pin_high(IS31FL3743A_SDB_PIN);
    suspend_wakeup_init_user();
}
#endif

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
}
