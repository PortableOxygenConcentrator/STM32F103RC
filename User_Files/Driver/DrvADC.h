/**
  ******************************************************************************
  * @file    DrvADC.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about ADC. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */
	
	
#ifndef __ADC_H__
#define __ADC_H__

#include "AplMain.h"
	
/*Define the parameters used in the program.*/
typedef struct 
{
	float x,y,y1,y2,y3; 
	u32	pressure_zero;
	u16	ADC_temp1[10],ADC_temp2[50];
	u16 ADC_smooth_filter[30];

	u8	i,j,counter;
	FlagStatus  ADC_cs_flag;
	
}Pressure_Sensor_ParaTypeDef;
	
extern Pressure_Sensor_ParaTypeDef breath_pressure_sensor;
extern Pressure_Sensor_ParaTypeDef system_pressure_sensor;

void	ADC1_Init(void);
u16 ADC1_Handle(u8 ch);

void	ADC2_Init(void);
u16 ADC2_Handle(u8 ch);

#endif

/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
