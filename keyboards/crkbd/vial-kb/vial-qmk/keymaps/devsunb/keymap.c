#include QMK_KEYBOARD_H

#define NAV_ESC LT(2, KC_ESC)
#define NUM_RGU LT(1, KC_RGUI)
#define TG_MOUS TG(3)
#define MO_MOUS MO(3)
#define MO_RGB  MO(4)

enum keycodes {
    SW_NEXT = SAFE_RANGE,
    SW_PREV,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  MO_RGB,    TG_MOUS,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_LBRC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, CW_TOGG,       KC_B,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_BSLS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          NAV_ESC,  KC_SPC, KC_LSFT,     KC_ENT, KC_BSPC, NUM_RGU
                                      //`--------------------------'  `--------------------------'
  ),

  // NUM
  [1] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6, _______,    _______,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX, _______,    XXXXXXX, XXXXXXX, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          MO_MOUS, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  // NAV
  [2] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      SW_NEXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,    _______,  KC_INS, KC_MPRV,   KC_UP, KC_MNXT, KC_VOLU, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      SW_PREV, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX, XXXXXXX,    XXXXXXX, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGDN, KC_HOME, KC_MPLY,  KC_END, KC_MUTE, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  // MOUSE
  [3] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,    _______, XXXXXXX, XXXXXXX,   MS_UP, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX, XXXXXXX,    XXXXXXX, MS_WHLU, MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      MS_WHLD, MS_WHLL, XXXXXXX, MS_WHLR, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    MS_BTN1, MS_BTN2, MS_BTN3
                                      //`--------------------------'  `--------------------------'
  ),

  // RGB
  [4] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      QK_BOOT, UG_HUED, UG_HUEU, UG_PREV, UG_NEXT, XXXXXXX, _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, UG_SATU, UG_VALU, UG_SPDU, XXXXXXX, UG_TOGG,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, UG_SATD, UG_VALD, UG_SPDD, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};

// Combo

// const uint16_t PROGMEM esc_a[] = {NAV_ESC, KC_A, COMBO_END};
// const uint16_t PROGMEM esc_s[] = {NAV_ESC, KC_S, COMBO_END};
// const uint16_t PROGMEM esc_d[] = {NAV_ESC, KC_D, COMBO_END};
// const uint16_t PROGMEM esc_f[] = {NAV_ESC, KC_F, COMBO_END};
//
// combo_t key_combos[] = {
//     COMBO(esc_a, KC_LCTL),
//     COMBO(esc_s, KC_LALT),
//     COMBO(esc_d, KC_LGUI),
//     COMBO(esc_f, KC_LSFT),
// };

bool sw_win_active = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == SW_NEXT || keycode == SW_PREV) {
        if (record->event.pressed) {
            if (!sw_win_active) {
                sw_win_active = true;
                register_code(KC_LGUI);
            }
            if (keycode == SW_PREV) {
                register_code(KC_LSFT);
            }
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
            if (keycode == SW_PREV) {
                unregister_code(KC_LSFT);
            }
        }
    } else if (sw_win_active) {
        unregister_code(KC_LGUI);
        sw_win_active = false;
    }
    return true;
}
