/*
 * led.c
 *
 *  Created on: 8 Feb 2026
 *      Author: Jimothy
 */


#include "led.h"

#include "stm32f401xe.h"


void led_init() {
	// Enable GPIOA for PA5 (LED) as output
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &= ~(3 << (2 * 5));    // output
	GPIOA->MODER |= (1 << (2 * 5));
}


void led_set_state(LedState state) {
	switch (state) {
	case LED_ON:
		GPIOA->BSRR = (1 << 5);
		break;
	case LED_OFF:
		GPIOA->BSRR = (1 << (5 + 16));
		break;
	default:
		// not reachable
		break;
	}
}
