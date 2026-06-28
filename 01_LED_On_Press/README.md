LED blink with own HAL
======================

Bare-metal implementation of a program to turn on an LED with the press of
a button.

Next-Steps
----------
* Timebase module
    * debouncing
    * sensor polling
    * timeouts
    * scheduling
* UART logging
    * debug interface

Build
-----

* `make` to compile the source code.
* `make flash` to flash the connected device

Structure
---------

```
root
+-- Drivers
|   +-- CMSIS
|       +-- Device/ST/STM32F44xx
|       +-- Include
|           +-- core_cm4.h
+-- Inc
+-- Src
+-- Startup
|   +-- startup_stm32f401retx.s
+-- STM32F401RETX_FLASH.ld
+-- STM32F401RETX_RAM.ld

```

### Drivers
The `Drivers` directory contains the generic CMSIS Core layer as well as the
device (STM32F401) specific code. 

The CMISIS core is the standardized abstraction layer from ARM for the 
Cortex-M processor family. 

`core_cm4.h`
Contains definitions for registers, such as:
* Core registers
* NVIC registers
* SysTick
* MPU/FPU

For example:
```
typedef struct
{
    __IOM uint32_t CTRL;
    __IOM uint32_t LOAD;
    __IOM uint32_t VAL;
    __IOM uint32_t CALIB;
} SysTick_Type;
```
or
```
__STATIC_INLINE void __NVIC_EnableIRQ(IRQn_TYPE IRQn)
{
    // ...
}
```

### Inc & Src
Own code.

### Startup
The `startup_stm32f401retx.s` file describes the procedures between a reset and
entering `main()` and defines the devices' vector table.

*Vector table*

The vector table is what is loaded at the beginning of flash memory (normally
0x08000000).

On reset the Cortex-M4 loads the first entry of that memory (`_estack`) into
the Main Stock Pointer register. `_estack` is defined in the linker script and
maps to
```
_estack = ORIGIN(RAM) + LENGTH(RAM) # End of RAM, beginning of stack
```

It then jumps to the second word which contains `Reset_Handler` and starts
executing code. `Reset_Handler` is defined in assembly in the startup script.

`Reset_Handler` executes `SystemInit()`, prepares data regions and calls
`main()`, from which no return is expected.

The vector table contains also the positions of other core functions such as 
default interrupt handlers or the `SysTick_Handler`. Per default the vector
table points them to the `Default_Handler` (defined in the same file) unless 
they are overriden in the application.

This way when an interrupt occurs the NVIC looks in the vector table finds the
corresponding handle and jumps to the C function.

### STM32F401RETX_FLASH.ld
The linker consumes this file to glue all the binary files needed to run software on
the device.

Describes where to positions the different sections. For example
* `.isr_vector` : the vector table
* `.text` : function definitions
* `.rodata` : Read-only data (constants, strings)
all in flash. Or
* `.data` : to store values
in RAM. At start-up values in flash are copied to RAM.

### NVIC (Nested Vectored Interrupt Controller)
The `NVIC` registers sets bits to mark that an interrupt must be registered. Hardware-
assisted after each instruction the processor checks if an interrupt with high enough
priority was called.

The `NVIC` then looks in the vector table and jumps to the C definition of the 
function.
