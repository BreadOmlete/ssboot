########################################################################
# Makefile for SSBoot
# Author: Krzysztof Dziuba <krzysztof.dziuba@gmail.com>
########################################################################

########################################################################
# Configuration options:
########################################################################

# Board name
BOARD = stm32f100c4t6

include board/$(BOARD)/board.mk

# Output
TARGET = ssboot

# Compiler prefix
CC_PREFIX = arm-none-eabi

# Tools
CC = $(CC_PREFIX)-gcc
LD = $(CC_PREFIX)-ld
CXX = $(CC_PREFIX)-g++
OBJCOPY = $(CC_PREFIX)-objcopy
OBJDUMP = $(CC_PREFIX)-objdump

# Options
CFLAGS = -Iinc/ -Iinc/CoreSupport -Iboard/$(BOARD)/ -Wall -g3 -gdwarf-2 -O2 $(COPTS)
LDFLAGS = -T"board/$(BOARD)/$(LINKER_SCRIPT)" -nostartfiles -nodefaultlibs -nostdlib
LDFLAGS += -Wl,-Map=$(TARGET).map,--cref,--gc-sections $(COPTS) -g3 -gdwarf-2



OBJECTS = board/$(BOARD)/$(BOARD_OBJECTS) src/CoreSupport/core_cm3.o src/main.o board




all:	$(TARGET).elf $(TARGET).bin


$(TARGET).elf:	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) --output $@ $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

.S.o:
	$(CC) -c $(CFLAGS) $< -o $@
