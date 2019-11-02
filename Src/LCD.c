/*
 * LCD.c
 *
 *  Created on: Oct 28, 2019
 *      Author: Alatif
 */

#include "stm32f1xx.h"
#include "LCD.h"
#include "stm32f1xx_hal.h"
#include "main.h"


void LCD_Write4bit(uint8_t data){
	HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, ((data>>0)&1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, ((data>>1)&1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, ((data>>2)&1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, ((data>>3)&1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void LCD_Send(_Bool mode, uint8_t data){
	LCD_RW(0);
	if (mode){
		LCD_RS(1);
	}
	else {LCD_RS(0);}
	LCD_Write4bit(data>>4);
	LCD_EN();
	LCD_Write4bit(data);
	LCD_EN();
}

void LCD_Print(char *pData){
	while(*pData){
		LCD_Data(*pData++);
//		pData++;
	}
}

void LCD_SetCursor(uint8_t x, uint8_t y){
	if(y==0) {LCD_Command(0x80 + x);}
	if(y==1) {LCD_Command(0xC0 + x);}
	if(y==2) {LCD_Command(0x94 + x);}
	if(y==3) {LCD_Command(0xD4 + x);}

}

void LCD_Init(){
	LCD_RW(0);
	LCD_Command(0x33);
	LCD_Command(0x32);
	LCD_Command(0x28);
	LCD_Command(0x0C);
	LCD_Command(0x06);
	LCD_Clear();
}

void LCD_Clear(){
	LCD_Command(0x01);
}

void LCD_PrintNum(int16_t number){
	char buff[20];
	sprintf(buff, "%d", number);
	LCD_Print(buff);
}
