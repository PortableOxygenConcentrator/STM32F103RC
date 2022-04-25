/**
  ******************************************************************************
  * @file    AplMain.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides ... 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */
	
#ifndef __APLMAIN_H__
#define __APLMAIN_H__

#include <stdio.h>
#include <math.h>

#include "stm32f10x.h"

#include "DrvADC.h"
#include "DrvBLE.h"
#include "DrvCharger.h"
#include "DrvDac.h"
#include "DrvDelay.h"
#include "DrvFan.h"
#include "DrvFlash.h"
#include "DrvFont.h"
#include "DrvKey.h"
#include "DrvLcd.h"
#include "DrvLed.h"
#include "DrvPictures.h"
#include "DrvPower.h"	
#include "DrvSMBus.h"
#include "DrvSPI.h"
#include "DrvSYS.h"	
#include "DrvTimer.h"
#include "DrvUsart.h"
#include "DrvVavle.h"

#include "MidLCD.h"
#include "MidBLDC.h"
#include "MidTime.h"
#include "MidSensor.h"
#include "MidModbus.h"

#include "Common.h"

void Initial(void);
void Mode_Standby_Function(void);
void Mode_Oxygen_Generate_Function(void);
void Mode_Atomization_Function(void);
void Mode_AI_Function(void);
void Mode_Debug_Function(void);
void Mode_Judgement(void);


#endif


/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
