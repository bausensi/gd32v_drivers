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
/* Send low byte of data to display, LSB of high byte selects data/cmd  */
void hd44780_write(uint32_t gpio_periph, uint16_t data);
/* Init HD44780-like display in 4-bit mode  */
void hd44780_init(uint32_t gpio_periph);
/* Print a NUL terminated string to display */
void hd44780_print(uint32_t gpio_periph, const char *str);
/* Write one character to display           */
#define hd44780_write_char(gpio_periph, c)    hd44780_write(gpio_periph, BIT(8) | c    )
/* Jump to DDRAM address                    */
#define hd44780_ddram_goto(gpio_periph, addr) hd44780_write(gpio_periph, BIT(7) | addr )