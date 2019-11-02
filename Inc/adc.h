/*
 * adc.h
 *
 *  Created on: Oct 31, 2019
 *      Author: Alatif
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

ADC_HandleTypeDef hadc1;

uint32_t sensor[3];

void ADC_start(void);


#endif /* INC_ADC_H_ */
