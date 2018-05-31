/**
  ******************************************************************************
  * @file    LED.c
  * @author  XinLi
  * @version v1.0
  * @date    24-October-2017
  * @brief   LED module driver.
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

/* Header includes -----------------------------------------------------------*/
#include "LED.h"
#include <stdbool.h>

/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
static      GPIO_TypeDef *LED_GPIO[LEDn]                = {LED1_GPIO, LED2_GPIO, LED3_GPIO, LED4_GPIO};
static      uint16_t      LED_GPIO_Pin[LEDn]            = {LED1_GPIO_Pin, LED2_GPIO_Pin, LED3_GPIO_Pin, LED4_GPIO_Pin};
static      uint32_t      LED_RCC_AHB1Periph_GPIO[LEDn] = {LED1_RCC_AHB1Periph_GPIO, LED2_RCC_AHB1Periph_GPIO, LED3_RCC_AHB1Periph_GPIO, LED4_RCC_AHB1Periph_GPIO};
static __IO LED_Status    ledStatus[LEDn]               = {LED_Off, LED_Off, LED_Off, LED_Off};

/* Function declarations -----------------------------------------------------*/
static void LED_Init(void);

/* Function definitions ------------------------------------------------------*/

/**
  * @brief  Led initializes.
  * @param  None.
  * @return None.
  */
static void LED_Init(void)
{
  static bool init_flag = false;
  
  if(init_flag == false)
  {
    init_flag = true;
    
    for(int i = 0; i < LEDn; i++)
    {
      GPIO_InitTypeDef GPIO_InitStructure = {0};
      
      RCC_AHB1PeriphClockCmd(LED_RCC_AHB1Periph_GPIO[i], ENABLE);
      
      GPIO_InitStructure.GPIO_Pin   = LED_GPIO_Pin[i];
      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
      GPIO_Init(LED_GPIO[i], &GPIO_InitStructure);
      
      GPIO_WriteBit(LED_GPIO[i], LED_GPIO_Pin[i], (BitAction)LED_Off);
    }
  }
}

/**
  * @brief  Set led status.
  * @param  [in] pin:    That led.
  * @param  [in] status: Led status.
  * @return None.
  */
void LED_SetStatus(LED_Pin pin, LED_Status status)
{
  if(status != ledStatus[pin])
  {
    ledStatus[pin] = status;
    
    LED_Init();
    
    GPIO_WriteBit(LED_GPIO[pin], LED_GPIO_Pin[pin], (BitAction)status);
  }
}

/**
  * @brief  Get led status.
  * @param  [in] pin: That led.
  * @return Led status.
  */
LED_Status LED_GetStatus(LED_Pin pin)
{
  return ledStatus[pin];
}
