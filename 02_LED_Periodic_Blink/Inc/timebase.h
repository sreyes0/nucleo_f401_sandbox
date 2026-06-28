/*
 * The time module is an abstraction for the clock of the system to offer an
 * interface to manage periodic tasks, timeouts, delays, etc.
 */


#ifndef TIMEBASE_H_
#define TIMEBASE_H_

#include <stdint.h>

typedef struct {
    uint32_t start;
    uint32_t period;
} timer_t;


void timebase_init();

uint32_t get_current_time_ms();

bool period_elapsed(const timer_t *timer);


#endif /* TIMEBASE_H_ */
