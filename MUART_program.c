/*
 * Name: MUART_program.c
 * Author: Mahmoud Adel
 * Description: This file contains logical implementation of UART module
 * Version: v1.0
 * */

/************************************************************************************************/
/*                                             Includes                                         */
/************************************************************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MUART_private.h"
#include "MUART_interface.h"

/************************************************************************************************/
/*                                        Functions' definitions                                */
/************************************************************************************************/

void muart_init(u16_t au16_baudRate)
{
	/*Enable Tx and Rx pins*/
	MUART_UCSRB = 0x18;

	/*Selecting asynchronous mode, no parity bit, 1-stop bit and 8-bits character size*/
	MUART_UCSRC = 0x86;

	/*Getting the low byte in UBRRL*/
	MUART_UBRRL = (u8_t)au16_baudRate;

	/*Getting the low byte in UBRRL*/
	MUART_UBRRH = (u8_t)(au16_baudRate >> 8);

	/*Return from this function*/
	return;
}

void muart_sendByte(u8_t au8_dataByte)
{
	/*Checking whether the data register is empty or not*/
	if(GET_BIT(MUART_UCSRA, 5))
	{
		/*Sending the data byte*/
		MUART_UDR = au8_dataByte;

		/*Waiting until the data is transmitted through the Tx pin*/
		while(!GET_BIT(MUART_UCSRA, 6));

		/*Clearing transmission flag*/
		SET_BIT(MUART_UCSRA, 6);
	}
	else
	{
		/*Do nothing*/
	}

	/*Return from this function*/
	return;
}

void muart_recvByte(u8_t* pu8_dataByte)
{
	/*Checking whether a new data has been received or not*/
	if(GET_BIT(MUART_UCSRA, 7))
	{
		/*Receiving the new data byte*/
		*pu8_dataByte = MUART_UDR;
	}
	else
	{
		/*Do nothing*/
	}

	/*Return from this function*/
	return;
}

void muart_sendStream(u8_t* pu8_dataBytes, u8_t au8_dataSize)
{
	/*Looping over data size*/
	while(au8_dataSize--)
	{
		/*Sending byte by byte*/
		muart_sendByte(*pu8_dataBytes);

		/*Moving to the next byte*/
		pu8_dataBytes++;
	}

	/*Return from this function*/
	return;
}
