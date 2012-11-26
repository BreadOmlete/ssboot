/*
 * SSBoot - STM32 SPI Bootloader for RPI robot
 *
 * Main project file
 *
 * Author: Krzysztof Dziuba <krzysztof.dziuba@gmail.com>
 * License: Simplified BSD License (see README.md)
*/

#include "board.h"

unsigned char data_buffer[1024];


int main()
{
	volatile int i = 0;

	while(1)
	{
		i++;
	}

	return 0;
}
