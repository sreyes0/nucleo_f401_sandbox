/*
 * time.h
 *
 * Created on: 28 Jun 2026
 *     Author: Jimothy
 *
 * The time module is an abstraction for the clock of the system to offer an
 * interface to manage periodic tasks, timeouts, delays, etc.
 */


#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>


void timer_init();

uint32_t get_current_time_ms();


#endif /* TIMER_H_ */
