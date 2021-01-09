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
#include "timer1.h"
#include <uart.h>

/**
 * Teensy pin assignment 
 */
// encoder 1 (middle right)
#define ENCA_PINA ((PINC >> 6) & 1)
#define ENCA_PINB ((PINC >> 7) & 1)

// Encoder 2 (top right)
#define ENCB_PINB ((PIND >> 5) & 1)
#define ENCB_PINA ((PIND >> 4) & 1)

// Encoder 3 (bottom right)
#define ENCC_PINA ((PIND >> 6) & 1)
#define ENCC_PINB ((PINF >> 0) & 1)

//Encoder 4 (Top left)
#define ENCD_PINB ((PINF >> 1) & 1)
#define ENCD_PINA ((PINF >> 4) & 1)

// Encoder 5 (middle left)
#define ENCE_PINA ((PINF >> 5) & 1)
#define ENCE_PINB ((PINF >> 6) & 1)

// Encoder 6
#define ENCF_PINA ((PINF >> 7) & 1)
#define ENCF_PINB ((PINB >> 6) & 1)

#define ENCODER_TIMEOUT_COUNT 5
#define DEBUG 1

// Current pin values when read
extern uint8_t curA;
extern uint8_t curB;


/**
 * Functions
 */

/**
 * Read the status of the encoders and determine which
 * direction they are being rotated
 * 
 * This function has 10 milliseconds total to send a keystroke to the PC
 * If that threshold gets exceeded then return and do nothing
 * This is to make the system as nonblocking as possible
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