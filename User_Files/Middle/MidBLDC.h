/**
  ******************************************************************************
  * @file    MidBLDC.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about BLDC. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */
	
#ifndef __MIDBLDC_H__
#define __MIDBLDC_H__

#include "AplMain.h"

#define ENBLDC PBout(8)


void BLDC_Init(void);
void BLDC_Control(u16 speed);

#endif

/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
