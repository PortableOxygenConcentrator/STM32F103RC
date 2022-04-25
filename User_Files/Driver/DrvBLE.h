/**
  ******************************************************************************
  * @file		bluetooth.c
  * @author	Best Team
  * @version	V1.0.0
  * @date		24-June-2021
  * @brief	This file provides the functions about valve bluetooth. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "AplMain.h"

#define	BLUETOOTH_RESET_ON			PAout(15) = SET;
#define	BLUETOOTH_RESET_OFF			PAout(15) = RESET;

/*Wake up when the signal if off.*/
#define	BLUETOOTH_SLEEP				PBout(3) = SET;
#define	BLUETOOTH_WAKEUP			PBout(3) = RESET;

/*Interruption.Not used.*/
//#define	BLUETOOTH_INT					PBout(4)


void Bluetooth_AplMain(void);

 

 
#endif



/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
