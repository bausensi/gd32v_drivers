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
#include "utils.h"

void usleep(uint32_t t) {
    for(uint32_t i = 0; i < t; i++) {
        uint64_t start_mtime, delta_mtime;
        uint64_t tmp = get_timer_value();
        do {
            start_mtime = get_timer_value();
        } while(start_mtime == tmp);
        
        do {
            delta_mtime = get_timer_value() - start_mtime;
        } while(delta_mtime < ( (SystemCoreClock / 4000000) ));
    }
}
void u8toa(uint8_t n, char *dest) {
    dest[3] = '\0';
    uint8_t  t = n;
    uint32_t i = 0;
    do {
        dest[2 - i++] = (t > 0) ? '0' + (t % 10) : '0';
        t /= 10; 
    } while (i < 3);
}
void u16toa(uint16_t n, char *dest) {
    dest[5] = '\0';
    uint16_t t = n;
    uint32_t i = 0;
    do {
        dest[4 - i++] = (t > 0) ? '0' + (t % 10) : '0';
        t /= 10; 
    } while (i < 5);
}
void u32toa(uint32_t n, char *dest) {
    dest[10] = '\0';
    uint32_t t = n;
    uint32_t i = 0;
    do {
        dest[9 - i++] = (t > 0) ? '0' + (t % 10) : '0';
        t /= 10; 
    } while (i < 10);
}