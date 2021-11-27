#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};
enum {
    TD_F1,
    TD_F2,
    TD_F3,
    TD_F4,
    TD_F5,
    TD_F6,
    TD_F7,
    TD_F8,
    TD_F9,
    TD_F10,
    TD_F11,
    TD_F12,

};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_F1] = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_F1),
    [TD_F2] = ACTION_TAP_DANCE_DOUBLE(KC_2, KC_F2),
    [TD_F3] = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_F3),
    [TD_F4] = ACTION_TAP_DANCE_DOUBLE(KC_4, KC_F4),
    [TD_F5] = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_F5),
    [TD_F6] = ACTION_TAP_DANCE_DOUBLE(KC_6, KC_F6),
    [TD_F7] = ACTION_TAP_DANCE_DOUBLE(KC_7, KC_F7),
    [TD_F8] = ACTION_TAP_DANCE_DOUBLE(KC_8, KC_F8),
    [TD_F9] = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_F9),
    [TD_F10] = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_F10),
    [TD_F11] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_F11),
    [TD_F12] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_F12),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_all(
    KC_MUTE,   KC_DEL,   KC_ESC, TD(TD_F1),    TD(TD_F2),    KC_3,    KC_4,   TD(TD_F5),    KC_6,    KC_7,    KC_8,    TD(TD_F9),    TD(TD_F10),    TD(TD_F11), TD(TD_F12),  KC_DEL,  KC_BSPC, KC_HOME,
    KC_F1,   KC_PSCR,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
    KC_F2,   KC_F10,   KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP,
    KC_F5,   KC_F11,   KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
    KC_F9,   KC_F12,  KC_LCTL, KC_LGUI, KC_LALT, MO(2),   KC_SPC,  KC_SPC,  MO(2),   KC_SPC,  KC_RALT, MO(2), KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [1] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_NO, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [2] = LAYOUT_all(
    _______, _______, KC_ESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL, KC_HOME,
    _______, _______, RGB_TOG, RGB_MOD, _______, KC_UP,   _______, _______, _______, _______, _______, _______, KC_PSCREEN, _______, _______, _______, _______,
    _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_TILD, TG(1), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______

  )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    // SHIFT+ESC키에 '~' 대체
    case KC_ESC:
      // 키보드가 눌렸을 경우
       if (record->event.pressed){
        // 왼쪽 SHIFT키와 오른쪽 SHIFT키가 눌렸는지 확인
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
          if(get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTL)){
            register_code(KC_ESC);
          }
          else{
            register_code(KC_GRV);
          }
          
        } else {
          // ESC만 눌린 경우 ESC키로 정의한다.
          register_code(KC_ESC);
        }
      }
      // 키보드가 눌리지 않았을 경우 등록된 코드를 풀어준다.
       else {
        unregister_code(KC_GRV);
        unregister_code(KC_ESC);

       }
      return false; // 발생한 키 처리를 했으니 false 처리를 하여 중복으로 넘겨주지 않도록 한다.



    // SHIFT+BSPC키에 SHIFT+DEL키 대입
    case KC_BSPC:
      // 키보드가 눌렸을 경우
       if (record->event.pressed){
        // 왼쪽 SHIFT키와 오른쪽 SHIFT키가 눌렸는지 확인
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
         // SHIFT+DEL을 INSERT키로 치환하는 것이기 때문에 SHIFT+INSERT가 되지 않게 SHIFT를 빼준다.
          register_code(KC_DEL);

        } else {
          register_code(KC_BSPC);
        }
      }
      // 키보드가 눌리지 않았을 경우 등록된 코드를 풀어준다.
      else {
        unregister_code(KC_DEL);
        unregister_code(KC_BSPC);
       }
      return false; // 발생한 키 처리를 했으니 false 처리를 하여 중복으로 넘겨주지 않도록 한다.

    case KC_4:
      // 키보드가 눌렸을 경우
       if (record->event.pressed){
        // 왼쪽 SHIFT키와 오른쪽 SHIFT키가 눌렸는지 확인
        if (get_mods() & MOD_BIT(KC_LCTL)||get_mods() & MOD_BIT(KC_LOPT)){
         // SHIFT+DEL을 INSERT키로 치환하는 것이기 때문에 SHIFT+INSERT가 되지 않게 SHIFT를 빼준다.
          register_code(KC_F4);
        } else {
          register_code(KC_4);
        }
      }
      // 키보드가 눌리지 않았을 경우 등록된 코드를 풀어준다.
      else {
        unregister_code(KC_F4);
        unregister_code(KC_4);
       }
      return false; // 발생한 키 처리를 했으니 false 처리를 하여 중복으로 넘겨주지 않도록 한다.


    default:
      return true; // Process all other keycodes normally
 }
 return true;
}
