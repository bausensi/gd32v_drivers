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
#include "byj48.h"
#include "utils.h"
#include "config.h"

#ifdef ENABLE_BYJ48

#if   defined(BYJ48_DRIVE_HALFSTEP)

#define     BYJ48_STEPS     8
#define     BYJ48_MIN_DELAY 1000
static const uint8_t lut_step_table[8] = {
    0b00001001,
    0b00000001,
    0b00000011,
    0b00000010,
    0b00000110,
    0b00000100,
    0b00001100,
    0b00001000,
};
#elif defined(BYJ48_DRIVE_FULLSTEP)

#define       BYJ48_STEPS     4
#define       BYJ48_MIN_DELAY 2000
static const uint8_t lut_step_table[4] = {
    0b00001001,
    0b00000011,
    0b00000110,
    0b00001100,
};

#elif defined(BYJ48_DRIVE_WAVE)

#define       BYJ48_STEPS     4
#define       BYJ48_MIN_DELAY 2000
static const uint8_t lut_step_table[4] = {
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
};
#else

#error "Please choose a valid motor configuration"
#endif

void byj48_init(uint32_t gpio_periph) {
    gpio_init(gpio_periph, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, 0x0F << BYJ48_GPIO_OFFSET);
    GPIO_BC(gpio_periph) = 0xF0 << BYJ48_GPIO_OFFSET; 
}

static uint32_t i = 0;
void byj48_step(uint32_t gpio_periph, int32_t steps) {
    uint32_t reverse = 0;
    if(steps < 0) {
        reverse = 1;
        steps = -steps;
    }
    for(int32_t j = 0; j < steps; j++) {
        GPIO_BC(gpio_periph)  = (0x0F << BYJ48_GPIO_OFFSET); 
        GPIO_BOP(gpio_periph) = (reverse) ?
            lut_step_table[BYJ48_STEPS - i] << BYJ48_GPIO_OFFSET :
            lut_step_table[i] << BYJ48_GPIO_OFFSET;
        i++;
        i %= BYJ48_STEPS;
        usleep(BYJ48_MIN_DELAY);
    }
    GPIO_BC(gpio_periph)  = 0xFF00; 
}

#endif