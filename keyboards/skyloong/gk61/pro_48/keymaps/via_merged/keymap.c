#include QMK_KEYBOARD_H

// ───────────────────────── Слои ─────────────────────────
// Два полных набора слоёв — Windows и Mac. Активный default-layer
// определяет, какой набор используется; переключается кейкодами OS_WIN/OS_MAC
// (клавиши G/H на _FN) и хранится персистентно в EEPROM.
enum Layers {
    _BASE_WIN, _NUM_WIN, _NAV_WIN, _ORTHO_WIN, _FN_WIN,
    _BASE_MAC, _NUM_MAC, _NAV_MAC, _ORTHO_MAC, _FN_MAC,
};

enum custom_keycodes {
    RGB_BRIZ = SAFE_RANGE,
    RGB_BRIM,
    HOLD_CYCLE,  // переключить режим tap-hold для L_SPC/L_PUNCT
    TT_DEC,      // уменьшить TAPPING_TERM (для L_SPC/L_PUNCT) на 5мс
    TT_INC,      // увеличить TAPPING_TERM (для L_SPC/L_PUNCT) на 5мс
    OS_WIN,      // переключиться в Windows-профиль (клавиша G на _FN)
    OS_MAC,      // переключиться в Mac-профиль     (клавиша H на _FN)
};

// ──────────────── Короткие названия для действий в layout ────────────────

// слои — Windows
#define L_NUM_W    LT(_NUM_WIN, KC_TAB)
#define L_NAV_W    TD(TD_CAPS)
#define L_SPC_W    LT(_NUM_WIN, KC_SPC)
#define L_PUNCT_W  LT(_ORTHO_WIN, KC_BSPC)
#define A_LEFT_W   RGUI_T(KC_LEFT)
#define A_RIGHT_W  LT(_FN_WIN, KC_RGHT)

// слои — Mac
#define L_NUM_M    LT(_NUM_MAC, KC_TAB)
#define L_NAV_M    LT(_NAV_MAC, KC_CAPS)
#define L_SPC_M    LT(_NUM_MAC, KC_SPC)
#define L_PUNCT_M  LT(_ORTHO_MAC, KC_BSPC)
#define A_LEFT_M   RALT_T(KC_LEFT)
#define A_RIGHT_M  LT(_FN_MAC, KC_RGHT)

// общие для обеих раскладок
#define A_UP       RSFT_T(KC_UP)
#define A_DOWN     RCTL_T(KC_DOWN)

// яркость на Windows (через Twinkle Tray)
#define BR_DOWN    C(S(KC_F1))
#define BR_UP      C(S(KC_F2))

// прочее
#define X______    KC_NO
#define PUNTO      S(C(KC_NO))

// ───────────────────────── OS mode helper ─────────────────────────
static inline bool is_mac_mode(void) {
    return IS_LAYER_ON_STATE(default_layer_state, _BASE_MAC);
}

// ───────────────────────── Tap Dance (Windows Caps) ─────────────────────────
enum { TD_CAPS = 0 };

void td_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        layer_on(is_mac_mode() ? _NAV_MAC : _NAV_WIN);
    } else if (state->count == 1) {
        if (is_mac_mode()) {
            tap_code(KC_CAPS);
        } else {
            tap_code16(A(S(KC_NO)));  // Alt+Shift — смена языка
        }
    }
}

void td_caps_reset(tap_dance_state_t *state, void *user_data) {
    layer_off(_NAV_WIN);
    layer_off(_NAV_MAC);
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, td_caps_reset)
};

// ───────────────────────── Tap-hold режим для L_SPC / L_PUNCT ─────────────
// Переключается кейкодом HOLD_CYCLE, живёт только в RAM (сбрасывается на
// HOLD_MODE_DEFAULT при перезагрузке платы).
enum {
    HOLD_MODE_DEFAULT,     // ждать TAPPING_TERM целиком
    HOLD_MODE_PERMISSIVE,  // hold, если другая клавиша нажата И отпущена раньше таймаута
    HOLD_MODE_HOKP,        // hold сразу по нажатию другой клавиши
};

static uint8_t hold_mode = HOLD_MODE_DEFAULT;
static uint16_t hold_mode_indicator_timer = 0;
#define HOLD_MODE_INDICATOR_MS 2000

static bool is_space_layer_key(uint16_t keycode) {
    return keycode == L_SPC_W || keycode == L_PUNCT_W ||
           keycode == L_SPC_M || keycode == L_PUNCT_M;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    if (is_space_layer_key(keycode)) {
        return hold_mode == HOLD_MODE_PERMISSIVE;
    }
    return true; // поведение по умолчанию для остальных tap-hold клавиш
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    if (is_space_layer_key(keycode)) {
        return hold_mode == HOLD_MODE_HOKP;
    }
    return false;
}

// ───────────────────────── Runtime-регулировка TAPPING_TERM ────────────
// Действует только на L_SPC / L_PUNCT (в обоих профилях, Win и Mac).
static int16_t tapping_term_offset = 0;
#define TAPPING_TERM_MIN 20

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    if (is_space_layer_key(keycode)) {
        return (uint16_t)(TAPPING_TERM + tapping_term_offset);
    }
    return TAPPING_TERM;
}

// Печатает беззнаковое число как текст (как будто вы его сами напечатали).
static void print_uint16(uint16_t n) {
    char buf[6];
    uint8_t i = sizeof(buf) - 1;
    buf[i] = '\0';
    if (n == 0) {
        buf[--i] = '0';
    } else {
        while (n > 0) {
            buf[--i] = (char)('0' + (n % 10));
            n /= 10;
        }
    }
    send_string(&buf[i]);
}

// ───────────────────────── Индикация OS-режима ─────────────────────────
// LED-индексы клавиш G (33) и H (34) — те же клавиши, что переключают OS.
#define OS_LED_WIN 33
#define OS_LED_MAC 34
#define OS_MODE_INDICATOR_MS 2000
static uint16_t os_indicator_timer = 0;

// ───────────────────────── Раскладка ─────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ═══════════════════════ WINDOWS ═══════════════════════
    [_BASE_WIN] = LAYOUT_all(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    KC_MINS,   KC_EQL,   KC_BSPC,
        L_NUM_W,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,    KC_LBRC,   KC_RBRC,  KC_BSLS,
        L_NAV_W,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN, KC_QUOT,             KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      A_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,            L_SPC_W,  X______,  KC_MUTE,            L_PUNCT_W,KC_LALT,  A_LEFT_W,           A_DOWN,   A_RIGHT_W
    ),

    [_NUM_WIN] = LAYOUT_all(
        KC_MUTE,  C(KC_1),  C(KC_2),  C(KC_3),  C(KC_4),  C(KC_5),  X______,  KC_PEQL,  KC_PSLS,  KC_PAST,  X______,  X______,  X______,  KC_DEL,
        X______,  A(KC_F4), C(KC_W),  X______,  C(KC_R),  C(KC_T),  X______,  KC_P7,    KC_P8,    KC_P9,    KC_PMNS,  X______,  X______,  X______,
        X______,  C(KC_A),  C(KC_S),  X______,  C(KC_F),  KC_ENT,   KC_ENT,   KC_P4,    KC_P5,    KC_P6,    KC_PPLS,  KC_BSPC,            KC_PENT,
        X______,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  A(KC_1),  S(KC_0),  KC_P1,    KC_P2,    KC_P3,    KC_PDOT,                      X______,
        X______,  X______,  KC_LALT,            X______,  X______,  KC_MUTE,            KC_P0,    X______,  X______,            X______,  X______
    ),

    [_NAV_WIN] = LAYOUT_all(
        KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,
        X______,  X______,  KC_LGUI,  KC_F2,    KC_F4,    X______,  X______,  KC_HOME,  KC_UP,    KC_PGUP,  KC_PSCR,  KC_SCRL,  KC_NUM,   KC_PAUS,
        X______,  X______,  KC_LCTL,  KC_LSFT,  KC_LALT,  KC_ENT,   KC_ENT,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,  KC_DEL,   KC_ENT,
        KC_CAPS,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  A(KC_1),  X______,  KC_END,   X______,  KC_PGDN,  X______,                      X______,
        X______,  X______,  KC_LALT,            X______,  X______,  KC_MUTE,            KC_DEL,   X______,  X______,            X______,  X______
    ),

    [_ORTHO_WIN] = LAYOUT_all(
        X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  KC_DEL,
        X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,
        X______,  S(KC_1),  S(KC_2),  S(KC_3),  S(KC_4),  S(KC_5),  S(KC_6),  S(KC_7),  S(KC_8),  S(KC_9),  S(KC_0),  KC_MINS,            KC_EQL,
        X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  KC_PDOT,                      X______,
        X______,  X______,  X______,            KC_ENT,   X______,  KC_MUTE,            X______,  X______,  X______,            X______,  X______
    ),

    [_FN_WIN] = LAYOUT_all(
        KC_ESC,   BR_DOWN,  BR_UP,    X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  A(KC_4),
        X______,  TT_DEC,   TT_INC,   EE_CLR,   QK_BOOT,  X______,  X______,  X______,  KC_INS,   X______,  X______,  RGB_BRIZ, RGB_BRIM, RM_TOGG,
        KC_CAPS,  X______,  KC_SCRL,  X______,  X______,  OS_WIN,   OS_MAC,   X______,  X______,  X______,  X______,  X______,            HOLD_CYCLE,
        KC_LSFT,  X______,  X______,  KC_CALC,  X______,  QK_RBT,   KC_NUM,   X______,  X______,  KC_MPRV,  KC_MNXT,                      KC_MPLY,
        X______,  X______,  X______,            X______,  X______,  KC_MPLY,            X______,  KC_VOLD,  KC_VOLU,            KC_MUTE,  X______
    ),

    // ═══════════════════════ MAC ═══════════════════════
    [_BASE_MAC] = LAYOUT_all(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    KC_MINS,   KC_EQL,   KC_BSPC,
        L_NUM_M,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,    KC_LBRC,   KC_RBRC,  KC_BSLS,
        L_NAV_M,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN, KC_QUOT,             KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      A_UP,
        KC_LCTL,  KC_LOPT,  KC_LCMD,            L_SPC_M,  X______,  KC_MUTE,            L_PUNCT_M,KC_RCMD,  A_LEFT_M,           A_DOWN,   A_RIGHT_M
    ),

    [_NUM_MAC] = LAYOUT_all(
        KC_MUTE,  G(KC_1),  G(KC_2),  G(KC_3),  G(KC_4),  G(KC_5),  X______,  KC_PEQL,  KC_PSLS,  KC_PAST,  X______,  X______,  X______,  KC_DEL,
        X______,  G(KC_Q),  G(KC_W),  X______,  G(KC_R),  G(KC_T),  X______,  KC_P7,    KC_P8,    KC_P9,    KC_PMNS,  X______,  X______,  X______,
        X______,  G(KC_A),  G(KC_S),  X______,  G(KC_F),  KC_ENT,   KC_ENT,   KC_P4,    KC_P5,    KC_P6,    KC_PPLS,  KC_BSPC,            KC_PENT,
        X______,  G(KC_Z),  G(KC_X),  G(KC_C),  G(KC_V),  X______,  S(KC_0),  KC_P1,    KC_P2,    KC_P3,    KC_PDOT,                      X______,
        X______,  X______,  KC_LALT,            X______,  X______,  KC_MUTE,            KC_P0,    X______,  X______,            X______,  X______
    ),

    [_NAV_MAC] = LAYOUT_all(
        KC_GRV,   X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,   KC_DEL,
        X______,  X______,  KC_LGUI,  KC_F2,    KC_F4,    X______,  X______,  KC_HOME,  KC_UP,    KC_PGUP,  KC_PSCR,  KC_SCRL,  KC_NUM,    PUNTO,
        X______,  X______,  KC_LCTL,  KC_LSFT,  KC_LALT,  KC_ENT,   KC_ENT,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,  KC_DEL,   KC_ENT,
        KC_CAPS,  G(KC_Z),  G(KC_X),  G(KC_C),  G(KC_V),  X______,  X______,  KC_END,   X______,  KC_PGDN,  X______,                      X______,
        X______,  X______,  KC_LALT,            X______,  X______,  KC_MUTE,            KC_DEL,   X______,  X______,            X______,  X______
    ),

    [_ORTHO_MAC] = LAYOUT_all(
        X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  KC_DEL,
        X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,
        X______,  S(KC_1),  S(KC_2),  S(KC_3),  S(KC_4),  S(KC_5),  S(KC_6),  S(KC_7),  S(KC_8),  S(KC_9),  S(KC_0),  KC_MINS,            KC_EQL,
        X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  KC_PDOT,                      X______,
        X______,  X______,  X______,            KC_ENT,   X______,  KC_MUTE,            X______,  X______,  X______,            X______,  X______
    ),

    [_FN_MAC] = LAYOUT_all(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  KC_F5,    KC_F6,    KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,
        X______,  TT_DEC,   TT_INC,   EE_CLR,   QK_BOOT,  X______,  X______,  X______,  X______,  X______,  X______,  RGB_BRIZ, RGB_BRIM, RM_TOGG,
        KC_CAPS,  X______,  X______,  X______,  X______,  OS_WIN,   OS_MAC,   X______,  X______,  X______,  X______,  X______,            HOLD_CYCLE,
        KC_LSFT,  X______,  X______,  X______,  X______,  QK_RBT,   X______,  X______,  X______,  KC_MPRV,  KC_MNXT,                      KC_MPLY,
        X______,  X______,  X______,            X______,  X______,  KC_MPLY,            X______,  KC_VOLD,  KC_VOLU,            KC_MUTE,  X______
    )
};

// ───────────────────────── Энкодер ─────────────────────────
#define VOLUME_CONTROL     ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
#define BRIGHT_CONTROL_WIN ENCODER_CCW_CW(BR_DOWN, BR_UP)
#define BRIGHT_CONTROL_MAC ENCODER_CCW_CW(KC_BRID, KC_BRIU)
#define NO_ACTION          ENCODER_CCW_CW(KC_NO, KC_NO)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE_WIN]  = { VOLUME_CONTROL },
    [_NUM_WIN]   = { VOLUME_CONTROL },
    [_NAV_WIN]   = { BRIGHT_CONTROL_WIN },
    [_ORTHO_WIN] = { VOLUME_CONTROL },
    [_FN_WIN]    = { NO_ACTION },

    [_BASE_MAC]  = { VOLUME_CONTROL },
    [_NUM_MAC]   = { VOLUME_CONTROL },
    [_NAV_MAC]   = { BRIGHT_CONTROL_MAC },
    [_ORTHO_MAC] = { VOLUME_CONTROL },
    [_FN_MAC]    = { NO_ACTION },
};

// ───────────────────────── Кастомные действия ─────────────────────────
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (keycode == OS_WIN || keycode == OS_MAC) {
        if (record->event.pressed) {
            if (keycode == OS_WIN) {
                set_single_persistent_default_layer(_BASE_WIN);
            } else {
                set_single_persistent_default_layer(_BASE_MAC);
            }
            os_indicator_timer = timer_read();
        }
        return false;
    }

    // Выход в бутлодер с QK_BOOT работает только вместе с левым Shift
    if (keycode == QK_BOOT) {
        if (record->event.pressed &&
            (get_mods() & MOD_BIT(KC_LSFT))) {
            reset_keyboard();
        }
        return false;
    }

    if (keycode == RGB_BRIZ) {
        if (record->event.pressed) {
            rgb_matrix_sethsv(0, 0, 0);
        }
        return false;
    }

    if (keycode == RGB_BRIM) {
        if (record->event.pressed) {
            rgb_matrix_sethsv(0, 0, 255);
        }
        return false;
    }

    if (keycode == HOLD_CYCLE) {
        if (record->event.pressed) {
            hold_mode = (hold_mode + 1) % 3;
            hold_mode_indicator_timer = timer_read();
        }
        return false;
    }

    if (keycode == TT_DEC || keycode == TT_INC) {
        if (record->event.pressed) {
            int16_t delta = (keycode == TT_INC) ? 5 : -5;
            int32_t new_term = (int32_t)TAPPING_TERM + tapping_term_offset + delta;

            if (new_term < TAPPING_TERM_MIN) {
                new_term = TAPPING_TERM_MIN;
            }

            tapping_term_offset = (int16_t)(new_term - TAPPING_TERM);
            print_uint16((uint16_t)new_term);
        }
        return false;
    }

    return true;
}

// ───────────────────────── RGB индикация ─────────────────────────
bool rgb_matrix_indicators_user(void) {

    led_t led_state = host_keyboard_led_state();

    #define RED(index)  rgb_matrix_set_color(index, 255, 0, 255)
    #define BLUE(index) rgb_matrix_set_color(index, 0, 0, 255)

    if (led_state.caps_lock)   { RED(28);  }
    if (!led_state.num_lock)   { RED(47);  }
    if (led_state.scroll_lock) { RED(30);  }
    if ((led_state.caps_lock || !led_state.num_lock || led_state.scroll_lock)) { RED(57); }

    // Временная индикация текущего hold-режима после переключения HOLD_CYCLE
    if (hold_mode_indicator_timer != 0 &&
        timer_elapsed(hold_mode_indicator_timer) < HOLD_MODE_INDICATOR_MS) {
        switch (hold_mode) {
            case HOLD_MODE_DEFAULT:    BLUE(42); break;
            case HOLD_MODE_PERMISSIVE: BLUE(43); break;
            case HOLD_MODE_HOKP:       BLUE(44); break;
        }
    }

    // Временная индикация текущего OS-режима (при старте платы и при переключении)
    // Красным на клавише G (33), если активен Windows, или на H (34), если Mac.
    if (os_indicator_timer != 0 &&
        timer_elapsed(os_indicator_timer) < OS_MODE_INDICATOR_MS) {
        if (is_mac_mode()) {
            rgb_matrix_set_color(OS_LED_MAC, 255, 0, 0);
        } else {
            rgb_matrix_set_color(OS_LED_WIN, 255, 0, 0);
        }
    }

    return false;
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(0, 0, 255);

    // Диагностика: показать текущий hold_mode и OS-режим сразу после старта платы.
    hold_mode_indicator_timer = timer_read();
    os_indicator_timer = timer_read();
}
