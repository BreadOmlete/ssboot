/*
 * SSBoot - STM32 SPI Bootloader for RPI robot
 *
 * Main project file
 *
 * Author: Krzysztof Dziuba <krzysztof.dziuba@gmail.com>
 * License: Simplified BSD License (see README.md)
*/

#include "board.h"

int main()
{
	board_init();

	// GPIOC14 10MHz, output push-pull
	GPIOC->CRH &= ~(GPIO_CRH_MODE14 | GPIO_CRH_CNF14);
	GPIOC->CRH |= GPIO_CRH_MODE14_0;


	while(1) {
		GPIOC->BRR |= GPIO_BSRR_BS14;
		delayms(1000);
		GPIOC->BSRR |= GPIO_BSRR_BS14;
		delayms(1000);
	}

	return 0;
}
