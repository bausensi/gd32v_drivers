/*
    Copyright (C) 2023 Benjamín Ausensi
	This file is part of gd32v_drivers.
	gd32v_drivers is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the Free Software
	Foundation, either version 3 of the License, or (at your option) any later version.
	Foobar is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
	without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
	PURPOSE. See the GNU General Public License for more details. You should have
    received a copy of the GNU General Public License along with gd32v_drivers. If not,
    see <https://www.gnu.org/licenses/>. 
*/
#pragma once
#include <gd32vf103_gpio.h>

/* Config word:                                       */
/* LSB 0-3: GPIO offset, 4-5: drive configuration MSB */
typedef uint64_t byj48_t;

/* Init 28byj-48 stepper motor board */
/* GPIOs must be: IN1-4              */
byj48_t byj48_init(uint32_t gpio_periph, uint32_t config);
/* Move motor by n half/steps (configuration) */
/* Sign determines direction: positive is CW  */
void byj48_step(byj48_t *target, int32_t steps);