/*
 * ADC.h
 *
 *  Created on: Oct 28, 2019
 *      Author: Alatif
 */

#ifndef LCD_H_
#define LCD_H_

#include "stm32f1xx.h"
#include "LCD.h"
#include "stm32f1xx_hal.h"
#include "main.h"

#define LCD_EN() 			{	HAL_GPIO_WritePin(LCD_EN_GPIO_Port,LCD_EN_Pin,GPIO_PIN_SET);\
								HAL_Delay(1);\
								HAL_GPIO_WritePin(LCD_EN_GPIO_Port,LCD_EN_Pin,GPIO_PIN_RESET);\
								HAL_Delay(1);}
#define LCD_RW(state)		{	HAL_GPIO_WritePin(LCD_RW_GPIO_Port,LCD_RW_Pin, (state) ? GPIO_PIN_SET : GPIO_PIN_RESET);}
#define LCD_RS(state)		{	HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin, (state) ? GPIO_PIN_SET : GPIO_PIN_RESET);}
#define LCD_Command(data)	{	LCD_Send(0,data);}
#define LCD_Data(data)		{	LCD_Send(1,data);}

void LCD_Write4bit(uint8_t data);
void LCD_Send(_Bool mode, uint8_t data);
void LCD_Init (void);
void LCD_Print(char *pData);
void LCD_SetCursor(uint8_t x,uint8_t y);
void LCD_Clear(void);
void LCD_PrintNum(int16_t number);


#endif /* LCD_H_ */
