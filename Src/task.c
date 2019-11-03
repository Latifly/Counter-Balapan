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
#include "uart.h"

uint16_t batas[3];
uint8_t bouncing[3]={0xFF,0xFF,0xFF};
uint8_t button=0xFF;
uint8_t stopwatchEnable;
uint16_t timeoutCount[3];
uint16_t timoutMax=1000;
uint32_t temp;
uint8_t lapA=0, lapB=0, lapC=0;



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
		lapA++;
		if(lapA>5) {
			lapA=5;
		}
		else{
			milisec_A=milisec;
			sec_A=sec;
			minute_A=minute;
		}
		sendtoPC();
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
	}

//	if(lap[0]==4 && bouncing[0]==0x03){ //print if finish
//		LCD_SetCursor(7,1);
//		LCD_PrintNum(minute);
//		LCD_Print(":");
//		LCD_PrintNum(sec);
//		LCD_Print(":");
//		LCD_PrintNum(milisec);
//	}


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
		lapB++;
		if(lapB>5) {
			lapB=5;
		}
		else {
			milisec_B=milisec;
			sec_B=sec;
			minute_B=minute;
		}
		sendtoPC();
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
	}

	//jalur3
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
		lapC++;
		if(lapC>5) {
			lapC=5;
		}
		else{
			milisec_C=milisec;
			sec_C=sec;
			minute_C=minute;
		}
		sendtoPC();
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
	}

//	buttonSS
	if(HAL_GPIO_ReadPin(Button_SS_GPIO_Port,Button_Res_Pin) == GPIO_PIN_RESET){
		button=(button<<1);
	}
	else{
		button=(button<<1)|1;
	}

	if (button==0x03){
		timerEnable=!(timerEnable);
		if(stopwatchEnable==1){
			stopwatchEnable=0;
		}
	}
}



void task2_run(void){ //switching 7 segment
	shift_data(lapA);
	HAL_GPIO_WritePin(SEG_ENA1_GPIO_Port,SEG_ENA1_Pin,GPIO_PIN_SET);
	for(uint16_t i=0;i<10000;i++);
	HAL_GPIO_WritePin(SEG_ENA1_GPIO_Port,SEG_ENA1_Pin,GPIO_PIN_RESET);

	shift_data(lapB);
	HAL_GPIO_WritePin(SEG_ENA2_GPIO_Port,SEG_ENA2_Pin,GPIO_PIN_SET);
	for(uint16_t i=0;i<10000;i++);
	HAL_GPIO_WritePin(SEG_ENA2_GPIO_Port,SEG_ENA2_Pin,GPIO_PIN_RESET);

	shift_data(lapC);
	HAL_GPIO_WritePin(SEG_ENA3_GPIO_Port,SEG_ENA3_Pin,GPIO_PIN_SET);
	for(uint16_t i=0;i<10000;i++);
	HAL_GPIO_WritePin(SEG_ENA3_GPIO_Port,SEG_ENA3_Pin,GPIO_PIN_RESET);
}

void task3_run(void){ //stopwatch, timer 10ms
	if(lapA==1||lapB==1||lapC==1){
	stopwatchEnable=1;
	}

	if(stopwatchEnable==1){
		milisec++;
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
//	LCD_Clear();
	LCD_SetCursor(3,0);
	LCD_Print("Counter Balapan");
	LCD_SetCursor(7,1);
	LCD_Print("3 Jalur");
	LCD_SetCursor(4,3);
	LCD_Print("by Lapitech");
}

void stopwatch_print(void){
	LCD_SetCursor(7,0);
	LCD_PrintNum(minute);
	LCD_Print(":");
	LCD_PrintNum(sec);
	LCD_Print(":");
	LCD_PrintNum(milisec);
}

void hasil_waktu(void){
	// jalur A
	LCD_SetCursor(0,1);
	LCD_Print("A");
	LCD_SetCursor(2,1);
	LCD_PrintNum(lapA);
	LCD_SetCursor(4,1);
	LCD_PrintNum(minute_A);
	LCD_Print(":");
	LCD_PrintNum(sec_A);
	LCD_Print(":");
	LCD_PrintNum(milisec_A);
	if(lapA==5){
		LCD_SetCursor(14,1);
			LCD_Print("FINISH");
	}

	// jalur A
		LCD_SetCursor(0,2);
		LCD_Print("A");
		LCD_SetCursor(2,2);
		LCD_PrintNum(lapB);
		LCD_SetCursor(4,2);
		LCD_PrintNum(minute_B);
		LCD_Print(":");
		LCD_PrintNum(sec_B);
		LCD_Print(":");
		LCD_PrintNum(milisec_B);
		if(lapB==5){
			LCD_SetCursor(14,2);
			LCD_Print("FINISH");
		}

		// jalur C
		LCD_SetCursor(0,3);
		LCD_Print("C");
		LCD_SetCursor(2,3);
		LCD_PrintNum(lapC);
		LCD_SetCursor(4,3);
		LCD_PrintNum(minute_C);
		LCD_Print(":");
		LCD_PrintNum(sec_C);
		LCD_Print(":");
		LCD_PrintNum(milisec_C);
		if(lapC==5){
			LCD_SetCursor(14,3);
			LCD_Print("FINISH");
		}
}


void sendtoPC(void){
	UART_println("------------------");
	UART_print("jalur A  Lap="); UART_printnum(lapA); UART_print("  "); UART_printnum(minute_A); UART_print(":"); UART_printnum(sec_A); UART_print(":"); UART_printnum(milisec_A); UART_println(" ");
	UART_print("jalur B  Lap="); UART_printnum(lapB); UART_print("  "); UART_printnum(minute_B); UART_print(":"); UART_printnum(sec_B); UART_print(":"); UART_printnum(milisec_B); UART_println(" ");
	UART_print("jalur C  Lap="); UART_printnum(lapC); UART_print("  "); UART_printnum(minute_C); UART_print(":"); UART_printnum(sec_C); UART_print(":"); UART_printnum(milisec_C); UART_println(" ");
}

//	LCD_Clear();
//	LCD_SetCursor(3,0);
//	LCD_PrintNum(minute);
//	LCD_Print(":");
//	LCD_PrintNum(sec);
//	LCD_Print(":");
//	LCD_PrintNum(milisec);

