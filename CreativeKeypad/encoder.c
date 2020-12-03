/**
COPYRIGHT 2020 LUKE ZAMBELLA
Encoder Handler

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



void getDirection(uint8_t enc) {
    // reset the timer count
    timer1_clear();

    // First check if pin A was activated
    if (readEncoder(enc, 0) == 0) {
        // Next wait for pin B to activate by
        // blocking until the pin goes low
        while(readEncoder(enc, 1) == 1) {
            // if pin A gets deactivated then cease operation
            if (readEncoder(enc, 0) == 1) return;
            // Timeout after 10 total milliseconds
            if (timer1_read32() > ENCODER_TIMEOUT_COUNT) {
                if (DEBUG) 
                    print("TIMEOUT\n");
                return;
            }
        }

        // wait for state 3 (pin A is diabled)
        while (readEncoder(enc, 0) == 0) {
            // check for an invalid state
            // if pinB goes back high then return
            if (readEncoder(enc, 1) == 1) return;
            // Timeout after 10 total milliseconds
            if (timer1_read32() > ENCODER_TIMEOUT_COUNT){
                if (DEBUG)
                    print("TIMEOUT\n");
                return;
            }
        }
        // wait for the final state
        // Pin b going high
        while (readEncoder(enc, 1) == 0) {
            // If pin a goes back low then return
            if (readEncoder(enc, 0) == 0) return;
            // Timeout after 10 total milliseconds
            if (timer1_read32() > ENCODER_TIMEOUT_COUNT){
                if (DEBUG)
                    print("TIMEOUT\n");
                return;
            }
        }
        if(DEBUG)
            print("Counter Clockwise!\n");

        register_code(ENCODERMAP_CLK[enc].code);
        _delay_us(100);
        unregister_code(ENCODERMAP_CLK[enc].code);
        //directions[0] = -1;
    }

    // Check the status of pin B if pin A wasnt not activated
    else if (readEncoder(enc, 1) == 0) {
        // wait for pinA to go low (state 2)
        while(readEncoder(enc, 0) == 1) {
            // if pin b goes back high then cease
            if (readEncoder(enc, 1) == 1) return;

            if (timer1_read32() > ENCODER_TIMEOUT_COUNT) {
                if (DEBUG) 
                    print("TIMEOUT\n");
                return;
            }
        }
        // wait for state 3 (pinB goes high)
        while (readEncoder(enc, 1) == 0) {
            // check for an invalid state
            // if pinA goes back high then return
            if (readEncoder(enc, 0) == 1) return;

            if (timer1_read32() > ENCODER_TIMEOUT_COUNT) {
                if (DEBUG) 
                    print("TIMEOUT\n");
                return;
            }
        }
        // wait for the final state
        // Pin A going high
        while (readEncoder(enc, 0) == 0) {
            // If pin b goes back low then return
            if (readEncoder(enc, 1) == 0) return;

            if (timer1_read32() > ENCODER_TIMEOUT_COUNT) {
                if (DEBUG) 
                    print("TIMEOUT\n");
                return;
            }
        }
        if(DEBUG)
            print("Clockwise!\n");
        register_code(ENCODERMAP_CCLK[enc].code);
        _delay_us(100);
        unregister_code(ENCODERMAP_CCLK[enc].code);
        //directions[0] = 1;
    }

}

uint8_t readEncoder(uint8_t encNum, uint8_t pinNum) {
    // Pin A
    if (pinNum == 0) {
        switch (encNum) {
            case 0:
                return ENCA_PINA;
                break;
            case 1:
                return ENCB_PINA;
                break;
            case 2:
                return ENCC_PINA;
                break;
            case 3:
                return ENCD_PINA;
                break;
            case 4:
                return ENCE_PINA;
                break;   
            case 5:
                return ENCF_PINA;

        }
    // pin B
    } else if (pinNum == 1) {
        switch (encNum) {
            case 0:
                return ENCA_PINB;
                break;
            case 1:
                return ENCB_PINB;
                break;
            case 2:
                return ENCC_PINB;
                break;
            case 3: 
                return ENCD_PINB;
                break;
            case 4:
                return ENCE_PINB;
                break;
            case 5:
                return ENCF_PINB;
        }
    } 
}