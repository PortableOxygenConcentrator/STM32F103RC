/**
  ******************************************************************************
  * @file    DrvLED.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about led. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */
	
#ifndef __DRVLED_H__
#define __DRVLED_H__

#include "AplMain.h"

void LED_Init(void); 

#define LED_FAULT PBout(8)
#define LED_POWER PBout(9)

#endif



/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
