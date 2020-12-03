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

FILENAME: timer2.h
DESCRIPTION: Header file for AVR's timer2 controls. This timer is responsible
for timing out the encoders if no acceptable state has been reached and no 
input can be derived from them.

timer2 is a built in AVR timer that uses 8-bit PWM. This timer was chosen
because timer0 was already in use and timer1 is too precise.
 */

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile uint32_t timerCount;
/**
 * Sets up timer2 
 */
void timer1_init(void);
/**
 * Resets the timer counter to 0
 */ 
void timer1_clear(void);

/**
 * Reads the current counter value as a 32-bit unsigned integer
 */
uint32_t timer1_read32(void);
