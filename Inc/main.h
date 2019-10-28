/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LEDIN_Pin GPIO_PIN_13
#define LEDIN_GPIO_Port GPIOC
#define Button_Res_Pin GPIO_PIN_14
#define Button_Res_GPIO_Port GPIOC
#define Button_SS_Pin GPIO_PIN_15
#define Button_SS_GPIO_Port GPIOC
#define SENS1_Pin GPIO_PIN_0
#define SENS1_GPIO_Port GPIOA
#define SENS2_Pin GPIO_PIN_1
#define SENS2_GPIO_Port GPIOA
#define SENS3_Pin GPIO_PIN_2
#define SENS3_GPIO_Port GPIOA
#define SER_DATA_Pin GPIO_PIN_6
#define SER_DATA_GPIO_Port GPIOA
#define SER_CLK_Pin GPIO_PIN_7
#define SER_CLK_GPIO_Port GPIOA
#define SER_LOAD_Pin GPIO_PIN_0
#define SER_LOAD_GPIO_Port GPIOB
#define SEG_ENA1_Pin GPIO_PIN_1
#define SEG_ENA1_GPIO_Port GPIOB
#define SEG_ENA2_Pin GPIO_PIN_10
#define SEG_ENA2_GPIO_Port GPIOB
#define SEG_ENA3_Pin GPIO_PIN_11
#define SEG_ENA3_GPIO_Port GPIOB
#define LCD_RS_Pin GPIO_PIN_12
#define LCD_RS_GPIO_Port GPIOB
#define LCD_RW_Pin GPIO_PIN_13
#define LCD_RW_GPIO_Port GPIOB
#define LCD_EN_Pin GPIO_PIN_14
#define LCD_EN_GPIO_Port GPIOB
#define LCD_D4_Pin GPIO_PIN_15
#define LCD_D4_GPIO_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_8
#define LCD_D5_GPIO_Port GPIOA
#define LCD_D6_Pin GPIO_PIN_11
#define LCD_D6_GPIO_Port GPIOA
#define LCD_D7_Pin GPIO_PIN_12
#define LCD_D7_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_7
#define BUZZER_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
