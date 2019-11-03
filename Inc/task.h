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
void hasil_waktu(void);
void sendtoPC(void);

uint8_t milisec, milisec_A, milisec_B, milisec_C;
uint8_t sec, sec_A, sec_B, sec_C;
uint8_t minute, minute_A, minute_B, minute_C;

_Bool timerEnable;


#endif /* INC_TASK_H_ */
