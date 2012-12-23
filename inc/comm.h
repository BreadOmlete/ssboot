/*
 * SSBoot - STM32 SPI Bootloader for RPI robot
 *
 * General communication functions. Implementation should be board specific.
 *
 * Author: Krzysztof Dziuba <krzysztof.dziuba@gmail.com>
 * License: Simplified BSD License (see README.md)
*/

#ifndef COMM_H_
#define COMM_H_

typedef enum
{
	ERR_OK,
	ERR_FULL,
	ERR_TIMEOUT,
} ERR;


/*
 * Initialize communication channel.
 * Return: error code.
 */
ERR comm_init();

/*
 * Send buffer buff of size len to the remote.
 * Return: error code.
 */
ERR comm_send(char *buf, char len);

/*
 * Receive data from the remote, store it to buffer buf, store length of
 * received data to len. Leave function after timeout miliseconds.
 * Return: error code.
 */
ERR comm_recv(char *buf, char *len, int timeout);



#endif /* COMM_H_ */
