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


void task1_run(void){


}

void task2_run(void){


}

void task3_run(void){ //stopwatch

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
