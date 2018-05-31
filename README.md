# STM32F4xx_PVD_Example

STM32F4 的 PVD 驱动。适用于 STM32F4 全部芯片。

## 开发环境

* 固件库：STM32F4xx_DSP_StdPeriph_Lib_V1.8.0
* 编译器：ARMCC V5.06
* IDE：Keil uVision5
* 操作系统：Windows 10 专业版

## API

* void PVD_Init(PVD_Level level, PVD_Callback function)
* void PVD_DeInit(void)
* void PVD_SetLevel(PVD_Level level)
* PVD_Level PVD_GetLevel(void)
* void PVD_SetCallback(PVD_Callback function)
* PVD_Callback PVD_GetCallback(void)
* PVD_Output PVD_GetOutput(void)
