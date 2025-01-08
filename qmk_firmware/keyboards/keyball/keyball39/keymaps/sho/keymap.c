/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "lib/keyball/keyball.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
 LCTL_T(KC_A), KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , RCTL_T(KC_ENT),
 LSFT_T(KC_Z), KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   ,RSFT_T(KC_MINS),
    KC_ESC   , XXXXXXX  , KC_LGUI  ,LT(1,KC_TAB),LT(2,KC_SPC),LT(4,KC_LNG2),RALT_T(KC_LNG1),KC_BSPC,XXXXXXX,XXXXXXX  ,XXXXXXX   , MO(3)
  ),

  [1] = LAYOUT_universal(
    S(KC_5)  , S(KC_4)  , S(KC_7)  , S(KC_6)  , KC_SLSH  ,                            KC_NUHS  ,S(KC_LBRC),S(KC_RBRC),S(KC_COMM), S(KC_DOT),
    S(KC_2)  , S(KC_3)  , S(KC_8)  , S(KC_EQL), KC_EQL   ,                           S(KC_MINS), S(KC_9)  , S(KC_0)  , KC_SCLN  ,S(KC_SCLN),
    KC_GRV   , S(KC_GRV), XXXXXXX  , S(KC_1)  ,S(KC_SLSH),                           S(KC_NUHS), KC_LBRC  , KC_RBRC  , KC_QUOT  ,S(KC_QUOT),
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,      XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX
  ),

  [2] = LAYOUT_universal(
    XXXXXXX  , KC_7     , KC_8     , KC_9     , XXXXXXX  ,                            XXXXXXX  , KC_HOME  , KC_UP    , KC_END   , XXXXXXX  ,
    KC_0     , KC_4     , KC_5     , KC_6     , XXXXXXX  ,                            KC_PGUP  , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_PGDN  ,
    KC_0     , KC_1     , KC_2     , KC_3     , XXXXXXX  ,                            XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,      XXXXXXX  , KC_DEL   , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX
  ),

  [3] = LAYOUT_universal(
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                            XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                            XXXXXXX  , KC_BTN4  , KC_BTN3  , KC_BTN5  , XXXXXXX  ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                            XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,      XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX
  ),

  [4] = LAYOUT_universal(
    XXXXXXX  , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,                            CPI_D100 , CPI_I100 , XXXXXXX  , SCRL_DVI , SCRL_DVD ,
    XXXXXXX  , KC_F4    , KC_F5    , KC_F6    , KC_F11   ,                            XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,
    XXXXXXX  , KC_F1    , KC_F2    , KC_F3    , KC_F12   ,                            XXXXXXX  , SSNP_VRT , SSNP_HOR , SSNP_FRE , XXXXXXX  ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,      KBC_RST  , KBC_SAVE , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

// コンボキーの定義
const uint16_t PROGMEM combo_jk[]  = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_kl[]  = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_jkl[] = {KC_J, KC_K, KC_L, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_jk, KC_BTN1),  // j + k → マウス左クリック
    COMBO(combo_kl, KC_BTN2),  // k + l → マウス右クリック
    COMBO(combo_jkl, KC_BTN3), // j + k + l → マウスホイールクリック
};

// 加速度係数の増加率
const float ACCELERATION_SCALE = (ACCELERATION_FACTOR_MAX - ACCELERATION_FACTOR_MIN) / (MOTION_THRESHOLD_MAX - MOTION_THRESHOLD_MIN);

// 加速度係数を計算
static inline float calculate_acceleration_factor(int16_t motion_magnitude) {
    if (motion_magnitude <= MOTION_THRESHOLD_MIN) {
        return ACCELERATION_FACTOR_MIN;
    } else if (motion_magnitude >= MOTION_THRESHOLD_MAX) {
        return ACCELERATION_FACTOR_MAX;
    }
    return ACCELERATION_FACTOR_MIN + (motion_magnitude - MOTION_THRESHOLD_MIN) * ACCELERATION_SCALE;
}

static inline int8_t clip2int8(int16_t v) {
    return (v) < -127 ? -127 : (v) > 127 ? 127 : (int8_t)v;
}

// カーソル移動処理をオーバーライドし、加速度を適用
void keyball_on_apply_motion_to_mouse_move(keyball_motion_t *m, report_mouse_t *r, bool is_left) {
    int16_t motion_magnitude    = abs(m->x) + abs(m->y);
    float   acceleration_factor = calculate_acceleration_factor(motion_magnitude);

    r->x = clip2int8((int16_t)((float)m->y * acceleration_factor));
    r->y = clip2int8((int16_t)((float)m->x * acceleration_factor));

    m->x = 0;
    m->y = 0;
}
