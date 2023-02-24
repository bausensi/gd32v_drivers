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
#define       BYJ48_MIN_DELAY 15000
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

byj48_t byj48_init(uint32_t gpio_periph, uint32_t config) {
    byj48_t result = ((uint64_t)gpio_periph << 32) | config;
    gpio_init(gpio_periph, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, 0x0F << (config & 0x0F));
    GPIO_BC(gpio_periph) = 0x0F << (config & 0x0F); 

    return result;
}

static uint32_t i = 0;
void byj48_step(byj48_t *target, int32_t steps) {
    uint32_t periph  = (*target >> 32);
    uint8_t  gpio_offset = (*target & 0x0F);
    uint32_t reverse = 0;
    if(steps < 0) {
        reverse = 1;
        steps = -steps;
    }
    for(int32_t j = 0; j < steps; j++) {
        GPIO_BC(periph)  = (0x0F << gpio_offset); 
        GPIO_BOP(periph) = (reverse) ?
            lut_step_table[BYJ48_STEPS - i] << gpio_offset :
            lut_step_table[i] << gpio_offset;
        i++;
        i %= BYJ48_STEPS;
        usleep(BYJ48_MIN_DELAY);
    }
    GPIO_BC(periph)  = 0x0F << gpio_offset; 
}

#endif