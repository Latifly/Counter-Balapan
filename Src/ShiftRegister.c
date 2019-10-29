/*
 * ShiftRegister.c
 *
 *  Created on: Oct 29, 2019
 *      Author: Alatif
 */

#include "main.h"


void shift_data(uint8_t data){
	for(int i=7; i>=0; i--){
		HAL_GPIO_WritePin(SER_DATA_GPIO_Port, SER_DATA_Pin, ((data>>i)&1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SER_CLK_GPIO_Port,SER_CLK_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(SER_CLK_GPIO_Port,SER_CLK_Pin,GPIO_PIN_RESET);
	}

	HAL_GPIO_WritePin(SER_LOAD_GPIO_Port, SER_LOAD_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(SER_LOAD_GPIO_Port, SER_LOAD_Pin,GPIO_PIN_RESET);

}