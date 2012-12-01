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
	// AHB, APB1, APB2 clock not divided
	RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

	// GPIOC14 10MHz, output push-pull
	GPIOC->CRH &= ~(GPIO_CRH_MODE14 | GPIO_CRH_CNF14);
	GPIOC->CRH |= GPIO_CRH_MODE14_0;

	GPIOC->BSRR |= GPIO_BSRR_BS14;

	while(1);

	return 0;
}
