// Copyright 2021-2024 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @mainpage Pascal Getreuer's QMK keymap
 *
 * This is my Quantum Mechanical Keyboard (QMK) keymap for the Dactyl Ergodox.
 * Who knew a keyboard could do so much?
 *
 * Feature libraries
 * -----------------
 *  * features/achordion.h: customize the tap-hold decision
 *  * features/autocorrection.h: run rudimentary autocorrection on your keyboard
 *  * features/caps_word.h: modern alternative to Caps Lock
 *  * features/custom_shift_keys.h: they're surprisingly tricky to get right;
 *                                  here is my approach
 *  * features/layer_lock.h: macro to stay in the current layer
 *  * features/mouse_turbo_click.h: macro that clicks the mouse rapidly
 *  * features/orbital_mouse.h: a polar approach to mouse key control
 *  * features/repeat_key.h: a "repeat last key" implementation
 *  * features/sentence_case.h: capitalize first letter of sentences
 *  * features/select_word.h: macro for convenient word or line selection
 *  * features/socd_cleaner.h: enhance WASD for fast inputs for gaming
 *
 * License
 * -------
 * This repo uses the Apache License 2.0 except where otherwise indicated. See
 * LICENSE.txt for details.
 *
 * For further documentation of this keymap's features, see
 * <https://getreuer.info/posts/keyboards>
 */

#ifdef ACHORDION_ENABLE
#include "features/achordion.h"
#endif  // ACHORDION_ENABLE
#ifdef CUSTOM_SHIFT_KEYS_ENABLE
#include "features/custom_shift_keys.h"
#endif  // CUSTOM_SHIFT_KEYS_ENABLE
#ifdef LAYER_LOCK_ENABLE
#include "features/layer_lock.h"
#endif  // LAYER_LOCK_ENABLE
#ifdef ORBITAL_MOUSE_ENABLE
#include "features/orbital_mouse.h"
#endif  // ORBITAL_MOUSE_ENABLE
#ifdef SENTENCE_CASE_ENABLE
#include "features/sentence_case.h"
#endif

// Home row mods (0 is inside of index, 1 is index, etc.)
#define H0 HYPR_T
#define H1 LSFT_T
#define H2 LCTL_T
#define H3 LALT_T
#define H4 LGUI_T
// Layer switches
#define FUN_MIN LT(FUN, KC_MINS)
#define SYM_MO  MO(SYM)
#define TO_GAME TO(GAME)

enum layers {
  BASE,
  SYM,
  NUM,
  FUN,
  GAME,
};

enum custom_keycodes {
  LLOCK = SAFE_RANGE,
};

///////////////////////////////////////////////////////////////////////////////
// Tap-hold configuration (https://docs.qmk.fm/tap_hold)
///////////////////////////////////////////////////////////////////////////////
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    default:
      return TAPPING_TERM;
  }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
  // If you quickly hold a tap-hold key after tapping it, the tap action is
  // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
  // lead to missed triggers in fast typing. Here, returning 0 means we
  // instead want to "force hold" and disable key repeating.
  switch (keycode) {
    case H0(KC_H):
    case H1(KC_J):
    case H2(KC_K):
    case H3(KC_L):
      return 120;
    default:
      return 0;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Achordion (https://getreuer.info/posts/keyboards/achordion)
///////////////////////////////////////////////////////////////////////////////
#ifdef ACHORDION_ENABLE
bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
  // Also allow same-hand holds when the other key is in the rows outside the
  // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboards are split.
  uint8_t row = other_record->event.key.row % (MATRIX_ROWS / 2);
  if (!(1 <= row && row <= 3)) { return true; }

  return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  switch (tap_hold_keycode) {
    default:
      return 500;
  }
}

uint16_t achordion_streak_chord_timeout(
    uint16_t tap_hold_keycode, uint16_t next_keycode) {
  // Disable streak detection on LT keys.
  if (IS_QK_LAYER_TAP(tap_hold_keycode)) {
    return 0;
  }

  // Otherwise, tap_hold_keycode is a mod-tap key.
  const uint8_t mod = mod_config(QK_MOD_TAP_GET_MODS(tap_hold_keycode));
  if ((mod & MOD_LSFT) != 0) {
    return 100;  // A short streak timeout for Shift mod-tap keys.
  } else {
    return 220;  // A longer timeout otherwise.
  }
}
#endif  // ACHORDION_ENABLE

///////////////////////////////////////////////////////////////////////////////
// Autocorrect (https://docs.qmk.fm/features/autocorrect)
///////////////////////////////////////////////////////////////////////////////
#ifdef AUTOCORRECT_ENABLE
bool apply_autocorrect(uint8_t backspaces, const char* str,
                       char* typo, char* correct) {
  for (uint8_t i = 0; i < backspaces; ++i) {
    tap_code(KC_BSPC);
  }
  send_string_with_delay_P(str, TAP_CODE_DELAY);
  return false;
}
#endif  // AUTOCORRECT_ENABLE

///////////////////////////////////////////////////////////////////////////////
// User macro callbacks (https://docs.qmk.fm/feature_macros)
///////////////////////////////////////////////////////////////////////////////
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
#ifdef ACHORDION_ENABLE
  if (!process_achordion(keycode, record)) { return false; }
#endif  // ACHORDION_ENABLE
#ifdef ORBITAL_MOUSE_ENABLE
  if (!process_orbital_mouse(keycode, record)) { return false; }
#endif  // ORBITAL_MOUSE_ENABLE
#ifdef LAYER_LOCK_ENABLE
  if (!process_layer_lock(keycode, record, LLOCK)) { return false; }
#endif  // LAYER_LOCK_ENABLE
#ifdef SENTENCE_CASE_ENABLE
  if (!process_sentence_case(keycode, record)) { return false; }
#endif  // SENTENCE_CASE_ENABLE
#ifdef CUSTOM_SHIFT_KEYS_ENABLE
  if (!process_custom_shift_keys(keycode, record)) { return false; }
#endif  // CUSTOM_SHIFT_KEYS_ENABLE

  const uint8_t mods = get_mods();
  const uint8_t all_mods = (mods | get_weak_mods()
#ifndef NO_ACTION_ONESHOT
                        | get_oneshot_mods()
#endif  // NO_ACTION_ONESHOT
  );
  const uint8_t shift_mods = all_mods & MOD_MASK_SHIFT;
  const bool alt = all_mods & MOD_BIT(KC_LALT);

  switch (keycode) {
    // Behavior:
    //  * Unmodified:       _ (KC_UNDS)
    //  * With Shift:       - (KC_MINS)
    //  * With Alt:         Unicode en dash
    //  * With Shift + Alt: Unicode em dash
    case KC_UNDS: {
        static uint16_t registered_keycode = KC_NO;

        if (record->event.pressed) {
          if (alt) {
            send_unicode_string(shift_mods ? "\xe2\x80\x94" : "\xe2\x80\x93");
          } else {
            process_caps_word(keycode, record);
            const bool shifted = (mods | get_weak_mods()) & MOD_MASK_SHIFT;
            clear_weak_mods();
            clear_mods();

            if (registered_keycode) {  // Invoked through Repeat key.
              unregister_code16(registered_keycode);
            } else {
              registered_keycode = shifted ? KC_MINS : KC_UNDS;
            }

            register_code16(registered_keycode);
            set_mods(mods);
          }
        } else if (registered_keycode) {
          unregister_code16(registered_keycode);
          registered_keycode = KC_NO;
        }
      } return false;
  }


  return true;
}

void matrix_scan_user(void) {
#ifdef ACHORDION_ENABLE
  achordion_task();
#endif  // ACHORDION_ENABLE
#ifdef LAYER_LOCK_ENABLE
  layer_lock_task();
#endif  // LAYER_LOCK_ENABLE
#ifdef ORBITAL_MOUSE_ENABLE
  orbital_mouse_task();
#endif  // ORBITAL_MOUSE_ENABLE
#ifdef SENTENCE_CASE_ENABLE
  sentence_case_task();
#endif  // SENTENCE_CASE_ENABLE
}

