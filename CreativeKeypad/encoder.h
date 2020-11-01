/**
 * Copyright 2020 Luke Zambella
 * 
 * Quick and Tiny encoder library
 * 
 */
#include <stdint.h>
#include <stdbool.h>

/// Define a variable to easily store the needed data efficiently
struct encoder {
    /// Value of Pin A
    uint8_t pinA;
    /// Value of Pin B
    uint8_t pinB;
};
/**
 * Teensy pin assignment 
 */
#define ENCA_PINA (PINC |= << 6)
#define ENCB_PINB (PINC |= << 7)

/**
 * Define some global variables.
 */

/// Delay for debouncing
#define BOUNCE_DELAY_US 10
/// Number of encoders on the device
#define ENCODER_COUNT 1

/// Stored value of the previous states of pin A
int8_t prevA[ENCODER_COUNT];    
/// Stored value of the preciouse states of pin B
int8_t prevB[ENCODER_COUNT];

/**
 * Library functions
 */

/**
 * Get the direction of an encoder was rotated
 * INPUT: pointer to an encoder struct
 * OUTPUT: -1 if rotated coutner clockwise, 1 if rotated clockwise, 0 otherwise
 */
int8_t getDirection(encoder * encInput);
void updateState()