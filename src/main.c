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
#include "utils.h"
#include "config.h"

const char *str = "Uptime XXXXXX";
int main(void) {
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    
    hd44780_init(GPIOA);
    byj48_init(GPIOB);
    
    hd44780_print(GPIOA, str);
    
    uint8_t runtime[2] = {0};
    char buf[4];
    char c = ':';
    while(1) {
        runtime[0]++;
        if(runtime[0] == 60) {
            runtime[0] = 0;
            runtime[1]++;
        }
        
        c = (runtime[0] & 1) ? ':' : ' ';
        
        u8toa(runtime[1], buf);
        hd44780_ddram_goto(GPIOA, 7);
        hd44780_print(GPIOA, buf);
        u8toa(runtime[0], buf);
        hd44780_ddram_goto(GPIOA, 10);
        hd44780_print(GPIOA, buf);
        
        hd44780_ddram_goto(GPIOA, 10);
        hd44780_write_char(GPIOA, c);
        
        byj48_step(GPIOB, 69); 
        usleep(1000000);
    }
}