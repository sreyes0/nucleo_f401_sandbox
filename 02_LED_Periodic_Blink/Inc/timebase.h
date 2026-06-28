/*
 * The time module is an abstraction for the clock of the system to offer an
 * interface to manage periodic tasks, timeouts, delays, etc.
 */


#ifndef TIMEBASE_H_
#define TIMEBASE_H_

#include <stdint.h>

typedef struct {
    uint32_t start;
    uint32_t length;
} timer_t;


void timebase_init();

uint32_t get_current_time_ms();

void timer_start(timer_t *timer, const uint32_t length);

bool timer_expired(const timer_t *timer);


#endif /* TIMEBASE_H_ */
