/*
 * HydraBus/HydraNFC
 *
 * Copyright (C) 2024 Nicolas Oberli
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "hydrabus.h"
#include "common.h"
#include "bsp_gpio.h"

uint8_t RGB_PATTERN[] = {0xff, 0xff, 0xff, 0x80, 0, 0, 0, 0, 0, 0x80, 0xff, 0xff};


inline void rgb_write_zero (void) 
{
	bsp_gpio_set(BSP_GPIO_PORTA, 4);
	DelayUs(1);
	bsp_gpio_clr(BSP_GPIO_PORTA, 4);
	DelayUs(5);
}

inline void rgb_write_one (void) 
{
	bsp_gpio_set(BSP_GPIO_PORTA, 4);
	DelayUs(1);
	bsp_gpio_clr(BSP_GPIO_PORTA, 4);
	DelayUs(2);
	bsp_gpio_set(BSP_GPIO_PORTA, 4);
	DelayUs(1);
	bsp_gpio_clr(BSP_GPIO_PORTA, 4);
	DelayUs(2);
}

inline void rgb_write_eos(void)
{
	bsp_gpio_clr(BSP_GPIO_PORTA, 4);
	// delay for 4x Tcycle (6ms each)
	DelayUs(24);
}

inline void rgb_write_u8(uint8_t data)
{
	uint8_t i;

	// data sent MSB first
	for(i = 0; i < 8; i++) {
		if( (data<<i) & 0x80 ){
			rgb_write_one();
		} else {
			rgb_write_zero();
		}
	}
}

bsp_status_t rgb_init(void)
{
	bsp_gpio_init(BSP_GPIO_PORTA, 3, MODE_CONFIG_DEV_GPIO_OUT_PUSHPULL, MODE_CONFIG_DEV_GPIO_NOPULL);

	return BSP_OK;
}

bsp_status_t rgb_set_color(uint8_t red, uint8_t green, uint8_t blue)
{
	// Start czcle meassurement
	rgb_write_zero();
	rgb_write_zero();

	// Send command
	rgb_write_u8(0x3A);
	rgb_write_u8(red);
	rgb_write_u8(green);
	rgb_write_u8(blue);

	// End transaction
	rgb_write_eos();

	return BSP_OK;
}

bsp_status_t rgb_rainbow(void)
{
	static uint8_t cycle = 0;
	uint8_t r = RGB_PATTERN[cycle % sizeof(RGB_PATTERN)];
	uint8_t g = RGB_PATTERN[(cycle+8) % sizeof(RGB_PATTERN)];
	uint8_t b = RGB_PATTERN[(cycle+4) % sizeof(RGB_PATTERN)];

	rgb_set_color(r, g, b);

	cycle++;
	cycle = cycle % sizeof(RGB_PATTERN);

	return BSP_OK;
}


