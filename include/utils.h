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
#include <gd32vf103.h>
/* Sleep for t microseconds                                   */
void usleep(uint32_t t);
/* Unsigned integers to base 10 ASCII                         */
void u8toa(uint8_t n, char *dest);
void u16toa(uint16_t n, char *dest);
void u32toa(uint32_t n, char *dest);