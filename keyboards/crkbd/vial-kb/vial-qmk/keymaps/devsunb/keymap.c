#include QMK_KEYBOARD_H

enum layers {
    L_BASE,
    L_NAV,
    L_MOUSE,
    L_RGB,
};

enum keycodes {
    CMD_SPC = SAFE_RANGE,
    OS_SFT,
    OS_ALT,
    OS_CTL,
};

#define ESC_CMD MT(MOD_LGUI, KC_ESC)
#define LT_RCMD LT(L_NAV, KC_RCMD)
#define TG_MOU  TG(L_MOUSE)
#define MO_RGB  MO(L_RGB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  MO_RGB,     MO_RGB,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
       OS_CTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, CW_TOGG,    CW_TOGG,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
       OS_SFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                           OS_ALT,  KC_SPC, ESC_CMD,     KC_ENT, LT_RCMD, KC_BSPC
                                      //`--------------------------'  `--------------------------'
  ),

  [L_NAV] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6, _______,    _______,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______, KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX, _______,    _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  TG_MOU,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______, KC_MPRV, KC_MNXT, KC_MPLY, XXXXXXX, XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_BSLS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [L_MOUSE] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, _______,    _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, MS_ACL2, MS_ACL1, MS_ACL0, XXXXXXX, _______,    _______, MS_LEFT, MS_DOWN,   MS_UP, MS_RGHT,  TG_MOU, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, CMD_SPC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    MS_BTN1, MS_BTN2, MS_BTN3
                                      //`--------------------------'  `--------------------------'
  ),

  [L_RGB] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      XXXXXXX, UG_HUED, UG_HUEU, UG_PREV, UG_NEXT, XXXXXXX, _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, UG_SATU, UG_VALU, UG_SPDU, XXXXXXX, UG_TOGG,    UG_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, UG_SATD, UG_VALD, UG_SPDD, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, QK_BOOT,    QK_BOOT, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};

typedef enum {
    os_up_unqueued,
    os_up_queued,
    os_up_used,
    os_down_unused,
    os_down_used,
} oneshot_state;

oneshot_state os_ctl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_sft_state = os_up_unqueued;

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case OS_CTL:
    case OS_ALT:
    case OS_SFT:
    case ESC_CMD:
    case LT_RCMD:
        return true;
    default:
        return false;
    }
}

void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (*state == os_up_unqueued) {
                register_code(mod);
            }
            *state = os_down_unused;
        } else {
            switch (*state) {
            case os_down_unused:
                *state = os_up_queued;
                break;
            case os_down_used:
                *state = os_up_unqueued;
                unregister_code(mod);
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (!is_oneshot_ignored_key(keycode)) {
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    break;
                case os_up_queued:
                    *state = os_up_used;
                    break;
                default:
                    break;
                }
            }
        } else {
            if ((keycode == ESC_CMD && *state != os_up_unqueued) ||
                (!is_oneshot_ignored_key(keycode) && *state == os_up_used)) {
                *state = os_up_unqueued;
                unregister_code(mod);
            }
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_ctl_state, KC_LCTL, OS_CTL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_sft_state, KC_LSFT, OS_SFT,
        keycode, record
    );

    if (keycode == CMD_SPC) {
        if (record->event.pressed) {
            register_code(KC_LCMD);
            register_code(KC_SPC);
        } else {
            unregister_code(KC_SPC);
            unregister_code(KC_LCMD);
            layer_off(L_MOUSE);
        }
    }

    return true;
}
