/*
 * SSBoot - STM32 SPI Bootloader for RPI robot
 *
 * Implementation of low-level communication channel using SPI peripherial.
 *
 * Author: Krzysztof Dziuba <krzysztof.dziuba@gmail.com>
 * License: Simplified BSD License (see README.md)
*/

#include "board.h"
#include "comm.h"

volatile unsigned int _delay_counter;


void board_init()
{
	// AHB, APB1, APB2 clock not divided
	RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

	/* setup SysTick for 1ms tick */
	SysTick->LOAD = 1000;

}

void SysTick_Handler()
{
	if(--_delay_counter == 0)
		SysTick->CTRL = 0;
}

void delayms(int time)
{
	_delay_counter = time;
	SysTick->CTRL = SysTick_CTRL_ENABLE | SysTick_CTRL_TICKINT;

	while(_delay_counter);
}

/* From comm.h */
ERR comm_init()
{

	return ERR_OK;
}

ERR comm_send(char *buf, char len)
{

	return ERR_OK;
}

ERR comm_recv(char *buf, char *len)
{

	return ERR_OK;
}
