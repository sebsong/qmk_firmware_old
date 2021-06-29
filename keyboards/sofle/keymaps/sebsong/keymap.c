 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H
#include "keyboards/sofle/sofle.h"
#include "keyboards/sofle/rev2/config.h"
#include "oled.c"
#include "encoder.c"

#include "definitions.h"
#include "keycode.h"
#include "tmk_core/common/action.h"
#include "quantum/quantum_keycodes.h"

#include "stdint.h"
#include "stdbool.h"

#define TAP_DELAY 200

#define KC_PRV_TAB LCMD(LSFT(KC_LBRACKET))
#define KC_NXT_TAB LCMD(LSFT(KC_RBRACKET))

//Default keymap. This can be changed in Via. Use oled.c and encoder.c to change beavior that Via cannot change.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTR | LAlt | LCMD |ENTER | /LOWER  /       \RAISE \  |SPACE | RCMD | RAlt | RCTR |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[DEFAULT] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSLASH,
  KC_ESC,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MPLY,     RGB_TOG,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                   KC_LCTRL,KC_LALT,KC_LCMD, KC_BSPC, MO(LOWER), MO(RAISE), KC_SPC, KC_ENT, KC_RALT, KC_RCTRL
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | Shift|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[LOWER] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_EQUAL,
  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12,
  _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                       KC_CIRC, KC_4, KC_5, KC_6, KC_RPRN, KC_PIPE,
  _______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,       _______, KC_LBRC, KC_1, KC_2, KC_3, KC_BSLS, _______,
                       _______, _______, _______, _______, _______,       _______, XXXXXXX,  KC_0, KC_0 ,_______
),
/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[RAISE] = LAYOUT(
  _______, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______,
  _______,  KC_INS,  KC_PRV_TAB,   KC_UP,  KC_NXT_TAB, XXXXXXX,                        KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2,_______, KC_BSPC,
  KC_SLEP, KC_LALT,  KC_LEFT,  KC_DOWN,  KC_RGHT, KC_CAPS,                       KC_WH_D,  KC_MS_L, KC_MS_D, KC_MS_R,  KC_DEL, KC_BSPC,
  _______,KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,  _______,       _______,  XXXXXXX, _______, XXXXXXX, _______,   XXXXXXX, _______,
                         _______, _______, _______, KC_MS_BTN1, _______,       _______, _______, _______, _______, _______
)
};

bool key_pressed;

void mod_tap(uint16_t mod, uint16_t tap, keyrecord_t *record, bool shift_tap) {
    static uint16_t start;
    if (record->event.pressed) {
        start = timer_read();
        key_pressed = false;
        register_code(mod);
    } else {
        if (!shift_tap) {
            unregister_code(mod);
        }

        if (!key_pressed && timer_elapsed(start) < TAP_DELAY) {
            tap_code(tap);
        }

        if (shift_tap) {
            unregister_code(mod);
        }
    }
}

bool process_record_user_default(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSHIFT:
            mod_tap(keycode, KC_9, record, true);
            break;
        case KC_RSHIFT:
            mod_tap(keycode, KC_0, record, true);
    }

    return true;
}

bool process_record_user_lower(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSHIFT:
            mod_tap(keycode, KC_LEFT_CURLY_BRACE, record, true);
            break;
        case KC_RSHIFT:
            mod_tap(keycode, KC_RIGHT_CURLY_BRACE, record, true);
    }

    return true;
}

bool process_record_user_raise(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSHIFT:
            mod_tap(keycode, KC_LBRACKET, record, false);
            break;
        case KC_RSHIFT:
            mod_tap(keycode, KC_RBRACKET, record, false);
            break;
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        key_pressed = true;
    }

    if (IS_LAYER_ON(DEFAULT)) {
        return process_record_user_default(keycode, record);
    } else if (IS_LAYER_ON(LOWER)) {
        return process_record_user_lower(keycode, record);
    } else if (IS_LAYER_ON(RAISE)) {
        return process_record_user_raise(keycode, record);
    }

    return true;
}
