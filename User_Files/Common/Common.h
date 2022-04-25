/**
  ******************************************************************************
  * @file    Common.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides all the global variables. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */
	
#ifndef __COMMON_H__
#define __COMMON_H__

#include "AplMain.h"


/*Define the parameters used in the program.*/
typedef struct 
{
	u32 single_time;										/*Accumulate time in one time*/
	u32 accumulate_time;								/*Accumulate time in total*/
	u32 real_accumulate_time;						/*Accumulate time in the real time*/
	u32 accumulate_display_time;				/*Accumulate time to display*/
	u32 mem_accumulate_time;						/*Accumulate time in memory*/	
 	u16 set_time;												/*Set Time*/
	u16 time_1s_count;									/*Basic Time*/
	
	u16 LCD_brightness;									/*The brightness of LCD*/
	
	u16 flash_memory[10];								/*The memeory of flash*/
		
	u16	pressure_time1;									/*Pressure time1*/
	u16	pressure_time2;									/*Pressure time2*/
	u16	pressure_time3;									/*Pressure time2*/
	u16	pressure_time4;									/*Pressure time4*/
	u16	pressure_time5;									/*Pressure time5*/
	u16	pressure_time6;									/*Pressure time6*/
	
	u16 FAN_Speed;											/*The speed of FAN*/		
	
	u16 BLDC_Speed;											/*The speed of BLDC*/	

	u8 alarm_message;										/*Alarm messages*/

	u8 density;													/*System density*/
	u8 respiratory_rate;								/*System respiratory rate*/
	u8 mode;														/*System mode*/
	u8 mode_last;												/*System last mode*/
	u8 grade;														/*System grade*/

	FlagStatus vavle_start_up_flag;			/*System vavle_start_up_flag*/
	FlagStatus keys_ack;								/*The acknowledge of key1 and key2 are triggered together.*/
	
}System_ParaTypeDef;

extern System_ParaTypeDef system;

#define MODE_OXYGENERATE 		1
#define MODE_ATOMIZATION	 	2
#define MODE_DEBUG 					3
#define MODE_AI 						4
#define MODE_STANDBY 				255

#endif

/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
