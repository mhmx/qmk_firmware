#include QMK_KEYBOARD_H

// ───────────────────────── Слои ─────────────────────────
enum Layers {
    _BASE,   // [0] Базовый слой
    _NUM,    // [1] Numpad слой
    _NAV,    // [2] Слой навигации и управления подсветкой
    _ORTHO,  // [3] Орто слой для символов
    _FN      // [4] FN слой управления подсветкой и прочим
};

enum custom_keycodes {
    RGB_BRIZ = SAFE_RANGE,
    RGB_BRIM,
};

// ──────────────── Короткие названия для действий в layout

// слои
#define L_NUM      LT(_NUM, KC_TAB)
#define L_NAV      LT(_NAV, KC_CAPS)
#define L_SPC      LT(_NUM, KC_SPC)
#define L_PUNCT    LT(_ORTHO, KC_BSPC)

// стрелки
#define A_UP       RSFT_T(KC_UP)
#define A_LEFT     RALT_T(KC_LEFT)
#define A_DOWN     RCTL_T(KC_DOWN)
#define A_RIGHT    LT(_FN, KC_RGHT)

// заглушка KC_NO вместо XXXXXXX
#define X______    KC_NO

#define PUNTO      S(C(KC_NO))

// ───────────────────────── Раскладка ─────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_all(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    KC_MINS,   KC_EQL,   KC_BSPC,
        L_NUM,    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,    KC_LBRC,   KC_RBRC,  KC_BSLS,
        L_NAV,    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN, KC_QUOT,             KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      A_UP,
        KC_LCTL,  KC_LOPT,  KC_LCMD,            L_SPC,    X______,  KC_MUTE,            L_PUNCT,  KC_RCMD,  A_LEFT,             A_DOWN,   A_RIGHT
    ),  //                                      левый     большой   энкодер             правый
        //                                      пробел    пробел                        пробел

    [_NUM] = LAYOUT_all(
        KC_MUTE,  G(KC_1),  G(KC_2),  G(KC_3),  G(KC_4),  G(KC_5),  X______,  KC_PEQL,  KC_PSLS,  KC_PAST,  X______,  X______,  X______,  KC_DEL,
        X______,  G(KC_Q),  G(KC_W),  X______,  G(KC_R),  G(KC_T),  X______,  KC_P7,    KC_P8,    KC_P9,    KC_PMNS,  X______,  X______,  X______,
        X______,  G(KC_A),  G(KC_S),  X______,  G(KC_F),  KC_ENT,   KC_ENT,   KC_P4,    KC_P5,    KC_P6,    KC_PPLS,  KC_BSPC,            KC_PENT,
        X______,  G(KC_Z),  G(KC_X),  G(KC_C),  G(KC_V),  X______,  S(KC_0),  KC_P1,    KC_P2,    KC_P3,    KC_PDOT,                      X______,
        X______,  X______,  KC_LALT,            X______,  X______,  KC_MUTE,            KC_P0,    X______,  X______,            X______,  X______
    ),

    [_NAV] = LAYOUT_all(
        KC_GRV,   X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,   KC_DEL,
        X______,  X______,  KC_LGUI,  KC_F2,    KC_F4,    X______,  X______,  KC_HOME,  KC_UP,    KC_PGUP,  KC_PSCR,  KC_SCRL,  KC_NUM,    PUNTO,
        X______,  X______,  KC_LCTL,  KC_LSFT,  KC_LALT,  KC_ENT,   KC_ENT,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,  KC_DEL,   KC_ENT,
        KC_CAPS,  G(KC_Z),  G(KC_X),  G(KC_C),  G(KC_V),  X______,  X______,  KC_END,   X______,  KC_PGDN,  X______,                      X______,
        X______,  X______,  KC_LALT,            X______,  X______,  KC_MUTE,            KC_DEL,   X______,  X______,            X______,  X______
    ),

    [_ORTHO] = LAYOUT_all(
        X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  KC_DEL,
        X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,
        X______,  S(KC_1),  S(KC_2),  S(KC_3),  S(KC_4),  S(KC_5),  S(KC_6),  S(KC_7),  S(KC_8),  S(KC_9),  S(KC_0),  KC_MINS,            KC_EQL,
        X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  KC_PDOT,                      X______,
        X______,  X______,  X______,            KC_ENT,   X______,  KC_MUTE,            X______,  X______,  X______,            X______,  X______
    ),

    [_FN] = LAYOUT_all(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  KC_F5,    KC_F6,    KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,
        X______,  X______,  X______,  EE_CLR,   QK_BOOT,  X______,  X______,  X______,  X______,  X______,  X______,  RGB_BRIZ, RGB_BRIM, RM_TOGG,
        KC_CAPS,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,            X______,
        KC_LSFT,  X______,  X______,  X______,  X______,  QK_RBT,   X______,  X______,  X______,  KC_MPRV,  KC_MNXT,                      KC_MPLY,
        X______,  X______,  X______,            X______,  X______,  KC_MPLY,            X______,  KC_VOLD,  KC_VOLU,            KC_MUTE,  X______
    )
};

// ───────────────────────── Энкодер ─────────────────────────
#define VOLUME_CONTROL     ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
#define BRIGHT_CONTROL     ENCODER_CCW_CW(KC_BRID, KC_BRIU)
#define NO_ACTION          ENCODER_CCW_CW(KC_NO, KC_NO)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]  = { VOLUME_CONTROL },
    [_NUM]   = { VOLUME_CONTROL },
    [_NAV]   = { BRIGHT_CONTROL },
    [_ORTHO] = { VOLUME_CONTROL },
    [_FN]    = { NO_ACTION },
};

// ───────────────────────── Кастомные действия ─────────────────────────
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

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

    return true;
}

// ───────────────────────── RGB индикация ─────────────────────────
bool rgb_matrix_indicators_user(void) {

    led_t led_state = host_keyboard_led_state(); // получаем статус LED по USB от ПК

    // Названия цветов
    #define RED(index)  rgb_matrix_set_color(index, 255, 0, 0)
    
    // Индикация клавиши Caps Lock (если включен) - на энкодере
    if (led_state.caps_lock) { RED(57); } 

    return false;
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(0, 0, 255);
}