/**
COPYRIGHT 2020 LUKE ZAMBELLA
timer2 handler

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

FILENAME: timer1.c
DESCRIPTION: timer1.h implementation code.
 */

#include "timer1.h"

// timer counter
volatile uint32_t timerCount = 0;

void timer1_init(void) {
    // set counter
    OCR1A = 63;

    // set to CTC
    TCCR1A = 0x02;

    // Set the prescalar to 256
    // ORR the first 3 bits to the correct value
    TCCR1B |= 0x04;

    // Set interrupt on compare match
    TIMSK1 |= (1 << OCIE1A);
    
    // Interrupts are already enabled
    sei();
}

uint32_t timer1_read32(void) {
    return timerCount;    
}

void timer1_clear(void) {
    timerCount = 0;
}


ISR(TIMER1_COMPA_vect) {
    timerCount++;
}