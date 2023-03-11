/*
 * Name: MUART_interface.h
 * Author: Mahmoud Adel
 * Description: This file contains interfacing information of UART module
 * Version: v1.0
 * */

/*Header file guard*/
#ifndef MUART_INTERFACE_H_
#define MUART_INTERFACE_H_

/************************************************************************************************/
/*                                        Interfacing macros                                    */
/************************************************************************************************/

#define UART_2400_BPS          (207)
#define UART_4800_BPS          (103)
#define UART_9600_BPS          (51)
#define UART_19200_BPS         (25)
#define UART_115200_BPS        (3)

/************************************************************************************************/
/*                                        Functions' prototypes                                 */
/************************************************************************************************/

/*This function is used to initialize UART peripheral with specific baud rate*/
void muart_init(u16_t au16_baudRate);

/*This function is used to send one byte over UART peripheral*/
void muart_sendByte(u8_t au8_dataByte);

/*This function is used to receive one byte over UART peripheral*/
void muart_recvByte(u8_t* pu8_dataByte);

/*This function is used to send stream of bytes over UART peripheral*/
void muart_sendStream(u8_t* pu8_dataBytes, u8_t au8_dataSize);

#endif /* MUART_INTERFACE_H_ */
