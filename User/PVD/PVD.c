/**
  ******************************************************************************
  * @file    PVD.c
  * @author  XinLi
  * @version v1.0
  * @date    24-October-2017
  * @brief   Power voltage detector driver.
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
#include "PVD.h"
#include <string.h>

/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
static __IO PVD_Callback callback = NULL;

/* Function declarations -----------------------------------------------------*/
/* Function definitions ------------------------------------------------------*/

/**
  * @brief  Power voltage detector initialize.
  * @param  [in] level:    Power voltage detector level.
  * @param  [in] function: Power voltage detector callback.
  * @return None.
  */
void PVD_Init(PVD_Level level, PVD_Callback function)
{
  EXTI_InitTypeDef EXTI_InitStructure = {0};
  NVIC_InitTypeDef NVIC_InitStructure = {0};
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  
  EXTI_InitStructure.EXTI_Line    = EXTI_Line16;
  EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel                   = PVD_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PVD_IRQ_PreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = PVD_IRQ_SubPriority;
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  PWR_PVDLevelConfig(level);
  PWR_PVDCmd(ENABLE);
  
  callback = function;
}

/**
  * @brief  Power voltage detector deinitializes.
  * @param  None.
  * @return None.
  */
void PVD_DeInit(void)
{
  EXTI_InitTypeDef EXTI_InitStructure = {0};
  NVIC_InitTypeDef NVIC_InitStructure = {0};
  
  EXTI_InitStructure.EXTI_Line    = EXTI_Line16;
  EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel                   = PVD_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PVD_IRQ_PreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = PVD_IRQ_SubPriority;
  NVIC_InitStructure.NVIC_IRQChannelCmd                = DISABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  PWR_PVDCmd(DISABLE);
  
  callback = NULL;
}

/**
  * @brief  Set power voltage detector level.
  * @param  [in] level: Power voltage detector level.
  * @return None.
  */
void PVD_SetLevel(PVD_Level level)
{
  PWR_PVDLevelConfig(level);
}

/**
  * @brief  Get power voltage detector level.
  * @param  None.
  * @return Power voltage detector level.
  */
PVD_Level PVD_GetLevel(void)
{
  uint32_t tmpreg = PWR->CR;
  
  return (PVD_Level)(tmpreg & 0xE0);
}

/**
  * @brief  Set power voltage detector callback.
  * @param  [in] function: Power voltage detector callback.
  * @return None.
  */
void PVD_SetCallback(PVD_Callback function)
{
  callback = function;
}

/**
  * @brief  Get power voltage detector callback.
  * @param  None.
  * @return Power voltage detector callback.
  */
PVD_Callback PVD_GetCallback(void)
{
  return callback;
}

/**
  * @brief  Get power voltage detector output.
  * @param  None.
  * @return Power voltage detector output.
  */
PVD_Output PVD_GetOutput(void)
{
  uint32_t tmpreg = PWR->CSR;
  
  return (PVD_Output)((tmpreg >> 2) & 0x01);
}

/**
  * @brief  This function handles the PVD Output interrupt request.
  * @param  None.
  * @return None.
  */
void PVD_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line16) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line16);
    
    if(callback != NULL)
    {
      callback(PVD_GetOutput());
    }
  }
}
