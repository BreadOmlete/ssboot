########################################################################
# Board specific Makefile for SSBoot
# Author: Krzysztof Dziuba <krzysztof.dziuba@gmail.com>
########################################################################

LINKER_SCRIPT = linker_ram.ld
COPTS = -DSTM32F10X_LD_VL -mthumb -mthumb-interwork -mcpu=cortex-m3
BOARD_OBJECTS = system_stm32f10x.o startup.o board.o
