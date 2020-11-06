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
#include "encoder.h"

typedef struct {
	uint8_t                state;
	int32_t                position;
} Encoder_internal_state_t;

const uint8_t * ENCODERMAP_CLK = {
    ']'
};

const uint8_t * ENCODERMAP_CCLK = {
    '['
};
uint8_t curA = 999;

uint8_t prevA = 0;

uint8_t * directions = {
    0
};
int8_t position;

// pins [AB]
// These four states happen each signel turn
// so for clockwise, pin B will always go low first
const uint8_t stateCLK[5] = {
    0b01, 0b00, 0b10, 0b11
};
const uint8_t stateCCLK[5] = {
    0b10, 0b00, 0b01, 0b11
};
/**
 * Read the status of the encoders and determine which
 * direction they are being rotated
 */
int8_t * getDirection() {
    // First get the status of pin a
    if (ENCA_PINA == 0) {
        // wait for pinB to go low (state 2)
        while(ENCA_PINB == 1) {
            // if pin a goes back high then cease
            if (ENCA_PINA == 1) return;
        }
        // wait for state 3 (pinA goes high)
        while (ENCA_PINA == 0) {
            // check for an invalid state
            // if pinB goes back high then return
            if (ENCA_PINB == 1) return;
        }
        // wait for the final state
        // Pin b going high
        while (ENCA_PINB == 0) {
            // If pin a goes back low then return
            if (ENCA_PINA == 0) return;
        }
        print("Clockwise!\n");
    }
    // Check the status of pin B
    else if (ENCA_PINB == 0) {
        // wait for pinA to go low (state 2)
        while(ENCA_PINA == 1) {
            // if pin b goes back high then cease
            if (ENCA_PINB == 1) return;
        }
        // wait for state 3 (pinB goes high)
        while (ENCA_PINB == 0) {
            // check for an invalid state
            // if pinA goes back high then return
            if (ENCA_PINA == 1) return;
        }
        // wait for the final state
        // Pin A going high
        while (ENCA_PINA == 0) {
            // If pin b goes back low then return
            if (ENCA_PINB == 0) return;
        }
        print("Counter Clockwise!\n");
    }

}

void readEncoders() {
    // grab the two pins for encoder 1
    uint8_t pinA = ENCA_PINA;
    uint8_t pinB = ENCA_PINB;
    // Set them such that the result is 2 bits of data
    curA = (pinA << 1) | (pinB);
}