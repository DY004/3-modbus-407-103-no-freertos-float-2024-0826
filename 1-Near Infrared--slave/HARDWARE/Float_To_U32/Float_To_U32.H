#ifndef _Float_To_U32_H
#define _Float_To_U32_H
#include "sys.h"
#include "main.h"


#define PWR_KEY        HAL_GPIO_ReadPin(POWER_ON_OFF_GPIO_Port,POWER_ON_OFF_Pin)  //on/off按键

void Float_To_U32(float value,float value2, uint16_t Holdaddr);
#define S_REG_HOLDING_NREGS           500 //保持寄存器数量
extern u16 usSRegHoldBuf[S_REG_HOLDING_NREGS] ;//保持寄存器 
#endif


