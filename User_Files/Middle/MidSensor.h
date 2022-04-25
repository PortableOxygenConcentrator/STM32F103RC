/**
  ******************************************************************************
  * @file    MidSensor.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about sensor. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */
#ifndef __MIDSENSOR_H__
#define __MIDSENSOR_H__

#include "AplMain.h"


/*Define the parameters used in the program.*/
typedef struct 
{
	u8 receive_temp[12];
	u8 sensordata[12];
	u8 sensordata_temp;

	u8 sensor_heart_beat; 

	u8 sensor_comm_err; 
	
}O2_Sensor_ParaTypeDef;



void Get_O2_Sensor_Data(void);		 				
void O2_Sensor_Diag(u8 receive_data);			
void Handle_O2_Sensor_Data(void);	 				
	
#endif
	
/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/

