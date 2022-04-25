/**
  ******************************************************************************
  * @file			MidSensor.c
  * @author		Best Team
  * @version	V1.0.0
  * @date			26-March-2021
  * @brief   	This file provides the function about sensor. 
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
#include "MidSensor.h"

/*Define the parameters used in the program.*/
O2_Sensor_ParaTypeDef O2_sensor;

/**
  * @brief  		Get O2 Sensor Data
  *         
  * @param[in] 	None
  *         
  * @return 		None
  */
void Get_O2_Sensor_Data(void) 
{	
	static u8 k = 0;		
	
	O2_sensor.receive_temp[k] = USART_ReceiveData(USART3);	
	
	k++;

	if(k > 11) 
	{
		k = 0;
		O2_sensor.sensor_heart_beat ^= 0x01;
	}
	
}


/**
  * @brief  		Handle O2 Sensor Data
  *         
  * @param[in] 	None
  *         
  * @return 		None
  */
void Handle_O2_Sensor_Data(void)
{
	u8 i = 0;
	u8 j = 0;
	u8 O2_denstiy = 0;
	
	for(j=0;j<12;j++)	
	{
		O2_sensor.sensordata[j] = O2_sensor.receive_temp[j];
	}
	

	for(i = 0;i <12;i ++)
	{	
			if(O2_sensor.sensordata[0] == 0x16)
			{
				if(O2_sensor.sensordata[1] == 0x09)
				{
					if(O2_sensor.sensordata[2] == 0x01)
					{
						break;
					}
				}	
			}
			
			O2_sensor.sensordata_temp = O2_sensor.sensordata[0];/*Protect the first sensor data.*/
		
			for(j = 0;j <11;j ++)
			{			
				O2_sensor.sensordata[j] = O2_sensor.sensordata[j + 1];/*Move the data until the first three datas are 0x16 0x09 0x01*/
			}
			
			O2_sensor.sensordata[11] = O2_sensor.sensordata_temp;/*Protect the first sensor data.*/
			
	}	

	O2_denstiy = ( 256* (float)O2_sensor.sensordata[3] + (float)O2_sensor.sensordata[4] )/10;
	
	if((O2_denstiy > 21) && (O2_denstiy <= 99)){
		system.density = O2_denstiy + 3;
	}
	else{
		system.density = 21;
	}

}


/**
  * @brief  		O2 Sensor Diagnostic
  *         
  * @param[in] 	None
  *         
  * @return 		None
  */
void O2_Sensor_Diag(u8 receive_data)
{
	FlagStatus sensor_heart_beat_1s_count_flag = RESET;
	static u8 last_receive_data = 0;
	static u8 sensor_heart_beat_1s_count = 0;	
	FlagStatus heart_beat_flag = SET;
	
	if(receive_data != last_receive_data)
	{
		heart_beat_flag = SET;
				
		last_receive_data = receive_data;
	}
	
	if(sensor_heart_beat_1s_count_flag) 
	{
		sensor_heart_beat_1s_count_flag = RESET;
		sensor_heart_beat_1s_count ++;
		
		if(heart_beat_flag)
		{
			heart_beat_flag = RESET;	
			sensor_heart_beat_1s_count = 0;
			O2_sensor.sensor_comm_err = 0;
		}
			
		if(sensor_heart_beat_1s_count > 5)
		{
			sensor_heart_beat_1s_count = 6;
			O2_sensor.sensor_comm_err = 1;
		}			
	}		
	
}


/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/

