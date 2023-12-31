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

#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#define EE_HANDS

// #define USB_MAX_POWER_CONSUMPTION 350

#define USB_POLLING_INTERVAL_MS 1

// MOUSE
#define MK_KINETIC_SPEED

#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_MOVE_DELTA 0.5
#define MOUSEKEY_MAX_SPEED 30

#define MOUSEKEY_WHEEL_DELAY 0
#define MOUSEKEY_WHEEL_TIME_TO_MAX 8
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 4
#define MOUSEKEY_WHEEL_MAX_SPEED 4

// RGB
#define RGB_DI_PIN D3
#define RGBLED_NUM 74
#define RGBLED_SPLIT {37,37}
#define RGBLIGHT_LIMIT_VAL 150

#define RGBLIGHT_DEFAULT_HUE 180
#define RGBLIGHT_EFFECT_TWINKLE

// disable features to try to save some space
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT
// #define NO_ACTION_TAPPING

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
