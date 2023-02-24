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
#include <gd32vf103_rcu.h>
#include <gd32vf103_gpio.h>
#include "hd44780.h"
#include "byj48.h"
#include "config.h"

int main(void) {
    byj48_t m1, m2;
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    m1 = byj48_init(GPIOB, 0x0A);
    m2 = byj48_init(GPIOA, 0x02);
    
    while(1) {
        byj48_step(&m1,  1024);
        usleep(1000000);
        byj48_step(&m2,   512);
        usleep(1000000);
        byj48_step(&m1, -1024);
        usleep(1000000);
        byj48_step(&m2,   512);
        usleep(1000000);
        byj48_step(&m1,  1024);
        usleep(1000000);
        byj48_step(&m2, -1024);
        usleep(1000000);
        byj48_step(&m1, -1024);
        usleep(1000000);
    }
}