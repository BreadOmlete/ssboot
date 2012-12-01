########################################################################
# Makefile for SSBoot
# Author: Krzysztof Dziuba <krzysztof.dziuba@gmail.com>
########################################################################

########################################################################
# Configuration options:
########################################################################

# Board name
BOARD = stm32f100c4t6

########################################################################
# All other:
########################################################################

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
LDFLAGS += -ffunction-sections -fdata-sections

B_PATH = board/$(BOARD)
B_OBJECTS = $(foreach obj, $(BOARD_OBJECTS), $(B_PATH)/$(obj))

OBJECTS = $(B_OBJECTS) src/CoreSupport/core_cm3.o src/main.o


all:	$(TARGET).elf $(TARGET).bin $(TARGET).hex $(TARGET).lst


$(TARGET).elf:	$(OBJECTS)
	@echo "Linking $@..."
	@$(CC) $(CFLAGS) $(OBJECTS) --output $@ $(LDFLAGS)

$(TARGET).bin: $(TARGET).elf
	@echo "Converting to $@..."
	@$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

$(TARGET).hex: $(TARGET).elf
	@echo "Converting to $@..."
	@$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET).hex

$(TARGET).lst: $(TARGET).elf
	@echo "Converting to $@..."
	@$(OBJDUMP) -D $(TARGET).elf > $(TARGET).lst

.c.o:
	@echo "Building $@..."
	@$(CC) -c $(CFLAGS) $< -o $@

.S.o:
	@echo "Building $@..."
	@$(CC) -c $(CFLAGS) $< -o $@
	
clean:
		@rm -f $(OBJECTS)
		@rm -f $(TARGET).elf $(TARGET).bin $(TARGET).hex $(TARGET).map $(TARGET).lst
		@echo "Cleaning done."
	
	
