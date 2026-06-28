/*
 * led.h
 *
 *  Created on: 8 Feb 2026
 *      Author: Jimothy
 */

#ifndef LED_H_
#define LED_H_

#include <stdint.h>

extern volatile uint32_t tick;

typedef enum {
	LED_ON,
	LED_OFF
} LedState;

void led_init();
void led_set_state(LedState state);
void led_toggle();

#endif /* LED_H_ */
