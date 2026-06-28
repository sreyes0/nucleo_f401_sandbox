/*
 * button.c
 *
 *  Created on: 8 Feb 2026
 *      Author: Jimothy
 */


#include "button.h"

#include "stm32f401xe.h"


#define DEBOUNCE_MS 20
#define LONG_PRESS_MS 2000

static volatile uint32_t t_last_edge = 0;
static volatile uint32_t t_press = 0;
static volatile uint32_t t_release = 0;
static volatile uint8_t e_press = 0;
static volatile uint8_t e_release = 0;


void EXTI15_10_IRQHandler(void) {
	// Handler is for EXTI 10 .. 15

	// Check for EXTI13
	if (EXTI->PR & EXTI_PR_PR13) {
		uint32_t now = tick;
		// Debouncing measure
		if ((now - t_last_edge) >= DEBOUNCE_MS) {
			t_last_edge = now;

			if (GPIOC->IDR & (1 << 13)) {
				// Button is released (button is active-low)
				e_release = 1;
				t_release = now;
			} else {
				// Button is pressed
				e_press = 1;
				t_press = now;
			}
		}

		EXTI->PR = EXTI_PR_PR13; // Clear bit programming to 1
	}
}


void button_init() {
	// Enable SYSCFG Clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// Connect to RCC
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// Enable GPIOC for PC13 (USER BUTTON) as pull-up input
	GPIOC->MODER &= ~(3 << (2 * 13));	// input
	GPIOC->PUPDR &= ~(3 << (2 * 13));   // pull-up
	GPIOC->PUPDR |= (1 << (2 * 13));

	// Setup ISR
	// Set to EXTI 13 on Port C
	SYSCFG->EXTICR[3] &= ~(0xF << 4);
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;

	// Activate interrupt for line 13
	EXTI->IMR |= EXTI_IMR_IM13;
	// Button press is high to low
	// enable rising (released event)
	EXTI->RTSR |= EXTI_RTSR_TR13;
	// enable falling (pressed event)
	EXTI->FTSR |= EXTI_FTSR_TR13;

	// CMSIS (ARM Cortex M4) functions
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	NVIC_SetPriority(EXTI15_10_IRQn, 2);
}


ButtonEvent button_get_event() {
	if (e_press) {
		e_press = 0;
		return BUTTON_PRESS;
	}

	if (e_release) {
		e_release = 0;
		if ((t_release - t_press) >= LONG_PRESS_MS) {
			return BUTTON_LONG_PRESS;
		}
		return BUTTON_RELEASE;
	}

	return BUTTON_IDLE;
}
