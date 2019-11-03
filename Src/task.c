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
uint16_t timoutMax=1000;
uint32_t temp;
uint8_t lap[3]={0,0,0};



void task1_run(void){
	//jalur1
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

	if (bouncing[0]==0x03 && timeoutCount[0]<timoutMax){ //counting
		lap[0]++;
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
	}

	if(lap[0]==4 && bouncing[0]==0x03){ //print if finish
		LCD_SetCursor(7,1);
		LCD_PrintNum(minute);
		LCD_Print(":");
		LCD_PrintNum(sec);
		LCD_Print(":");
		LCD_PrintNum(milisec);
	}


	//jalur2
	if(sensor[1]>=batas[1]+100 || sensor[1]<=batas[1]-100 ){ //sensor detect
		bouncing[1]=(bouncing[1]<<1);
		timeoutCount[1]++;
	}
	else{
		bouncing[1]=(bouncing[1]<<1)|1; //sensor tidak detect
		timeoutCount[1]=0;
	}

	if (timeoutCount[1]>timoutMax){
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_SET);
	}

	if (bouncing[1]==0x03 && timeoutCount[1]<timoutMax){
		lap[1]++;
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
	}

	//jalur2
	if(sensor[2]>=batas[2]+100 || sensor[2]<=batas[2]-100 ){ //sensor detect
		bouncing[2]=(bouncing[2]<<1);
		timeoutCount[2]++;
	}
	else{
		bouncing[2]=(bouncing[2]<<1)|1; //sensor tidak detect
		timeoutCount[2]=0;
	}

	if (timeoutCount[2]>timoutMax){
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_SET);
	}

	if (bouncing[2]==0x03 && timeoutCount[2]<timoutMax){
		lap[2]++;
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
	}


}



void task2_run(void){ //switching 7 segment
	shift_data(lap[0]);
	HAL_GPIO_WritePin(SEG_ENA1_GPIO_Port,SEG_ENA1_Pin,GPIO_PIN_SET);
	for(uint16_t i=0;i<10000;i++);
	HAL_GPIO_WritePin(SEG_ENA1_GPIO_Port,SEG_ENA1_Pin,GPIO_PIN_RESET);

	shift_data(lap[1]);
	HAL_GPIO_WritePin(SEG_ENA2_GPIO_Port,SEG_ENA2_Pin,GPIO_PIN_SET);
	for(uint16_t i=0;i<10000;i++);
	HAL_GPIO_WritePin(SEG_ENA2_GPIO_Port,SEG_ENA2_Pin,GPIO_PIN_RESET);

	shift_data(lap[2]);
	HAL_GPIO_WritePin(SEG_ENA3_GPIO_Port,SEG_ENA3_Pin,GPIO_PIN_SET);
	for(uint16_t i=0;i<10000;i++);
	HAL_GPIO_WritePin(SEG_ENA3_GPIO_Port,SEG_ENA3_Pin,GPIO_PIN_RESET);
}

void task3_run(void){ //stopwatch, timer 10ms
	if(lap[0]==1||lap[1]==0||lap[2]){
	stopwatchEnable=1;
	}
	if(stopwatchEnable==1){
		milisec+=10;
		if (milisec>99){
			milisec-=100;
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

	LCD_Clear();
	LCD_SetCursor(7,0);
	LCD_PrintNum(minute);
	LCD_Print(":");
	LCD_PrintNum(sec);
	LCD_Print(":");
	LCD_PrintNum(milisec);


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

