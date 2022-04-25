/**
  ******************************************************************************
  * @file    DrvPower.h
  * @author  Best Team
  * @version V1.0.0
  * @date   24-June-2021
  * @brief   This file provides the function about power. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */
	
	
#ifndef __DRVPOWER_H__
#define __DRVPOWER_H__

#include "AplMain.h"

//#define ADAPTER_IN	PAin(0)
#define EN12V	 			PCout(3)

void Power_12V_Init(void);
void Adapter_Check_Init(void);

#endif

/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
