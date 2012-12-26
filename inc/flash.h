/*
 * SSBoot - STM32 Serial Bootloader for RPI robot
 *
 * General flash programming functions. Implementation should be board specific.
 *
 * Author: Krzysztof Dziuba <krzysztof.dziuba@gmail.com>
 * License: Simplified BSD License (see README.md)
*/

#ifndef FLASH_H_
#define FLASH_H_

typedef enum {
	FLASH_OK,
	FLASH_ERR_UNLOCK,
	FLASH_ERR_ERASE,
	FLASH_ERR_PROGRAM,
} FLASH_ERR;


/* Return size of flash sector */
FLASH_ERR flash_sector_size();

/* Erase flash memory sector
 * address - any address inside sector to erase
 */
FLASH_ERR flash_erase_sector(unsigned int address);

/* Program flash memory
 * address - start address in flash memory
 * data - data to program
 * len - length of data in bytes
 */
FLASH_ERR flash_write_sector(unsigned int address, unsigned short *data, int len);



#endif /* FLASH_H_ */
