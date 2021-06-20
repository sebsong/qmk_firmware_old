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

//Sets up what the OLED screens display.

#include "definitions.h"
#include "oled.h"
#include <stdio.h>

#ifdef OLED_DRIVER_ENABLE

#define IDLE_FRAME_DELAY 1000
#define TAP_FRAME_DELAY_SLOW 1000
#define TAP_FRAME_DELAY_FAST 100

uint16_t last_idle_frame_time;
uint16_t last_tap_frame_time;
int current_idle_frame = 0;
int current_tap_frame = 0;

static void render_bongo_cat_idle(bool reverse) {
    if (timer_elapsed(last_idle_frame_time) > IDLE_FRAME_DELAY) {
        current_idle_frame++;
        current_idle_frame %= IDLE_FRAMES;
        last_idle_frame_time = timer_read();
    }

    if (!reverse) {
        oled_write_raw_P(idle[current_idle_frame], ANIM_SIZE);
    } else {
        oled_write_raw_P(idle_reverse[current_idle_frame], ANIM_SIZE);
    }
}

static void render_bongo_cat_tap(bool reverse) {
    int frame_delay;
    if (rgblight_is_enabled()) {
        frame_delay = TAP_FRAME_DELAY_FAST;
    } else {
        frame_delay = TAP_FRAME_DELAY_SLOW;
    }

    if (timer_elapsed(last_tap_frame_time) > frame_delay) {
        current_tap_frame++;
        current_tap_frame %= TAP_FRAMES;
        last_tap_frame_time = timer_read();
    }

    if (!reverse) {
        oled_write_raw_P(tap[current_tap_frame], ANIM_SIZE);
    } else {
        oled_write_raw_P(tap_reverse[current_tap_frame], ANIM_SIZE);
    }
}

// static void render_logo(void) {
//     static const char PROGMEM qmk_logo[] = {
//         0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
//         0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
//         0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0
//     };

//     oled_write_P(qmk_logo, false);
// }

// static void print_status_narrow(void) {
//     // Print current mode
//     oled_write_P(PSTR("\n\n"), false);

//     oled_write_ln_P(PSTR("QWRTY"), false);
//     oled_write_P(PSTR("\n\n"), false);
//     // Print current layer
//     oled_write_ln_P(PSTR("LAYER"), false);
//     switch (get_highest_layer(layer_state)) {
//         case DEFAULT:
//             oled_write_P(PSTR("base\n"), false);
//             break;
//         case LOWER:
//             oled_write_P(PSTR("lower\n"), false);
//             break;
//         case RAISE:
//             oled_write_P(PSTR("raise"), false);
//             break;
//         default:
//             oled_write_ln_P(PSTR("Undef"), false);
//     }
//     oled_write_P(PSTR("\n\n"), false);
// }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_0;
    } else {
        return OLED_ROTATION_180;
    }
}

void oled_task_user(void) {
    bool reverse;
    if (is_keyboard_master()) {
        reverse = false;
    } else {
        reverse = true;
    }

    if (!rgblight_is_enabled()) {
        render_bongo_cat_idle(reverse);
    } else {
        render_bongo_cat_tap(reverse);
    }
}

#endif
