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

#define KC_PTAB LCMD(LSFT(KC_LBRACKET))
#define KC_NTAB LCMD(LSFT(KC_RBRACKET))

#define KC_WIN_PTAB LSFT(LCTRL(KC_TAB))
#define KC_WIN_NTAB LCTRL(KC_TAB)

enum custom_keycodes {
    KC_MAC,
    KC_WIN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| PLAY  |    |  RGB  |------+------+------+------+------+------|
 * |LSHIFT|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RSHIFT|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTL | LALT | LCMD | BSPC | / LOWER /       \RAISE \ |SPACE |ENTER | RALT | RCTL |
 *            |      |      |      |      |/       /         \      \|      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[DEFAULT] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSLS,
  KC_ESC,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MPLY,    RGB_TOG,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                    KC_LCTL, KC_LALT, KC_LCMD, KC_BSPC,MO(LWR),MO(RSE), KC_SPC, KC_ENT, KC_RALT,  KC_RCTL
),
[DEFAULT_WIN] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSLS,
  KC_ESC,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MPLY,    RGB_TOG,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                KC_LCTL, KC_LALT, KC_LCMD, KC_BSPC,MO(LWR_WIN),MO(RSE_WIN), KC_SPC, KC_ENT, KC_RALT,  KC_RCTL
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |      |      |      |      |      |                    |      |   7  |   8  |   9  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |      |      |      |      |      |-------.    ,-------|      |   4  |   5  |   6  |      |      |
 * |------+------+------+------+------+------|  PLAY |    |  RGB  |------+------+------+------+------+------|
 * |LSHIFT|      |      |      |      |      |-------|    |-------|      |   1  |   2  |   3  |      |RSHIFT|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTL | LALT | LCMD | BSPC | /LOWER  /       \RAISE \ |SPACE |   0  |   0  | RCTL |
 *            |      |      |      |      |/       /         \      \|      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[LWR] = LAYOUT(
  XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_EQL,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,    KC_7,    KC_8,    KC_9,  KC_F11, KC_F12,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,     _______, XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX, _______,
                    _______, _______, _______, _______,  _______,   _______,  _______,    KC_0,    KC_0, _______
),
[LWR_WIN] = LAYOUT(
  XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_EQL,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,    KC_7,    KC_8,    KC_9,  KC_F11, KC_F12,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,     _______, XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX, _______,
                    _______, _______, _______, _______,  _______,   _______,  _______,    KC_0,    KC_0, _______
),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |      |PRVTAB|  UP  |NXTTAB|      |                    |SCRL U|LCLICK|MS UP |RCLICK|      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |      | LEFT | DOWN |RIGHT |      |-------.    ,-------|SCRL D|MS LFT|MS DWN|MS RGT|      |      |
 * |------+------+------+------+------+------|  PLAY |    |  RGB  |------+------+------+------+------+------|
 * |LSHIFT|      |      |      |      |      |-------|    |-------|      |      |      |      |      |RSHIFT|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTL | LALT | LCTL | BSPC | / LOWER /       \RAISE \ |SPACE | RCMD | RALT | RCTL |
 *            |      |      |      |      |/       /         \      \|      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[RSE] = LAYOUT(
  KC_WIN,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, KC_PTAB,   KC_UP, KC_NTAB, XXXXXXX,                          KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,                          KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,        _______, XXXXXXX, KC_WH_L, KC_WH_R, XXXXXXX, XXXXXXX, _______,
                    _______, _______, _______, _______,   _______,     _______,  _______, _______, _______, _______
),
[RSE_WIN] = LAYOUT(
  KC_MAC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, KC_PTAB,   KC_UP, KC_NTAB, XXXXXXX,                          KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,                          KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,        _______, XXXXXXX, KC_WH_L, KC_WH_R, XXXXXXX, XXXXXXX, _______,
                    _______, _______, _______, _______,   _______,     _______,  _______, _______, _______, _______
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

    // handle mod tap
    if (IS_LAYER_ON(DEFAULT) || IS_LAYER_ON(DEFAULT_WIN)) {
        return process_record_user_default(keycode, record);
    } else if (IS_LAYER_ON(LWR)) {
        return process_record_user_lower(keycode, record);
    } else if (IS_LAYER_ON(RSE)) {
        return process_record_user_raise(keycode, record);
    }

    // handle layer switching
    switch (keycode) {
        case KC_MAC:
            if (record->event.pressed) {
                set_single_persistent_default_layer(DEFAULT);
            }
            return false;
        case KC_WIN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(DEFAULT_WIN);
            }
            return false;
    }

    return true;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    }
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);

    switch (get_highest_layer(default_layer_state)) {
        case MAC:
            oled_write_ln_P(PSTR("MAC"), false);
            break;
        case WIN:
            oled_write_ln_P(PSTR("WIN"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
}
