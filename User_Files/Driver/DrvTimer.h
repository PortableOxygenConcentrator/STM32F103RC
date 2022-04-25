/**
  ******************************************************************************
  * @file    DrvTimer.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about timer. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */

#ifndef __DRVTIMER_H__
#define __DRVTIMER_H__

#include "AplMain.h"


extern FlagStatus key_timer2_100ms_flag;					/*Used in the vavle-controling and keys-judgement.*/
extern FlagStatus breath_vavle_timer2_10ms_flag;	/*Used in the breath-vavle controling.*/
extern FlagStatus breath_sensor_timer2_10ms_flag;	/*Used in the breath-sensor time calculating.*/
extern FlagStatus no_breath_timer2_10ms_flag;			/*Used in the no-breath time calculating.*/
extern FlagStatus O2_vavle_timer2_10ms_flag;			/*Used in the O2-vavle controling.*/
extern FlagStatus ui_timer2_1s_flag;							/*Used in the UI-refreshing.*/
extern FlagStatus modbus_timer2_100ms_flag;				/*Used in the modbus-refreshing.*/

extern u8  TIM8CH3_CAPTURE_STA ;     				
extern u16 TIM8CH3_CAPTURE_VAL;  
 
void TIM2_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM4_Cap_Init(u32 arr,u16 psc);
void TIM5_Init(u16 arr,u16 psc);
void TIM6_Init(u16 arr,u16 psc);
void TIM7_Init(u16 arr,u16 psc);
void TIM8_Init(u32 arr,u16 psc);


#endif



/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
