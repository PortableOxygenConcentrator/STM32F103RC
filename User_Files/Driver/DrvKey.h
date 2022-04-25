/**
  ******************************************************************************
  * @file    DrvKey.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about key. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */
	
	
#ifndef __DRVKEY_H__
#define __DRVKEY_H__

#include "AplMain.h"

#define KEY1 PAin(0)
#define KEY2 PAin(1)
#define KEY3 PAin(2)
#define KEY4 PAin(3)
#define KEY5 PAin(4)

#define KEY1_STATUS 0
#define KEY2_STATUS 1
#define KEY3_STATUS 2
#define KEY4_STATUS 3
#define KEY5_STATUS 4

void Key_Init(void); 
FlagStatus Key_GetFlagStatus(u8 key_num);

#endif


/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
