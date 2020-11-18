/**
COPYRIGHT 2020 LUKE ZAMBELLA

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
#include <avr/io.h>
#include "keycode.h"
#include <util/delay.h>
#include "debug.h"
#include "actionmap.h"
#include "encodermap.h"
/**
 * Teensy pin assignment 
 */
// encoder 1 (middle right)
#define ENCA_PINA ((PINC >> 6) & 1)
#define ENCA_PINB ((PINC >> 7) & 1)

// Encoder 2 (top right)
#define ENCB_PINA ((PIND >> 5) & 1)
#define ENCB_PINB ((PIND >> 4) & 1)

// Encoder 3 (bottom right)
#define ENCC_PINB ((PIND >> 6) & 1)
#define ENCC_PINA ((PINF >> 0) & 1)

/**
 * Define some global variables.
 */


// Current pin values when read
extern uint8_t curA;
extern uint8_t curB;

/// Stored value of the previous states of pin A for all encoders
extern uint8_t prevA;    
/// Stored value of the prevoius states of pin B for all encoders
extern uint8_t prevB;


/**
 * Functions
 */

/**
 * Read the status of the encoders and determine which
 * direction they are being rotated
 * 
 * INPUT: encoder number [0-5]
 * OUTPUT: keystroke event corresponding to ENCODERMAP_CLK/CCLK[0-5]
 */
void getDirection(uint8_t enc);

/**
 * Gets the enocder input per pin
 * INPUT:
 *  encNum: The number of the encoder to check
 *  pinNum: The pin (A or B) of the encoder
 * 
 * OUTPUT:
 *  The status of the desired pin (HIGH or LOW)
 */
uint8_t readEncoder(uint8_t encNum, uint8_t pinNum);