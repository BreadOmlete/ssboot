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
#include "flash.h"

volatile unsigned int _delay_counter;


void board_init()
{
	// AHB, APB1, APB2 clock not divided
	RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_USART1EN;

	// Remap USART1
	AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;

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
COMM_ERR comm_init()
{
	// TX - PB6, RX - PB7
	// GPIOB6 mode alternative push-pull, 50MHz
	// GPIOB7 mode floating input
	GPIOB->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_CNF6_0 | GPIO_CRL_MODE6_1 | GPIO_CRL_MODE6_0);
	GPIOB->CRL &= ~(GPIO_CRL_CNF7_1 | GPIO_CRL_CNF7_0 | GPIO_CRL_MODE7_1 | GPIO_CRL_MODE7_0);
	GPIOB->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1 | GPIO_CRL_CNF7_0;
	// Configure UART1 115200, 8N1
	USART1->BRR = 0x045;
	USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;

	return COMM_OK;
}

COMM_ERR comm_send(char *buf, char len)
{
	while(--len) {
		while(!(USART1->SR & USART_SR_TXE));
		USART1->DR = *buf++;
	}

	return COMM_OK;
}

COMM_ERR comm_recv(char *buf, char *len, int timeout)
{
	int i = 0;
	_delay_counter = timeout;
	SysTick->CTRL = SysTick_CTRL_ENABLE | SysTick_CTRL_TICKINT;

	while(i < *len) {
		while(!(USART1->SR & USART_SR_RXNE) && _delay_counter);
		if (USART1->SR & USART_SR_RXNE) {
			buf[i++] = USART1->DR & 0xff;
			_delay_counter = timeout;
		} else {
			*len = i;
			return COMM_ERR_TIMEOUT;
		}
	}

	return COMM_ERR_FULL;
}

FLASH_ERR flash_erase_sector(unsigned int address)
{
	// check if locked:
	if (FLASH->CR & FLASH_CR_LOCK) {
		FLASH->KEYR = 0x45670123;
		FLASH->KEYR = 0xCDEF89AB;

		if (FLASH->CR & FLASH_CR_LOCK)
			return FLASH_ERR_UNLOCK;
	}

	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = address;
	FLASH->CR |= FLASH_CR_STRT;

	while(FLASH->SR & FLASH_SR_BSY);

	FLASH->CR &= ~(FLASH_CR_STRT | FLASH_CR_PER);
	FLASH->SR |= FLASH_SR_EOP;

	return FLASH_OK;

}

FLASH_ERR flash_write_sector(unsigned int address, unsigned short *data, int len)
{
	volatile unsigned short *addr = (unsigned short *)(address);

	while(len) {
		// check if locked:
		if (FLASH->CR & FLASH_CR_LOCK) {
			FLASH->KEYR = 0x45670123;
			FLASH->KEYR = 0xCDEF89AB;

			if (FLASH->CR & FLASH_CR_LOCK)
				return FLASH_ERR_UNLOCK;
		}

		while(FLASH->SR & FLASH_SR_BSY);

		if (!(FLASH->CR & FLASH_CR_PG))
			FLASH->CR |= FLASH_CR_PG;

		*addr = *data;
		while(FLASH->SR & FLASH_SR_BSY);
		if (*addr != *data) {
			FLASH->CR &= ~FLASH_CR_PG;
			return FLASH_ERR_PROGRAM;
		}
		addr += 1;
		data += 1;
		len -= 2;
	}

	FLASH->CR &= ~FLASH_CR_PG;

	return FLASH_OK;
}
