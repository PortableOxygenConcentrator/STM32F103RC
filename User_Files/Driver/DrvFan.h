/**
  ******************************************************************************
  * @file    DrvFan.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about fan. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */

#ifndef __DRVFAN_H__
#define __DRVFAN_H__

#include "AplMain.h"

#define V3  		PAout(10)
#define FAN 		PAout(7)
#define FAN_EN  V3


void Fan_Init(void);
void Fan_Ctrl(u16 speed);


#endif

/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
