/*
 * adc.c
 *
 *  Created on: Oct 31, 2019
 *      Author: Alatif
 */

#include "stm32f1xx.h"
#include "adc.h"



void ADC_start(void){
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)sensor, 3);
}
