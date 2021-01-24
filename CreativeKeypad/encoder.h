#include <avr/io.h>
#include "uart.h"
#include "debug.h"
#include <stdint.h>
#include "actionmap.h"
#include "encodermap.h"
#include <util/delay.h>

// encoder 1 (middle right)
#define ENCA_PINA ((PINC >> 6) & 1)
#define ENCA_PINB ((PINC >> 7) & 1)

// Encoder 2 (top right)
#define ENCB_PINB ((PINF >> 1) & 1)
#define ENCB_PINA ((PINF >> 0) & 1)

// Encoder 3 (bottom right)
#define ENCC_PINA ((PIND >> 4) & 1)
#define ENCC_PINB ((PIND >> 6) & 1)

//Encoder 4 (Top left)
#define ENCD_PINB ((PINF >> 4) & 1)
#define ENCD_PINA ((PINF >> 5) & 1)

// Encoder 5 (middle left)
#define ENCE_PINA ((PINF >> 6) & 1)
#define ENCE_PINB ((PINF >> 7) & 1)

// Encoder 6
#define ENCF_PINA ((PINB >> 6) & 1)
#define ENCF_PINB ((PINB >> 5) & 1)

#define ENCODER_TIMEOUT_COUNT 5
#define DEBUG 1
//#define DEBUG_STATE 
void updateStates(uint8_t enc);
void sendKeyAction(uint8_t enc, uint8_t dir);
uint8_t readEncoder(uint8_t encNum, uint8_t pinNum);