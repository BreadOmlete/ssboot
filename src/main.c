/*
 * SSBoot - STM32 SPI Bootloader for RPI robot
 *
 * Main project file
 *
 * Author: Krzysztof Dziuba <krzysztof.dziuba@gmail.com>
 * License: Simplified BSD License (see README.md)
*/

#include "board.h"
#include "comm.h"

int strlen(char *s)
{
	int i = 0;
	while(*s++ != 0)
		i++;

	return i+1;
}


int main()
{
	char *s = ":SSBOOT ";
	char r[16];
	int status;
	char len = 4;
	board_init();
	comm_init();


	flash_erase_sector(0x08000400);
	flash_write_sector(0x08000400, (unsigned short *)s, 8);

	comm_send(s, strlen(s));
	status = comm_recv(r, &len, 2000);

	if (status == ERR_TIMEOUT)
		comm_send("  timeout", 10);
	else
		comm_send("  len", 6);


	while(1);

	return 0;
}
