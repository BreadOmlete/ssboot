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
#include "flash.h"

#define BOOT_TIMEOUT_MS 2000
#define BUFFER_LEN 1024
char buf[BUFFER_LEN];


int main()
{
	COMM_ERR comm_status;
	int len = BUFFER_LEN;

	board_init();
	comm_init();

	comm_send(":SSBOOT", 7);
	comm_status = comm_recv(buf, &len, BOOT_TIMEOUT_MS);

	if (comm_status == COMM_ERR_TIMEOUT || buf[0] != 'i')
	{
		comm_send("NOK", 3);
		while(1);
	}

	comm_send("OK", 2);


	while(1);

	return 0;
}
