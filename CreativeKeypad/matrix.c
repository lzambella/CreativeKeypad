/*
Copyright 2020 Luke Zambella

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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "debug.h"
#include "timer.h"
#include "matrix.h"
#include <util/delay.h>
#include "encoder.h"
#include "timer1.h"

#ifndef DEBOUNCE
# define DEBOUNCE	5
#endif
#define NUM_ROWS 3
/* matrix state(1:on, 0:off) */
// The matrix array contains binary data for each cell relating to that particular row
// so row 1 could have 0b0110 in matrix[0] meaning columns 1 and 4 have read something
static matrix_row_t matrix[MATRIX_ROWS];
static int8_t * encoderRes;
static uint8_t read_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

// Variable to store the current row
uint8_t curRow = 0;
/**
 * Variable that determines whether
 * the timer is waiting to settle high (1) or low (0)
 * When this is 1 we are waiting for the current row pin
 * to settle after being set to high otherwise
 * we are waiting for it to settle after being set to low
 */
uint8_t settleEdge = 1;

/**
 * Initialize the matrix by setting all the keys
 * Set the GPIO pins too
 */
void matrix_init(void)
{
    // Set all bits to low
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
    // initialize columns to normal input and rows to output
    // Actual switches use a pull up design with hardware debouncing
    // (0: LOW, 1: HIGH) when DDRx[n] == 1 or OUTPUT
    // (0: NORMAL, 1: PULLUP) when DDRx[n] == 0 or INPUT

    // Set the row pins to output
    DDRB |= (1 << 0);
    DDRB |= (1 << 1);
    DDRB |= (1 << 2);
    
    // Column pins are input
    // These should be set to normal read mode because of external pullup
    DDRB &= ~(1 << 3);
    DDRB &= ~(1 << 7);
    DDRD &= ~(1 << 0);
    DDRD &= ~(1 << 1);

    PORTB &= ~(1 << 3);
    PORTB &= ~(1 << 7);
    PORTD &= ~(1 << 0);
    PORTD &= ~(1 << 1);

    timer_clear();
    timer1_init();

    // Initialize the UART service
    // Pins D2(rx) and D3(tx)
    uart_init(SERIAL_UART_BAUD);
}

uint8_t matrix_scan(void)
{
    /** Check the status of the timer
     * If the timer count is greater than the threshold
     * then either read the columns or disable all rows
     * We need to let each row settle for a very long time
     * because using a timer ensures that its
     * nonblocking to reading the encoders
    */
   if (timer_read() > 8 && settleEdge == 1) {
        // Read the current column
        uint8_t cols = read_cols();
        // Set the current matrix row array cell to the column inputs
        matrix[curRow] = cols;

        // Disable all rows
        unselect_rows();
        // increment the next row or reset it
        curRow++;
        if (curRow >= NUM_ROWS)
            curRow = 0;
        // Now set the settle timer to falling
        settleEdge = 0;
        timer_clear();
   } else if (timer_read() > 8 && settleEdge == 0) {
        // here we wait approx 6ms before enabling the next row
        // When the timer fires with settleEdge = 0 
        // select the next row (which was incremented from before)
        select_row(curRow);

        // set the edge timer to one
        settleEdge = 1;
        // reset timer
        timer_clear();
   }
    // Check the encoders
    updateStates(0);
    updateStates(1);
    updateStates(2);
    updateStates(3);
    updateStates(4);
    updateStates(5);
    return 1;
}

inline
/*
* Get a single row in the matrix array
* Each row contains bits that represent the columns in the matrix
* So row 1 may have 0110 for col[3:0]
*/
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

inline
/*
* Reads a single bit from the desired column
* Return 1 if input HIGH
* Return 0 if input LOW
*/
static uint8_t read_cols()
{
    // Get the state of the columns
    // Remember 0 means that the column has been pressed
    uint8_t c1 = (~PINB & (1 << 3)) >> 3;
    uint8_t c2 = (~PINB & (1 << 7)) >> 7;

    uint8_t c3 = (~PIND & (1 << 0)) >> 0;
    uint8_t c4 = (~PIND & (1 << 1)) >> 1;

    // Make a continuous integer of the inputs
    uint8_t C = c1 << 0;
    C = C | c2 << 1;
    C = C | c3 << 2;
    C = C | c4 << 3;
    return C;

}

inline
/*
* Deselects rows by writing a LOW to all the row pins
* Have to make sure the input pins dont get messed up
*/
static void unselect_rows(void)
{
    // Quick hack
    // sets the read mode to normal on the col pins each call
    // which is what it defaults too anyway
    // The lower three bits of port B are the row pins
    PORTB &= ~(1 << 0);
    PORTB &= ~(1 << 1);
    PORTB &= ~(1 << 2);
}

inline
/*
* Selects a row by writing a HIGH to the desired pin
*/
static void select_row(uint8_t row)
{
    switch (row) {
        // Row 1 (pin B0)
        case 0:
            PORTB = (1<<0);
            break;
        case 1:
        // Row 2 (pin B1)
            PORTB = (1<<1);
            break;
        case 2:
        // Row 3 (Pin B2)
            PORTB = (1<<2);
            break;
    }
}
