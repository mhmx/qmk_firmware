#include QMK_KEYBOARD_H

// ───────────────────────── Слои ─────────────────────────
enum Layers {
    _BASE,   // [0] Базовый слой
    _NUM,    // [1] Numpad слой
    _NAV,    // [2] Слой навигации и управления подсветкой
    _ORTHO   // [3] Орто слой для символов
};

// ──────────────── Короткие названия для действий в layout

// слои
#define L_NUM      LT(_NUM,   KC_TAB)
#define L_NAV      LT(_NAV,   KC_CAPS)
#define L_SPC      LT(_NUM,   KC_SPC)
#define L_PUNCT    LT(_ORTHO, KC_BSPC)

// прочее
#define X______    KC_NO
#define SWITCH     C(A(KC_SPC))


// ───────────────────────── Раскладка ─────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_all(
        KC_ESC,            KC_1,      KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,      KC_8,      KC_9,     KC_0,    KC_MINS,   KC_EQL,   KC_BSLS, KC_DEL,
        L_NUM,             KC_Q,      KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,      KC_I,      KC_O,     KC_P,    KC_LBRC,   KC_RBRC,           KC_BSPC,
        L_NAV,             KC_A,      KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,      KC_K,      KC_L,     KC_SCLN, KC_QUOT,             KC_NUHS, KC_ENT,
        KC_LSFT, KC_LSFT,  KC_Z,      KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,      KC_COMM,   KC_DOT,   KC_SLSH, KC_RSFT,   KC_UP,             KC_DEL,
        KC_LCTL,           KC_LOPT,   KC_LCMD,            L_SPC,    KC_ENT,   L_PUNCT,             KC_ROPT,   MO(_NAV),          KC_LEFT,   KC_DOWN,           KC_RGHT
    ),

    [_NUM] = LAYOUT_all(
        KC_GRV,            G(KC_1),   G(KC_2),  G(KC_3),  G(KC_4),  G(KC_5),  X______,  KC_PEQL,   KC_PSLS,   KC_PAST,  X______, X______,   X______,  KC_GRV,  G(KC_BSPC),
        X______,           G(KC_Q),   G(KC_W),  X______,  G(KC_R),  G(KC_T),  X______,  KC_P7,     KC_P8,     KC_P9,    KC_PMNS, X______,   X______,           X______,
        X______,           G(KC_A),   G(KC_S),  X______,  G(KC_F),  KC_ENT,   KC_ENT,   KC_P4,     KC_P5,     KC_P6,    KC_PPLS, KC_BSPC,             KC_NUHS, KC_PENT,
        X______, X______,  G(KC_Z),   G(KC_X),  G(KC_C),  G(KC_V),  X______,  S(KC_0),  KC_P1,     KC_P2,     KC_P3,    KC_PDOT, KC_MPLY,   KC_VOLU,           KC_MUTE,
        X______,           X______,   KC_LALT,            X______,  X______,  KC_P0,               X______,   X______,           KC_MPRV,   KC_VOLD,           KC_MNXT
    ),

    [_NAV] = LAYOUT_all(
        KC_GRV,            KC_F1,     KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,     KC_F8,     KC_F9,    KC_F10,  KC_F11,    KC_F12,   KC_GRV,  KC_DEL,
        X______,           X______,   KC_LGUI,  KC_F2,    KC_F4,    X______,  X______,  KC_HOME,   KC_UP,     KC_PGUP,  KC_PSCR, KC_SCRL,   KC_NUM,            SWITCH,
        X______,           X______,   KC_LCTL,  KC_LSFT,  KC_LALT,  KC_ENT,   KC_ENT,   KC_LEFT,   KC_DOWN,   KC_RGHT,  KC_BSPC, KC_DEL,              X______, BL_STEP,
        KC_CAPS, X______,  G(KC_Z),   G(KC_X),  G(KC_C),  G(KC_V),  X______,  X______,  KC_END,    X______,   KC_PGDN,  X______, KC_MPLY,   KC_VOLU,           KC_MUTE,
        X______,           X______,   KC_LALT,            X______,  X______,  KC_MUTE,             BL_BRTG,   X______,           KC_MPRV,   KC_VOLD,           KC_MNXT
    ),

    [_ORTHO] = LAYOUT_all(
        QK_BOOT,           KC_BRID,   KC_BRIU,  KC_MCTL,  KC_LPAD,  KC_F5,    KC_F6,    KC_MPRV,   KC_MPLY,   KC_MNXT,  KC_MUTE, KC_VOLD,   KC_VOLU,  KC_GRV,  X______,
        EE_CLR,            X______,   X______,  X______,  X______,  X______,  X______,  S(KC_MINS),S(KC_EQL), KC_MINS,  KC_EQL,  X______,   X______,           X______,
        X______,           S(KC_1),   S(KC_2),  S(KC_3),  S(KC_4),  S(KC_5),  S(KC_6),  S(KC_7),   S(KC_8),   S(KC_9),  S(KC_0), KC_MINS,             KC_NUHS, KC_EQL,
        KC_LSFT, X______,  X______,   X______,  X______,  X______,  X______,  X______,  X______,   X______,   X______,  KC_PDOT, KC_RSFT,   BL_UP,             BL_TOGG,
        X______,           X______,   X______,            KC_ENT,   X______,  KC_MUTE,             X______,   X______,           X______,   BL_DOWN,           X______
    )
};

#include "backlight.h"
#include "timer.h"

#define BACKLIGHT_IDLE_TIMEOUT_MS (15UL * 60 * 1000)

static uint32_t idle_timer      = 0;
static bool     backlight_idled = false;
static uint8_t  saved_level     = 0;

void keyboard_post_init_user(void) {
    idle_timer = timer_read32();
}

void matrix_scan_user(void) {
    if (!backlight_idled && timer_elapsed32(idle_timer) > BACKLIGHT_IDLE_TIMEOUT_MS) {
        saved_level = get_backlight_level();
        if (saved_level > 0) {
            backlight_level_noeeprom(0);
        }
        backlight_idled = true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Выход в бутлодер с QK_BOOT работает только вместе с левым Shift
    if (keycode == QK_BOOT) {
        if (record->event.pressed &&
            (get_mods() & MOD_BIT(KC_LSFT))) {
            reset_keyboard();
        }

        return false;
    }

    if (record->event.pressed) {
        idle_timer = timer_read32();
        if (backlight_idled) {
            backlight_level_noeeprom(saved_level);
            backlight_idled = false;
        }
    }

    return true;
}

