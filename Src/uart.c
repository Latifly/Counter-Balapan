/*
 * uart.c
 *
 *  Created on: Nov 3, 2019
 *      Author: Alatif
 */


#include "uart.h"

void UART_print(char *pData){
	HAL_UART_Transmit(&huart1, (uint8_t *)pData, strlen(pData), 10);
}

void UART_println(char *pData){
	HAL_UART_Transmit(&huart1, (uint8_t *)pData, strlen(pData), 10);
	char newLine[2] = "\r\n";
	HAL_UART_Transmit(&huart1, (uint8_t *)newLine, 2, 10);
}

void UART_printnum(uint16_t num){
	char buff[50];
	sprintf(buff,"%d", num);
	HAL_UART_Transmit(&huart1, (uint8_t *)buff, strlen(buff), 10);
}

