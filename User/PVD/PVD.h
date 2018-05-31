/**
  ******************************************************************************
  * @file    PVD.h
  * @author  XinLi
  * @version v1.0
  * @date    24-October-2017
  * @brief   Header file for PVD.c module.
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

#ifndef __PVD_H
#define __PVD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Header includes -----------------------------------------------------------*/
#include "stm32f4xx.h"

/* Macro definitions ---------------------------------------------------------*/
#define PVD_IRQ_PreemptionPriority  (0)
#define PVD_IRQ_SubPriority         (0)

/* Type definitions ----------------------------------------------------------*/
typedef enum
{
  PVD_Level_2V0 = PWR_PVDLevel_0,
  PVD_Level_2V1 = PWR_PVDLevel_1,
  PVD_Level_2V3 = PWR_PVDLevel_2,
  PVD_Level_2V5 = PWR_PVDLevel_3,
  PVD_Level_2V6 = PWR_PVDLevel_4,
  PVD_Level_2V7 = PWR_PVDLevel_5,
  PVD_Level_2V8 = PWR_PVDLevel_6,
  PVD_Level_2V9 = PWR_PVDLevel_7
}PVD_Level;

typedef enum
{
  PVD_Output_High = 0,
  PVD_Output_Low  = 1
}PVD_Output;

typedef void (*PVD_Callback)(PVD_Output output);

/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
void PVD_Init(PVD_Level level, PVD_Callback function);
void PVD_DeInit(void);

void PVD_SetLevel(PVD_Level level);
PVD_Level PVD_GetLevel(void);

void PVD_SetCallback(PVD_Callback function);
PVD_Callback PVD_GetCallback(void);

PVD_Output PVD_GetOutput(void);

/* Function definitions ------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __PVD_H */
