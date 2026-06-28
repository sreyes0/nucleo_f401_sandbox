/*
 * button.h
 *
 *  Created on: 8 Feb 2026
 *      Author: Jimothy
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdint.h>

extern volatile uint32_t tick;

typedef enum {
	BUTTON_IDLE,
	BUTTON_PRESS,
	BUTTON_LONG_PRESS,
	BUTTON_RELEASE
} ButtonEvent;

void button_init();
ButtonEvent button_get_event();


#endif /* BUTTON_H_ */
