#include "encoder.h"
enum state {
    REST,   
    CW_A,   
    CW_B,   
    CW_C,   
    CCW_A,  
    CCW_B, 
    CCW_C
};
// Current state of each encoder
uint8_t curRead[6] = {0b11, 0b11, 0b11, 0b11, 0b11, 0b11};
uint8_t prevRead[6] = {0b11, 0b11, 0b11, 0b11, 0b11, 0b11};
// current state 0-3 for clockwise 0-(-3) for counter clockwise
int curState[6] = {REST, REST, REST, REST, REST, REST};
void updateStates(uint8_t enc) {
    // Read the encoder state into two bits
    uint8_t pinA = readEncoder(enc, 0);
    uint8_t pinB = readEncoder(enc, 1);
    // store the current reading
    curRead[enc] = (pinA << 1) | pinB;

    // Check if pin A or B have gone low on the current read
    if (prevRead[enc] == 0b11 && curState[enc] == REST) {
        if (pinA == 0) {
            #ifdef DEBUG_STATE
                print("STATE 0 -> 1 CCW\n");
            #endif
            curState[enc] = CCW_A;
        } else if (pinB == 0) {
            curState[enc] = CW_A;
        } else {
            // invalid state then reset
            curState[enc] = REST;
        }
    } 
    // State 2 CW or CCW, check for both pins low on current read
    if (prevRead[enc] == 0b10 && curState[enc] == CW_A) {
        if (pinA == 0 && pinB == 0) {
            curState[enc] = CW_B;
        } else if (pinA == 1 && pinB == 0) {
            // State stays the same if pins are the same
            curState[enc] = CW_A;
        } else {
            curState[enc] = REST;
        }
    } else if (prevRead[enc] == 0b01 && curState[enc] == CCW_A) {
        if (pinA == 0 && pinB == 0) {
            #ifdef DEBUG_STATE
                print("STATE 1 -> 2 CCW\n");
            #endif
            curState[enc] = CCW_B;
        } else if (pinA == 0 && pinB == 1) {
            // Pins stay the same so does the state
            curState[enc] = CCW_A;
        } else {
            curState[enc] = REST;
        }
    }
    
    // State 3, first pin goes back high
    if (prevRead[enc] == 0b00 && curState[enc] == CW_B) {
        if (pinA == 0 && pinB == 1) {
            curState[enc] = CW_C;
        } else if (pinA == 0 && pinB == 0) {
            // state stays the same
            curState[enc] = CW_B;
        } else {
            curState[enc] = REST;
        }
    } else if (prevRead[enc] == 0b00 && curState[enc] == CCW_B) {
        if (pinA == 1 && pinB == 0) {
            #ifdef DEBUG_STATE
                print("STATE 2 -> 3 CCW\n");
            #endif
            curState[enc] = CCW_C;
        } else if (pinA == 0 && pinB == 0) {
            curState[enc] = CCW_B;
        } else {
            curState[enc] = REST;
        }
    }

    // state 4: both pins are high
    // Send a keycode on a successful read
    if (prevRead[enc] == 0b01 && curState[enc] == CW_C) {
        if (pinA == 1 && pinB == 1) {
            // send keystroke and reset state to rest
            sendKeyAction(enc, 0);
            curState[enc] = REST;
        } else if (pinA == 0 && pinB == 1) {
            // same state
            curState[enc] = CW_C;
        } else {
            // invalid state
            curState[enc] = REST;
        }
    } else if (prevRead[enc] == 0b10 && curState[enc] == CCW_C) {
        if (pinA == 1 && pinB == 1) {
            sendKeyAction(enc, 1);
            curState[enc] = REST;
        } else if (pinA == 1 && pinB == 0) {
            curState[enc] = CCW_C;
        } else {
            curState[enc] = REST;
        }
    }


    // update the previous state at the end of the iteration
    // reset to high if in the rest state at all
    prevRead[enc] = curRead[enc];
    
}

/**
 * Send the correct key action
 * on a successful state traversal
 */
void sendKeyAction(uint8_t enc, uint8_t dir) {
    #ifdef DEBUG
    print("ENCODER #");
    print_dec(enc);
    print(" ROTATED ");
    if (dir == 1) {
        print("COUNTER CLOCKWISE\n");
    } else {
        print("CLOCKWISE\n");
    }
    uart_putchar('G');
    #endif

    // Check the keymap from encodermap and send the action
    // TODO: Add support for modifier keys
    // make this non blocking as well
    // Clockwise codes
    if (dir == 0) {
        register_code(ENCODERMAP_CLK[enc].code);
        _delay_us(100);
        unregister_code(ENCODERMAP_CLK[enc].code);
    } else if (dir == 1) {
        // counter clockwise
        register_code(ENCODERMAP_CCLK[enc].code);
        _delay_us(100);
        unregister_code(ENCODERMAP_CCLK[enc].code);
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