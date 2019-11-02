/*
 * task.c
 *
 *  Created on: Oct 29, 2019
 *      Author: Alatif
 */

#include "main.h"
#include "task.h"
#include "ShiftRegister.h"
#include "LCD.h"
#include "adc.h"

uint16_t batas[3];
uint8_t bouncing[3]={0xFF,0xFF,0xFF};
uint16_t timeoutCount[3];
uint16_t timoutMax=2000;
uint32_t temp;
uint8_t lap1=0, lap2=0, lap3=0;




void task1_run(void){

	if(sensor[0]>=batas[0]+100 || sensor[0]<=batas[0]-100 ){ //sensor detect
		bouncing[0]=(bouncing[0]<<1);
		timeoutCount[0]++;
	}
	else{
		bouncing[0]=(bouncing[0]<<1)|1; //sensor tidak detect
		timeoutCount[0]=0;
	}

	if (timeoutCount[0]>timoutMax){
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_SET);
	}

	if (timeoutCount[0]>timoutMax){
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_SET);
	}

	if (bouncing[0]==0x03 && timeoutCount[0]<timoutMax){
		lap1++;
	}



	HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
}



void task2_run(void){ //switching 7 segment

	shift_data(lap1);
	HAL_GPIO_WritePin(SEG_ENA1_GPIO_Port,SEG_ENA1_Pin,GPIO_PIN_SET);
	for(uint16_t i=0;i<10000;i++);
	HAL_GPIO_WritePin(SEG_ENA1_GPIO_Port,SEG_ENA1_Pin,GPIO_PIN_RESET);

	shift_data(lap2);
	HAL_GPIO_WritePin(SEG_ENA2_GPIO_Port,SEG_ENA2_Pin,GPIO_PIN_SET);
	for(uint16_t i=0;i<10000;i++);
	HAL_GPIO_WritePin(SEG_ENA2_GPIO_Port,SEG_ENA2_Pin,GPIO_PIN_RESET);

	shift_data(lap3);
	HAL_GPIO_WritePin(SEG_ENA3_GPIO_Port,SEG_ENA3_Pin,GPIO_PIN_SET);
	for(uint16_t i=0;i<10000;i++);
	HAL_GPIO_WritePin(SEG_ENA3_GPIO_Port,SEG_ENA3_Pin,GPIO_PIN_RESET);
}

void task3_run(void){ //stopwatch, timer 10ms

	start=1;
	if(start==1){
		milisec++;
		if (milisec>99){
			milisec=0;
			sec++;
			if(sec>59){
				sec=0;
				minute++;
			}
		}
	}
	else {
		milisec=sec=minute=0;
	}
}

void kalibrasi_sensor(void){
	LCD_Clear();
	LCD_Print("Kalibrasi sensor");
	for(uint8_t j=0;j<3;j++){
		temp=0;
		for(uint16_t i=0;i<1000;i++){
			temp+=sensor[j];
		}
		batas[j]=temp/1000;
	}
}

void display_utama(void){
	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_Print("Counter Balapan");
	LCD_SetCursor(0,1);
	LCD_Print("3 Jalur");
	LCD_SetCursor(0,3);
	LCD_Print("by Lapitech");
}

//	LCD_Clear();
//	LCD_SetCursor(3,0);
//	LCD_PrintNum(minute);
//	LCD_Print(":");
//	LCD_PrintNum(sec);
//	LCD_Print(":");
//	LCD_PrintNum(milisec);

