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
#define L_NAV      TD(TD_CAPS)
#define L_SPC      LT(_NUM, KC_SPC)
#define L_PUNCT    LT(_ORTHO, KC_BSPC)

// стрелки
#define A_UP       RSFT_T(KC_UP)
#define A_LEFT     RGUI_T(KC_LEFT)
#define A_DOWN     RCTL_T(KC_DOWN)
#define A_RIGHT    LT(_FN, KC_RGHT)

// яркость (с помощью Twinkle Tray)
#define BR_DOWN    C(S(KC_F1))
#define BR_UP      C(S(KC_F2))

// заглушка KC_NO вместо XXXXXXX
#define X______    KC_NO

// ───────────────────────── Tap Dance ─────────────

enum {
    TD_CAPS = 0
};

// Caps-Lock
void td_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        layer_on(_NAV);          // при удержании - включение слоя _NAV
    } else if (state->count == 1) {
        tap_code16(A(S(KC_NO))); // при нажатии   - смена языка Alt+Shift
    }
}

void td_caps_reset(tap_dance_state_t *state, void *user_data) {
    layer_off(_NAV);              // отключение слоя _NAV при отпускании
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, td_caps_reset)
};

// ───────────────────────── Раскладка ─────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_all(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    KC_MINS,   KC_EQL,   KC_BSPC,
        L_NUM,    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,    KC_LBRC,   KC_RBRC,  KC_BSLS,
        L_NAV,    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN, KC_QUOT,             KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      A_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,            L_SPC,    X______,  KC_MUTE,            L_PUNCT,  KC_LALT,  A_LEFT,             A_DOWN,   A_RIGHT
    ),  //                                      левый     большой   энкодер             правый
        //                                      пробел    пробел                        пробел

    [_NUM] = LAYOUT_all(
        KC_MUTE,  C(KC_1),  C(KC_2),  C(KC_3),  C(KC_4),  C(KC_5),  X______,  KC_PEQL,  KC_PSLS,  KC_PAST,  X______,  X______,  X______,  KC_DEL,
        X______,  A(KC_F4), C(KC_W),  X______,  C(KC_R),  C(KC_T),  X______,  KC_P7,    KC_P8,    KC_P9,    KC_PMNS,  X______,  X______,  X______,
        X______,  C(KC_A),  C(KC_S),  X______,  C(KC_F),  KC_ENT,   KC_ENT,   KC_P4,    KC_P5,    KC_P6,    KC_PPLS,  KC_BSPC,            KC_PENT,
        X______,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  A(KC_1),  S(KC_0),  KC_P1,    KC_P2,    KC_P3,    KC_PDOT,                      X______,
        X______,  X______,  KC_LALT,            X______,  X______,  KC_MUTE,            KC_P0,    X______,  X______,            X______,  X______
    ),

    [_NAV] = LAYOUT_all(
        KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,
        X______,  X______,  KC_LGUI,  KC_F2,    KC_F4,    X______,  X______,  KC_HOME,  KC_UP,    KC_PGUP,  KC_PSCR,  KC_SCRL,  KC_NUM,   KC_PAUS,
        X______,  X______,  KC_LCTL,  KC_LSFT,  KC_LALT,  KC_ENT,   KC_ENT,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,  KC_DEL,   KC_ENT,
        KC_CAPS,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  A(KC_1),  X______,  KC_END,   X______,  KC_PGDN,  X______,                      X______,
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
        KC_ESC,   BR_DOWN,  BR_UP,    X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  A(KC_4),
        X______,  X______,  X______,  EE_CLR,   QK_BOOT,  X______,  X______,  X______,  KC_INS,   X______,  X______,  RGB_BRIZ, RGB_BRIM, RM_TOGG,
        KC_CAPS,  X______,  KC_SCRL,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,  X______,            X______,
        KC_LSFT,  X______,  X______,  KC_CALC,  X______,  QK_RBT,   KC_NUM,   X______,  X______,  KC_MPRV,  KC_MNXT,                      KC_MPLY,
        X______,  X______,  X______,            X______,  X______,  KC_MPLY,            X______,  KC_VOLD,  KC_VOLU,            KC_MUTE,  X______
    )
};

// ───────────────────────── Энкодер ─────────────────────────
#define VOLUME_CONTROL     ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
#define BRIGHT_CONTROL     ENCODER_CCW_CW(BR_DOWN, BR_UP)
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
    #define CYAN(index) rgb_matrix_set_color(index, 0, 0, 255)

    //if (!layer_state_is(0))  { CYAN(57); } // Индикация энкодера для любого зажатого слоя (не базового _WIN)
    if (led_state.caps_lock)   { RED(28);  } // Индикация клавиши Caps Lock (если включен)
    if (!led_state.num_lock)   { RED(47);  } // Индикация клавиши N         (Num Lock, если выключен)
    if (led_state.scroll_lock) { RED(30);  } // Индикация клавиши S         (Scroll Lock, если включен)

    // Индикатор состояния - подсвечивает энкодер, если
    // хоть один из трех индикаторов выше активен
    if ((led_state.caps_lock || !led_state.num_lock || led_state.scroll_lock)) { RED(57); }

    return false;
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(0, 0, 255);
}