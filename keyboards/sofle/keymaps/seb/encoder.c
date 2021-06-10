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

//Setting up what encoder rotation does. If your encoder can be pressed as a button, that function can be set in Via.
#include "definitions.h"

#ifdef ENCODER_ENABLE

enum ENCODERS {
    LEFT,
    RIGHT
};

void left_encoder_update_user(bool clockwise) {
    if (IS_LAYER_ON(RAISE)) {
        if (clockwise) {
            tap_code(KC_MEDIA_NEXT_TRACK);
        } else {
            tap_code(KC_MEDIA_PREV_TRACK);
        }
    } else {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}

void right_encoder_update_user(bool clockwise) {
    if (clockwise) {
        tap_code(KC_DOWN);
    } else {
        tap_code(KC_UP);
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == LEFT) {
        left_encoder_update_user(clockwise);
    } else if (index == RIGHT) {
        right_encoder_update_user(!clockwise); // not sure why it seems like this is reversed for right side encoder
    }

    return true;
}

#endif
