#include QMK_KEYBOARD_H

//#include "host.h"
//#include "led.h"
//#include "quantum.h"
//#include "timer.h"

#define LT_1   LT(1, KC_A)
#define LT_2   LT(2, KC_F)
#define LT_3   LT(3, KC_SPC)
#define LT_4   LT(4, KC_BSPC)
#define LT_5   LT(5, KC_MUTE)

// Twinkle Tray brightness shortcuts.
#define BR_DOWN C(S(KC_F1))
#define BR_UP   C(S(KC_F2))
#define X______ KC_NO

enum custom_keycodes {
    M_CTRL = QK_KB_0,
    LESS,
    MORE,
    RU_2,
    EN_2,
    RU_3,
    EN_3,
    RU_4,
    EN_4,
    RU_6,
    EN_6,
    RU_7,
    EN_7,
    Q_LEFT,
    Q_RGHT,
    TIRE,
    INV_SPC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,            KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,  KC_DEL,
        KC_TAB,            KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_BSPC,
        M_CTRL,            LT(1, KC_A), KC_S,  KC_D,     LT(2, KC_F), KC_G,  KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            X______,  KC_ENT,
        KC_LSFT, X______,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,      MT(MOD_LSFT | MOD_RSFT, KC_UP), LT(5, KC_MUTE), KC_PGDN,
        X______,             KC_LGUI,  KC_LALT,            LT(3, KC_SPC), KC_ESC, LT(4, KC_BSPC), KC_RCTL,                KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_END
    ),
    [1] = LAYOUT(
        X______,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_GRV,   A(KC_4),
        X______,             X______,    KC_LGUI,  KC_F2,    KC_F4,    X______,    X______,    KC_HOME,  KC_UP,    KC_PGUP,  X______,    X______,    X______,             KC_PAUS,
        KC_CAPS,           X______,    KC_LCTL,  KC_LSFT,  KC_LALT,  X______,    KC_ENT,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,  KC_DEL,             X______,  KC_ENT,
        KC_LSFT, X______,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  A(KC_1),  X______,    KC_END,   X______,  KC_PGDN,  X______,             KC_PGUP,  X______,    X______,
        X______,             KC_LGUI,  KC_LALT,            KC_HOME,  X______,    KC_END,             X______,                        KC_HOME,  KC_PGDN,  KC_END,   X______
    ),
    [2] = LAYOUT(
        X______,             X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    A(KC_4),
        X______,             X______,    X______,    KC_F2,    KC_F4,    X______,    KC_PSLS,  KC_P7,    KC_P8,    KC_P9,    KC_PMNS,  X______,    X______,             X______,
        KC_LCTL,           X______,    KC_PSLS,  KC_PAST,  X______,    X______,    KC_ENT,   KC_P4,    KC_P5,    KC_P6,    KC_PPLS,  KC_BSPC,            X______,  KC_PENT,
        KC_LSFT, X______,  X______,    X______,    X______,    X______,    X______,    KC_PAST,  KC_P1,    KC_P2,    KC_P3,    KC_PDOT,            X______,    X______,    X______,
        X______,             KC_LGUI,  KC_LALT,            KC_LALT,  X______,    KC_P0,              X______,                        X______,    X______,    X______,    X______
    ),
    [3] = LAYOUT(
        QK_BOOT,           C(KC_1),  C(KC_2),  C(KC_3),  C(KC_4),  C(KC_5),  C(KC_6),  C(KC_7),  C(KC_8),  C(KC_9),  C(KC_0),  BR_DOWN,  BR_UP,    X______,    A(KC_4),
        X______,             A(KC_F4), C(KC_W),  G(KC_E),  C(KC_R),  C(KC_T),  C(KC_Y),  X______,    X______,    X______,    X______,    X______,    X______,             X______,
        KC_LCTL,           C(KC_A),  C(KC_S),  G(KC_D),  C(KC_F),  X______,    KC_ENT,   X______,    X______,    G(KC_L),  X______,    X______,             X______,  X______,
        KC_LSFT, X______,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  A(KC_1),  X______,    X______,    X______,    X______,    X______,             X______,    X______,    X______,
        KC_LCTL,           KC_LGUI,  KC_LALT,            X______,    X______,    X______,              X______,                        X______,    X______,    X______,    X______
    ),
    [4] = LAYOUT(
        KC_GRV,            X______,    X______,      X______,    X______,   X______,   X______,    X______,      X______,     X______,    X______,   TIRE,       X______, KC_GRV, X______,
        X______,             Q_LEFT,   Q_RGHT,     X______,    X______,   X______,   X______,    S(KC_MINS), S(KC_EQL), KC_MINS,  KC_EQL,  S(KC_LBRC), S(KC_RBRC), X______,
        KC_LCTL,           S(KC_1),  RU_2,       RU_3,     RU_4,    S(KC_5), RU_6,     RU_7,       S(KC_8),   S(KC_9),  S(KC_0), KC_MINS,            X______,  X______,
        X______,   X______,  X______,    EN_2,       EN_3,     EN_4,    X______,   EN_6,     EN_7,       LESS,      MORE,     KC_PDOT,            X______, X______, X______,
        X______,             X______,    X______,                INV_SPC, X______,   X______,                X______,                        X______,    X______,    X______,    X______
    ),
    [5] = LAYOUT(
        QK_BOOT,           X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    BR_DOWN,  BR_UP,    X______,    X______,
        QK_CLEAR_EEPROM,   X______,    X______,    X______,    X______,    X______,    X______,    X______,    KC_INS,   X______,    KC_PSCR,  X______,    X______,             X______,
        KC_LCTL,           X______,    KC_SCRL,  X______,    X______,    X______,    X______,    X______,    X______,    G(KC_L),  X______,    X______,             X______,  X______,
        KC_LSFT, X______,  X______,    X______,    KC_CAPS,  X______,    X______,    KC_NUM,   X______,    X______,    X______,    KC_MPLY,            KC_VOLU,  X______,    KC_PGUP,
        X______,           X______,    X______,              X______,    X______,    X______,              G(KC_L),                      KC_MPRV,  KC_VOLD,  KC_MNXT,  KC_HOME
    ),
    [6] = LAYOUT(
        QK_BOOT,           X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    BR_DOWN,  BR_UP,    X______,    X______,
        QK_CLEAR_EEPROM,   X______,    X______,    X______,    X______,    X______,    X______,    X______,    KC_INS,   X______,    KC_PSCR,  X______,    X______,             X______,
        KC_LCTL,           X______,    KC_SCRL,  X______,    X______,    X______,    X______,    X______,    X______,    G(KC_L),  X______,    X______,             X______,  X______,
        KC_LSFT, X______,  X______,    X______,    KC_CAPS,  X______,    X______,    KC_NUM,   X______,    X______,    X______,    KC_MPLY,            KC_VOLU,  X______,    KC_PGUP,
        X______,           X______,    X______,              X______,    X______,    X______,              G(KC_L),                      KC_MPRV,  KC_VOLD,  KC_MNXT,  KC_HOME
    ),
    [7] = LAYOUT(
        QK_BOOT,           X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    X______,    BR_DOWN,  BR_UP,    X______,    X______,
        QK_CLEAR_EEPROM,   X______,    X______,    X______,    X______,    X______,    X______,    X______,    KC_INS,   X______,    KC_PSCR,  X______,    X______,             X______,
        KC_LCTL,           X______,    KC_SCRL,  X______,    X______,    X______,    X______,    X______,    X______,    G(KC_L),  X______,    X______,             X______,  X______,
        KC_LSFT, X______,  X______,    X______,    KC_CAPS,  X______,    X______,    KC_NUM,   X______,    X______,    X______,    KC_MPLY,            KC_VOLU,  X______,    KC_PGUP,
        X______,             X______,    X______,              X______,    X______,    X______,              G(KC_L),                      KC_MPRV,  KC_VOLD,  KC_MNXT,  KC_HOME
    )
};

static void tap_keypad_digit(uint8_t digit) {
    switch (digit) {
        case 0:
            tap_code(KC_P0);
            break;
        case 1:
            tap_code(KC_P1);
            break;
        case 2:
            tap_code(KC_P2);
            break;
        case 3:
            tap_code(KC_P3);
            break;
        case 4:
            tap_code(KC_P4);
            break;
        case 5:
            tap_code(KC_P5);
            break;
        case 6:
            tap_code(KC_P6);
            break;
        case 7:
            tap_code(KC_P7);
            break;
        case 8:
            tap_code(KC_P8);
            break;
        case 9:
            tap_code(KC_P9);
            break;
    }
}

static void send_alt_code(uint16_t code, bool leading_zero) {
    uint8_t digits[3];
    uint8_t digit_count = 0;
    uint8_t weak_mods = get_weak_mods();

    while (code > 0) {
        digits[digit_count++] = code % 10;
        code /= 10;
    }

    add_weak_mods(MOD_BIT(KC_LALT));
    send_keyboard_report();

    if (leading_zero) {
        tap_keypad_digit(0);
    }

    while (digit_count > 0) {
        tap_keypad_digit(digits[--digit_count]);
    }

    set_weak_mods(weak_mods);
    send_keyboard_report();
}

static uint16_t m_ctrl_fast_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= LESS && keycode <= INV_SPC) {
        if (record->event.pressed) {
            switch (keycode) {
                case LESS:
                    send_alt_code(60, false);
                    break;
                case MORE:
                    send_alt_code(62, false);
                    break;
                case RU_2:
                    send_alt_code(34, false);
                    break;
                case EN_2:
                    send_alt_code(64, false);
                    break;
                case RU_3:
                    send_alt_code(252, false);
                    break;
                case EN_3:
                    send_alt_code(35, false);
                    break;
                case RU_4:
                    send_alt_code(59, false);
                    break;
                case EN_4:
                    send_alt_code(36, false);
                    break;
                case RU_6:
                    send_alt_code(58, false);
                    break;
                case EN_6:
                    send_alt_code(94, false);
                    break;
                case RU_7:
                    send_alt_code(63, false);
                    break;
                case EN_7:
                    send_alt_code(38, false);
                    break;
                case Q_LEFT:
                    send_alt_code(171, true);
                    break;
                case Q_RGHT:
                    send_alt_code(187, true);
                    break;
                case TIRE:
                    send_alt_code(151, true);
                    break;
                case INV_SPC:
                    send_alt_code(255, false);
                    break;
            }
        }
        return false;
    }

    if (keycode == M_CTRL) {
        if (record->event.pressed) {
            m_ctrl_fast_timer = timer_read();
            register_code(KC_LCTL);
        } else {
            unregister_code(KC_LCTL);
            if (timer_elapsed(m_ctrl_fast_timer) < TAPPING_TERM) {
                tap_code16(LALT(KC_LSFT));
            }
        }
        return false;
    }

    if (keycode == QK_BOOT) {
        if (record->event.pressed && (get_mods() & MOD_BIT(KC_LSFT))) {
            reset_keyboard();
        }
        return false;
    }

    if (keycode == QK_CLEAR_EEPROM && record->event.pressed && !(get_mods() & MOD_BIT(KC_LSFT))) {
        return false;
    }

    return true;
}

bool is_flow_tap_key(uint16_t keycode) {
    switch (keycode) {
        case LT(3, KC_SPC):
        case LT(4, KC_BSPC):
            return false;
    }
    return true;
}

static uint32_t startup_caps_lock_timer;
static bool startup_caps_lock_active;

void keyboard_post_init_user(void) {
    startup_caps_lock_timer = timer_read32();
    startup_caps_lock_active = true;

    led_t led_state = host_keyboard_led_state();
    led_state.caps_lock = true;
    led_set(led_state.raw);
}

bool led_update_user(led_t led_state) {
    if (startup_caps_lock_active) {
        led_state.caps_lock = true;
    }

    led_update_ports(led_state);
    return false;
}

void housekeeping_task_user(void) {
    if (startup_caps_lock_active && timer_elapsed32(startup_caps_lock_timer) >= 1000) {
        startup_caps_lock_active = false;
        led_set(host_keyboard_led_state().raw);
    }
}
