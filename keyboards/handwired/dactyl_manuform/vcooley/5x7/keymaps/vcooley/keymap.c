#include QMK_KEYBOARD_H

#include "vcooley.c"

// USE THIS FOR NEW LAYERS
// [_BLANK] = LAYOUT_5x7(
//     // left hand
//     _______,   _______,   _______,   _______,   _______,   _______,  _______,
//     _______,   _______,   _______,   _______,   _______,   _______,  _______,
//     _______,   _______,   H4(KC_),   H3(KC_),   H2(KC_),   H1(KC_),  H0(KC_),
//     _______,   _______,   _______,   _______,   _______,   _______,  _______,
//                                      _______, _______,
//                                                                 _______, _______,
//                                                                 _______, _______,
//                                                                 _______, _______,
//     // right hand
//                  _______,   _______,   _______,   _______,   _______,   _______,   _______,
//                  _______,   _______,   _______,   _______,   _______,   _______,   _______,
//                  H0(KC_),   H1(KC_),   H2(KC_),   H3(KC_),   H4(KC_),  _______,   _______,
//                  _______,   _______,   _______,   _______,   _______,   _______,   _______,
//                                        _______,   _______,
//     _______, _______,
//     _______, _______,
//     _______, _______
// )

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT_5x7(
        // left hand
        KC_NO,  _______,       KC_1,    KC_2,    KC_3,   KC_4,   KC_5,
        KC_NO,  _______,       KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,
        KC_NO,  _______,   HL4(KC_A), HL3(KC_S), HL2(KC_D), HL1(KC_F), HL0(KC_G),
        KC_NO,  OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,   KC_V, KC_B,
                                                 KC_UP,  KC_DOWN,

                                                                    KC_ESC,   KC_SPC,
                                                                   FUN_MIN,   KC_TAB,
                                                                   KC_PSCR,   KC_9,

        // right hand
                      KC_6,    KC_7,    KC_8,     KC_9,     KC_0,     KC_GRV,     KC_NO,
                      KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLS,    KC_NO,
              HR0(KC_H), HR1(KC_J),  HR2(KC_K),  HR3(KC_L),  HR4(KC_SCLN),  KC_QUOT,    KC_NO,
                      KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  OSM(MOD_RSFT), KC_NO,
                                        KC_LEFT, KC_RGHT,

             KC_BSPC,  OSM(MOD_LSFT),
             KC_ENT,      OSL(SYM),
             KC_LCTL,     KC_LALT
    ),

    [SYM] = LAYOUT_5x7(
        // left hand
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   KC_TILD,   KC_PLUS,   KC_LBRC,   KC_LCBR,   KC_LPRN,  KC_MINS,
        _______,   _______,   KC_EXLM,   KC_AT,     KC_HASH,   KC_DLR,   KC_PERC,
                                         _______,   _______,
                                                                    KC_MINS, KC_UNDS,
                                                                    _______, _______,
                                                                    _______, _______,

        // right hand
                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
                     KC_EQL,    KC_RPRN,   KC_RCBR,   KC_RBRC,   KC_ASTR,    KC_GRV,   _______,
                     KC_CIRC,   KC_AMPR,   KC_ASTR,   KC_PLUS,   KC_DLR,    _______,   _______,
                                           _______,   _______,
        KC_TRNS, _______,
        _______, _______,
        _______, _______
    ),
    [FUN] = LAYOUT_5x7(
        // left hand
        QK_BOOT,   _______,     KC_F1,     KC_F2,     KC_F3,    KC_F4,    KC_F5,
        _______,   _______,   _______,   _______,  _______,   _______,  _______,
        _______,   _______,   KC_LCTL,   KC_LALT,  KC_LGUI,   KC_LSFT,  KC_HYPR,
        TO(GAME), _______,   _______,   _______,  _______,   _______,  _______,
                   KC_MPRV,   KC_MNXT,
                                    _______, _______,
                                    _______, _______,
                                    _______, _______,
        // right hand
                          KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,
                          _______,   KC_BRID,   KC_BRIU,   _______,   _______,   _______,   _______,
                          KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _______,   _______,   _______,
                          KC_MUTE,   KC_VOLD,   KC_VOLU,   _______,   _______,   _______,   _______,
                                                KC_MPRV,   KC_MNXT,
             KC_DEL,  KC_LSFT,
             KC_ENT,  KC_MPLY,
             _______, KC_MSTP
    ),

    [NUM] = LAYOUT_5x7(
        // left hand
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,
                                    _______, _______,
                                    _______, _______,
                                    _______, _______,
        // right hand
                          _______,   _______,   KC_NUM,    _______,   KC_PMNS,   KC_PPLS,   _______,
                          _______,   _______,   KC_P7,     KC_P8,     KC_P9,     _______,   _______,
                          _______,   _______,   KC_P4,     KC_P5,     KC_P6,     KC_PAST,   _______,
                          _______,   _______,   KC_P1,     KC_P2,     KC_P3,     KC_PSLS,   _______,
                                                           KC_P1,     KC_PDOT,
             _______, KC_PENT,
             _______, _______,
             _______, _______
),

    [GAME] = LAYOUT_5x7(
        // left hand
        KC_NO,KC_NO, KC_ESC,   KC_1,    KC_2,    KC_3,   KC_4,
        KC_NO,KC_NO, KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,
        KC_NO,KC_NO, KC_LCTL,  KC_A,    KC_S,    KC_D,   KC_F,
        KC_NO,KC_NO, KC_LSFT,  KC_Z,    KC_X,    KC_C,   KC_V,
                                                 KC_T,   KC_G,
                                                                    KC_LALT, KC_SPC,
                                                                    KC_B,    KC_TAB,
                                                                    _______, KC_5,

        // right hand
                 _______,   _______,   _______,   _______,   _______,   _______,   TG(GAME),
                 _______,   _______,   _______,   _______,   _______,   _______,   _______,
                 _______,   _______,   _______,   _______,   _______,   _______,   _______,
                 _______,   _______,   _______,   _______,   _______,   _______,   _______,
                                       _______,   _______,
    _______, _______,
    _______, _______,
    _______, _______
    ),

};
