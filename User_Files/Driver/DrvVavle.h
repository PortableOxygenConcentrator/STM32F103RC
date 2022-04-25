/**
  ******************************************************************************
  * @file    DrvVavle.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about vavle. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */

#ifndef __DRVVAVLE_H__
#define __DRVVAVLE_H__

#include "AplMain.h"

#define VAVLE1 		PAout(12)
#define VAVLE2 		PAout(11)
#define VAVLE3 		PCout(2)
#define VAVLE4 		PCout(1)
#define VAVLE5 		PCout(0)

#define VAVLE_O2_1 	VAVLE1
#define VAVLE_O2_2 	VAVLE2
#define VAVLE_AVG 	VAVLE3
#define VAVLE_AI 		VAVLE4
#define VAVLE_DIR 	VAVLE5

void Vavle_Init(void);
void O2_Vavle_Control(void);
void Breath_Vavle_Control(void);

extern u16 t_vavle ;	
extern u16 t_vavle_last ;

#endif

/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
