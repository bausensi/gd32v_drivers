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

#define ENABLE_HD44780
#define ENABLE_BYJ48

/* HD44780 LCD driver settings            */
#define HD44780_GPIO_OFFSET 2
#define HD44780_TYPE_1602

/* 28BYJ-48 stepper motor driver settings */
#define BYJ48_GPIO_OFFSET    10
#define BYJ48_DRIVE_HALFSTEP