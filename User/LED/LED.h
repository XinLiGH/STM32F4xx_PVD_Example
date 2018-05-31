/**
  ******************************************************************************
  * @file    LED.h
  * @author  XinLi
  * @version v1.0
  * @date    24-October-2017
  * @brief   Header file for LED.c module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>Copyright &copy; 2017 XinLi</center></h2>
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <https://www.gnu.org/licenses/>.
  *
  ******************************************************************************
  */

#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C" {
#endif

/* Header includes -----------------------------------------------------------*/
#include "stm32f4xx.h"

/* Macro definitions ---------------------------------------------------------*/
#define LEDn                      (4)

#define LED1_RCC_AHB1Periph_GPIO  RCC_AHB1Periph_GPIOF
#define LED1_GPIO                 GPIOF
#define LED1_GPIO_Pin             GPIO_Pin_9

#define LED2_RCC_AHB1Periph_GPIO  RCC_AHB1Periph_GPIOF
#define LED2_GPIO                 GPIOF
#define LED2_GPIO_Pin             GPIO_Pin_10

#define LED3_RCC_AHB1Periph_GPIO  RCC_AHB1Periph_GPIOB
#define LED3_GPIO                 GPIOB
#define LED3_GPIO_Pin             GPIO_Pin_3

#define LED4_RCC_AHB1Periph_GPIO  RCC_AHB1Periph_GPIOB
#define LED4_GPIO                 GPIOB
#define LED4_GPIO_Pin             GPIO_Pin_4

/* Type definitions ----------------------------------------------------------*/
typedef enum
{
  LED_Pin1 = 0,
  LED_Pin2 = 1,
  LED_Pin3 = 2,
  LED_Pin4 = 3
}LED_Pin;

typedef enum
{
  LED_Off = 0,
  LED_On  = 1
}LED_Status;

/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
void LED_SetStatus(LED_Pin pin, LED_Status status);
LED_Status LED_GetStatus(LED_Pin pin);

/* Function definitions ------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __LED_H */
