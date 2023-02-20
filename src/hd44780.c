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
#include "hd44780.h"
#include "utils.h"
#include "config.h"

#ifdef ENABLE_HD44780

#if     defined(HD44780_TYPE_1602) || defined(HD44780_TYPE_2002)

#define HD44780_LINES 2
static const uint8_t  lut_ddram_lines[] = { 0x00, 0x40 };

#elif   defined(HD44780_TYPE_1604)

#define HD44780_LINES 4
static const uint8_t  lut_ddram_lines[] = { 0x00, 0x40, 0x10, 0x50 };

#elif   defined(HD44780_TYPE_2004)

#define HD44780_LINES 4
static const uint8_t  lut_ddram_lines[] = { 0x00, 0x40, 0x14, 0x54 };
#else

#error "Please specify a display configuration."
#endif

void hd44780_pulse_enable(uint32_t gpio_periph) {
    GPIO_BC(gpio_periph)  = BIT(1) << HD44780_GPIO_OFFSET;
    usleep(1);
    GPIO_BOP(gpio_periph) = BIT(1) << HD44780_GPIO_OFFSET;
    usleep(1);
    GPIO_BC(gpio_periph)  = BIT(1) << HD44780_GPIO_OFFSET;
    usleep(48);
}
void hd44780_write(uint32_t gpio_periph, uint16_t data) {
    /* Bit 0 controls the register select line.          */
    GPIO_BC(gpio_periph)  = BIT(0) << HD44780_GPIO_OFFSET;
    GPIO_BOP(gpio_periph) = (data & BIT(8)) ? (BIT(0) << HD44780_GPIO_OFFSET) : 0;
    
    /* 0x3C: bitmask of the D4-D7 lines in the GPIO port */
    GPIO_BC(gpio_periph)  = 0x3C << HD44780_GPIO_OFFSET;
    GPIO_BOP(gpio_periph) = (data)      & (0x3C << HD44780_GPIO_OFFSET);
    hd44780_pulse_enable(gpio_periph);
    GPIO_BC(gpio_periph)  = 0x3C << HD44780_GPIO_OFFSET;
    GPIO_BOP(gpio_periph) = (data << 4) & (0x3C << HD44780_GPIO_OFFSET);
    hd44780_pulse_enable(gpio_periph);

    usleep(2000);
}
void hd44780_init(uint32_t gpio_periph) {

    gpio_init(gpio_periph, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, 0x3F << HD44780_GPIO_OFFSET);
    GPIO_BC(gpio_periph) = 0x3F << HD44780_GPIO_OFFSET;
    usleep(50000);

    GPIO_BOP(gpio_periph) = 0b001100 << HD44780_GPIO_OFFSET;
    hd44780_pulse_enable(gpio_periph);
    usleep(5000);
    hd44780_pulse_enable(gpio_periph);
    usleep(100);
    
    GPIO_BC(gpio_periph)  = 0x3F << HD44780_GPIO_OFFSET;
    GPIO_BOP(gpio_periph) = 0b001000 << HD44780_GPIO_OFFSET;
    hd44780_pulse_enable(gpio_periph);
    usleep(100);
    
    /* EMS I, S    */
    hd44780_write(gpio_periph, 0x06);
    /* DON D, C, B */
    hd44780_write(gpio_periph, 0x0F);
    /* DON D, 0, 0 */
    hd44780_write(gpio_periph, 0x0C);
    /* CLR         */
    hd44780_write(gpio_periph, 1);
}
void hd44780_print(uint32_t gpio_periph, const char *str) {
    uint32_t line = 0;
    for(uint32_t i = 0; str[i] != '\0'; i++) {
        if(str[i] == '\n') {
            line++;
            line %= HD44780_LINES;
            hd44780_write(GPIOA, BIT(7) | lut_ddram_lines[line]);
        }
        else {
            hd44780_write(GPIOA, str[i] | BIT(8));
        }
    }
}

#endif