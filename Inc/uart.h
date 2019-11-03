/*
 * uart.h
 *
 *  Created on: Nov 3, 2019
 *      Author: Alatif
 */

#ifndef INC_UART_H_
#define INC_UART_H_


#include "main.h"
#include "string.h"
#include "stdio.h"

UART_HandleTypeDef huart1;

void UART_print(char *pData);
void UART_println(char *pData);
void UART_printnum(uint16_t num);


#endif /* INC_UART_H_ */
