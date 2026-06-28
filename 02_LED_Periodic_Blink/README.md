Periodic LED blink with timer module
====================================

Add an abstracted interface to interact with the devices clock. It should allow
us to do periodic tasks, implement delays and timeouts, and of course access
the device's time.

Improvements
------------
* We decoupled main.c from the stm32f401xe.h header since it doesn't handle the
  SysTick interrupt anymore
* button.c does not need to know about what source for the clock is used. It
  only cares about the time
* It's dead simple to change the source of the time now in timebase.h


