/**
COPYRIGHT 2020 LUKE ZAMBELLA
Encoder mapping header file

Exposes variables that define the keymapping of what each encoder action 
should do

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
#include "actionmap.h"
#include "config.h"

action_t ENCODERMAP_CLK[ENCODER_COUNT];
action_t ENCODERMAP_CCLK[ENCODER_COUNT];