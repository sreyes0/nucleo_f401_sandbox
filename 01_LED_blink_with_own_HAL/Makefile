TARGET = blink

# Environment
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

MCU = cortex-m4

# Includes
DRIVER_INCLUDES = \
    -IDrivers/CMSIS/Include \
    -IDrivers/CMSIS/Device/ST/STM32F4xx/Include

CORE_INCLUDES = \
    -IInc

# Source files
SRC = \
    Src/button.c \
    Src/led.c \
    Src/main.c \
    Src/syscalls.c \
    Src/sysmem.c

ASM = Startup/startup_stm32f401retx.s

# Compiler flags
CFLAGS = \
    -mcpu=$(MCU) \
    -mthumb \
    -O0 \
    -g \
    -Wall \
	-Wl,-Map=blink.map  \
	-MMD \
	-MP

CFLAGS += \
    -DSTM32F401xE

CFLAGS += \
    $(DRIVER_INCLUDES) \
    $(CORE_INCLUDES) 

# Create list of objects to compile
OBJS = $(SRC:.c=.o) $(ASM:.s=.o)
DEPS = $(OBJS:.o=.d)

# Link to FLASH, use RAM for debugging purposes
LDFLAGS = -T STM32F401RETX_FLASH.ld

# Commands
all: $(TARGET).bin $(TARGET).list

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(TARGET).list: $(TARGET).elf
	$(OBJDUMP) -d -S $< > $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# Flash device
flash: $(TARGET).bin
	st-flash write $< 0x08000000
	st-flash reset

# Erase device
erase:
	st-flash erase

# Clean workspace
clean: 
	rm -f *.map *.elf *.bin *.list $(OBJS) $(DEPS)

# Print all targeted objects
list_objs:
	find . -type f -name "*.o"
