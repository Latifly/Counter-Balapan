/*
 * task.h
 *
 *  Created on: Oct 29, 2019
 *      Author: Alatif
 */

#ifndef INC_TASK_H_
#define INC_TASK_H_

void task1_run(void);
void task2_run(void);
void task3_run(void);
void kalibrasi_sensor(void);
void display_utama(void);
void stopwatch_print(void);


uint8_t milisec, sec, minute;

_Bool timerEnable;


#endif /* INC_TASK_H_ */
