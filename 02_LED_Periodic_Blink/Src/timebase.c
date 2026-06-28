#include "timebase.h"

#include "stm32f401xe.h"

// Atomic if 32-bit for the Cortex M4 atomic,
// for 64-bit additional precautions necessary
volatile uint32_t tick = 0;


void SysTick_Handler(void) {
    tick++;
}

void timebase_init() {
    SysTick->LOAD = 16000 - 1;  // 1ms
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk
                  | SysTick_CTRL_TICKINT_Msk
                  | SysTick_CTRL_CLKSOURCE_Msk;
}

uint32_t get_current_time_ms() {
    return tick;
}
