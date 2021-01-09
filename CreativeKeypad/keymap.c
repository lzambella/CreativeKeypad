/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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
#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"

/*
For now, hardcode the keys and map them to standard ASCII keys
TMK has function specific keys that could be read from computer software and translate that to ascii however

The last 3 rows correspond to the encoder outputs
so there are two 'columns' each dedicated to the clockwise/counter clockwise direction
*/
#define KEYMAP( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23 \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03}, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13}, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23}, \
}

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = KEYMAP(
        0, 1, 2, 3, \
        4, 5, 6, 7, \
        8, 9, LCTRL, LALT
    )
};

/*
 * Fn action definition
 */
const action_t PROGMEM fn_actions[] = {
};
