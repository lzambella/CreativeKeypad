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
/**
 * Teensy pin assignment 
 */
#define ENCA_PINA ((PINC >> 6) & 1)
#define ENCA_PINB ((PINC >> 7) & 1)

/**
 * Define some global variables.
 */

/// Delay for debouncing
#define BOUNCE_DELAY_US 50
#define SETTLE_DELAY_US 4000
/// Number of encoders on the device
#define ENCODER_COUNT 1

/**
 * Map the encoder directions to a character
 * Use two arrays because we want different actions for clockwise/counterclockwise
 */
const extern uint8_t * ENCODERMAP_CLK;
const extern uint8_t * ENCODERMAP_CCLK;

// Current pin values when read
extern uint8_t curA;
extern uint8_t curB;

/// Stored value of the previous states of pin A for all encoders
extern uint8_t prevA;    
/// Stored value of the prevoius states of pin B for all encoders
extern uint8_t prevB;

// Create a single array for the directions thats always updated
extern uint8_t * directions;
/**
 * Functions
 */

/**
 * Get the directions that the encoders have rotated
 * OUTPUT: -1 if rotated counter clockwise, 1 if rotated clockwise, 0 otherwise. 
 * Results are stored in an array of size #ENCODER_COUNT for each encoder
 */
int8_t * getDirection();

/**
 * Reads the values of the pins all encoders are attached too
 * Updates the two arrays curA and curB with the binary data of the pins
 * where encoder 0 is the least significant bits
 */
void readEncoders();