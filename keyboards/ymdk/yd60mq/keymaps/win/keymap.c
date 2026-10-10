#include QMK_KEYBOARD_H

// ──────────────── Слои
enum Layers {
    _BASE,   // [0] Базовый слой
    _NAV,    // [1] Слой навигации и управления подсветкой
    _NUM,    // [2] Numpad слой
    _FN,     // [3] Функциональный слой
    _PUNCT   // [4] Знаки пунктуации
};

// ──────────────── Сокращения

// слои
#define L_A         LT(_NAV,   KC_A)
#define L_F         LT(_NUM,   KC_F)
#define L_SPC       LT(_FN,    KC_SPC)
#define L_FN        LT(_FN,    KC_MUTE)
#define L_BSPC      LT(_PUNCT, KC_BSPC)

// яркость (с помощью Twinkle Tray)
#define BR_DOWN     C(S(KC_F1))
#define BR_UP       C(S(KC_F2))

enum custom_keycodes { M_CTRL = QK_KB_0 };

// ──────────────── Раскладка
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_all(
        KC_ESC,            KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,  KC_DEL,
        KC_TAB,            KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_BSPC,
        M_CTRL,            L_A,      KC_S,     KC_D,     L_F,      KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            _______,  KC_ENT,
        KC_LSFT, _______,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,      RSFT_T(KC_UP),  L_FN,     KC_PGDN,
        KC_LCTL,           KC_LGUI,  KC_LALT,            L_SPC,    KC_APP,   L_BSPC,             KC_RCTL,                      KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_END
    ),

    [_NAV] = LAYOUT_all(
        KC_GRV,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_GRV,   A(KC_4),
        _______,           _______,  KC_LGUI,  KC_F2,    KC_F4,    _______,  _______,  KC_HOME,  KC_UP,    KC_PGUP,  KC_PSCR,  KC_SCRL,  KC_NUM,             KC_PAUS,
        KC_CAPS,           _______,  KC_LCTL,  KC_LSFT,  KC_LALT,  _______,  KC_ENT,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,  KC_DEL,             _______,  KC_ENT,
        KC_LSFT, _______,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  A(KC_1),  _______,  KC_END,   _______,  KC_PGDN,  _______,            KC_PGUP,  _______,  _______,
        KC_LCTL,           KC_LGUI,  KC_LALT,            KC_ESC,   _______,  _______,            _______,                      KC_HOME,  KC_PGDN,  KC_END,   _______
    ),

    [_NUM] = LAYOUT_all(
        KC_GRV,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  A(KC_4),
        _______,           _______,  G(KC_L),  KC_F2,    KC_F4,    _______,  KC_PSLS,  KC_P7,    KC_P8,    KC_P9,    KC_PMNS,  _______,  _______,            _______,
        KC_CAPS,           _______,  KC_PSLS,  KC_PAST,  _______,  _______,  KC_ENT,   KC_P4,    KC_P5,    KC_P6,    KC_PPLS,  KC_BSPC,            _______,  KC_PENT,
        KC_LSFT, _______,  _______,  _______,  _______,  _______,  _______,  KC_PAST,  KC_P1,    KC_P2,    KC_P3,    KC_PDOT,            _______,  _______,  _______,
        KC_LCTL,           KC_LGUI,  KC_LALT,            KC_LALT,  _______,  KC_P0,              _______,                      _______,  _______,  _______,  _______
    ),

    [_FN] = LAYOUT_all(
        QK_BOOT,           C(KC_1),  C(KC_2),  C(KC_3),  C(KC_4),  C(KC_5),  C(KC_6),  C(KC_7),  C(KC_8),  C(KC_9),  C(KC_0),  BR_DOWN,  BR_UP,    _______,  A(KC_4),
        _______,           A(KC_F4), C(KC_W),  G(KC_E),  C(KC_R),  C(KC_T),  C(KC_Y),  _______,  KC_INS,   _______,  _______,  _______,  _______,            QK_CLEAR_EEPROM,
        KC_CAPS,           C(KC_A),  C(KC_S),  G(KC_D),  C(KC_F),  _______,  KC_ENT,   _______,  _______,  G(KC_L),  _______,  KC_MPLY,            _______,  _______,
        KC_LSFT, _______,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  A(KC_1),  _______,  _______,  BL_DOWN,  BL_UP,    BL_TOGG,            KC_VOLU,  _______,  KC_PGUP,
        KC_LCTL,           KC_LGUI,  KC_LALT,            _______,  _______,  _______,            _______,                      KC_MPRV,  KC_VOLD,  KC_MNXT,  KC_HOME
    ),

    [_PUNCT] = LAYOUT_all(
        KC_GRV,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_GRV,   A(KC_4),
        _______,           _______,  _______,  _______,  _______,  _______,  _______, S(KC_MINS),S(KC_EQL),KC_MINS,  KC_EQL,  S(KC_LBRC),S(KC_RBRC),         _______,
        KC_CAPS,           S(KC_1),  S(KC_2),  S(KC_3),  S(KC_4),  S(KC_5),  S(KC_6),  S(KC_7),  S(KC_8),  S(KC_9),  S(KC_0),  KC_MINS,            _______,  _______,
        KC_LSFT, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,S(KC_COMM),S(KC_DOT), KC_PDOT,            _______,  _______,  _______,
        KC_LCTL,           KC_LGUI,  KC_LALT,            _______,  _______,  _______,            _______,                      _______,  _______,  _______,  _______
    )

};

// ──────────────── Дополнительные функции
static uint16_t m_ctrl_fast_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Ctrl при удержании, при нажатии - смена языка
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

    // Выход в бутлодер с QK_BOOT работает только вместе с левым Shift
    if (keycode == QK_BOOT) {
        if (record->event.pressed &&
            (get_mods() & MOD_BIT(KC_LSFT))) {
            backlight_set(0);
            reset_keyboard();
        }

        return false;
    }

    return true;
}

bool is_flow_tap_key(uint16_t keycode) {
    // Определяет для каких клавиш Flow Tap НЕ РАБОТАЕТ
    switch (keycode) {
        case LT(_FN, KC_SPC):
        case LT(_PUNCT, KC_BSPC):
            return false;
    }
    // Иначе работает для всех остальных клавиш
    return true;
}
