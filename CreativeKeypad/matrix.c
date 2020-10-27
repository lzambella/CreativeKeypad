/*
Copyright 2017 Jun Wako <wakojun@gmail.com>

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


#ifndef DEBOUNCE
# define DEBOUNCE	5
#endif
/* matrix state(1:on, 0:off) */
// The matrix array contains binary data for each cell relating to that particular row
// so row 1 could have 0b0110 in matrix[0] meaning columns 1 and 4 have read something
static matrix_row_t matrix[MATRIX_ROWS];

static uint8_t read_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);


/**
 * Initialize the matrix by setting all the keys
 * Set the GPIO pins too
 */
void matrix_init(void)
{
    // Set all bits to high for open switch
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = ~0;
    }
    // initialize columns to normal input and rows to output
    // Actual switches use a pull up design with hardware debouncing
    // (0: LOW, 1: HIGH) when DDRx[n] == 1
    // (0: NORMAL, 1: PULLUP) when DDRx[n] == 0
    DDRB = 0b01110111;
    DDRD = 0b11111100;
    PORTB = 0b00000000;
    PORTD = 0b00000000;
    print("Init. matrix\n");
}

uint8_t matrix_scan(void)
{
    // Iterate over each row
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        _delay_ms(5);
        // Read the current column
        uint8_t cols = read_cols();
        // Set the current matrix row array cell to the column inputs
        matrix[i] = cols;
        // Set all rows to zero
        unselect_rows();
        _delay_ms(5);
    }
    return 1;
}

inline
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
    print("Col 1: "); phex(c1); print("\n");
    print("Col 2: "); phex(c2); print("\n");
    print("Col 3: "); phex(c3); print("\n");
    print("Col 4: "); phex(c4); print("\n");
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
    PORTB = 0b00000000;
}

inline
/*
* Selects a row by writing a HIGH to the desired pin
*/
static void select_row(uint8_t row)
{
    switch (row) {
        case 0:
            PORTB |= (1<<0);
            break;
        case 1:
            PORTB |= (1<<1);
            break;
        case 2:
            PORTB |= (1<<2);
            break;
    }
}
