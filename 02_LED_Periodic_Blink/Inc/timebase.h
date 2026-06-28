/*
 * The time module is an abstraction for the clock of the system to offer an
 * interface to manage periodic tasks, timeouts, delays, etc.
 */


#ifndef TIMEBASE_H_
#define TIMEBASE_H_

#include <stdint.h>


void timebase_init();

uint32_t get_current_time_ms();


#endif /* TIMEBASE_H_ */
