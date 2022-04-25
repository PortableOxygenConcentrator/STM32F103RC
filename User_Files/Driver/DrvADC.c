/**
  ******************************************************************************
  * @file			DrvADC.c
  * @author		Best Team
  * @version	V1.0.0
  * @date			24-June-2021
  * @brief   	This file provides the function about ADC. 
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
#include "DrvADC.h"

Pressure_Sensor_ParaTypeDef breath_pressure_sensor;
Pressure_Sensor_ParaTypeDef system_pressure_sensor;

/**
  * @brief			Initial ADC1.
  *         
  * @param[in]	None.
  *         
  * @return			None.
  */
void ADC1_Init(void)	
{
	ADC_InitTypeDef 	ADC_InitStructure; 
	GPIO_InitTypeDef 	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC1,ENABLE );
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); 
                     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC1, &ADC_InitStructure);	  

	ADC_Cmd(ADC1, ENABLE);	
	
	ADC_ResetCalibration(ADC1);	
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	
	
	ADC_StartCalibration(ADC1);	

	while(ADC_GetCalibrationStatus(ADC1));	

//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
}

/**
  * @brief			Get ADC1.
  *         
  * @param[in]	u8 ch.
  *         
  * @return			ADC_GetConversionValue(ADC1).
  */
u16 Get_ADC1(u8 ch)   
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,converting time: (239.5+12.5)/12 = 21us		    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	 
	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC )); 

	return ADC_GetConversionValue(ADC1);	 
}

/**
  * @brief			ADC1_Handle.
  *         
  * @param[in]	u8 ch.
  *         
  * @return			none.
  *
	* @note formula
	*	@note y1=¦Á*x(0)+¦Â*x(0-1)+¦Ã*y1(0-1)			
	*	@note y2=¦Á*y1+¦Â*y1(0-1)+¦Ã*y2(0-1)			
	*	@note y3=¦Á*y2+¦Â*y2(0-1)+¦Ã*y3(0-1)			
 */
u16 ADC1_Handle(u8 ch)
{
	static u8 i = 0,j = 0;
  static float x_last = 0,y1_last = 0,y2_last = 0;//,y3_last = 0;
	float ka1 = 0.1367287,kb1 = 0.1367287,kc1 = 0.7265426;
	float ka2 = 0.059191,kb2 = 0.059191,kc2 = 0.881618;
//	float Ka3 = 0.001568,Kb3 = 0.001568,Kc3 = 0.996864;
	
	if(breath_pressure_sensor.counter < 50)
	{
		breath_pressure_sensor.ADC_temp1[i] = Get_ADC1(ch);

		breath_pressure_sensor.x = breath_pressure_sensor.ADC_temp1[i] ;

		i++;

		if(i == 10)
		{
			i = 0;

			for(j=0;j<10;j++)
			{
				breath_pressure_sensor.ADC_temp2[breath_pressure_sensor.counter] += breath_pressure_sensor.ADC_temp1[j];
			}
			breath_pressure_sensor.ADC_temp2[breath_pressure_sensor.counter] = breath_pressure_sensor.ADC_temp2[breath_pressure_sensor.counter]/10;
			breath_pressure_sensor.counter++;
			
			if(breath_pressure_sensor.counter == 50)
			{
				for(j=0;j<50;j++)
				{
					breath_pressure_sensor.pressure_zero += breath_pressure_sensor.ADC_temp2[j];
				}
				breath_pressure_sensor.pressure_zero = breath_pressure_sensor.pressure_zero/50;
				breath_pressure_sensor.ADC_cs_flag = SET;
			}
			
		}
	}
	else
	{
		if(breath_pressure_sensor.ADC_cs_flag)
		{
			breath_pressure_sensor.x = Get_ADC1(ch);//ADC_Smooth_Filter
			
			breath_pressure_sensor.y1 = ka1*breath_pressure_sensor.x + kb1*x_last + kc1*y1_last;
			
			breath_pressure_sensor.y2 = ka2*breath_pressure_sensor.y1 + kb2*y1_last + kc2*y2_last;
			
		//	breath_pressure_sensor.y3 = Ka3*breath_pressure_sensor.y2 + Kb3*y2_last + Kc3*y3_last;
			
			x_last = breath_pressure_sensor.x;
			y1_last = breath_pressure_sensor.y1;
			y2_last = breath_pressure_sensor.y2;
		//	y3_last = breath_pressure_sensor.y3;

			if (breath_pressure_sensor.y2 >= breath_pressure_sensor.pressure_zero)
			{
				breath_pressure_sensor.y = breath_pressure_sensor.y2 - breath_pressure_sensor.pressure_zero;
			}
			else
			{
				breath_pressure_sensor.y = 0;
			}
		//	breath_pressure_sensor.y = breath_pressure_sensor.y2 - breath_pressure_sensor.y3;				
			
		}


	}	
	return 0;
}


/**
  * @brief		Initial ADC2.
  *         
  * @param[in]	None.
  *         
  * @return		None.
  */
void ADC2_Init(void)	
{
	ADC_InitTypeDef 	ADC_InitStructure; 
	GPIO_InitTypeDef 	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC2,ENABLE );
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); 
                     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	ADC_DeInit(ADC2);  

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC2, &ADC_InitStructure);	  

	ADC_Cmd(ADC2, ENABLE);	
	
	ADC_ResetCalibration(ADC2);	
	 
	while(ADC_GetResetCalibrationStatus(ADC2));	
	
	ADC_StartCalibration(ADC2);	

	while(ADC_GetCalibrationStatus(ADC2));	

//	ADC_SoftwareStartConvCmd(ADC2, ENABLE);		
}


/**
  * @brief			Get ADC2.
  *         
  * @param[in]	u8 ch.
  *         
  * @return			ADC_GetConversionValue(ADC2).
  */
u16 Get_ADC2(u8 ch)   
{
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC2,converting time: (239.5+12.5)/12 = 21us		    
  
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);	 
	
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC )); 

	return ADC_GetConversionValue(ADC2);	 
}

/**
  * @brief			ADC2_Handle.
  *         
  * @param[in]	u8 ch.
  *         
  * @return			none.
  *
	* @note formula
	*	@note y1=¦Á*x(0)+¦Â*x(0-1)+¦Ã*y1(0-1)			
	*	@note y2=¦Á*y1+¦Â*y1(0-1)+¦Ã*y2(0-1)			
	*	@note y3=¦Á*y2+¦Â*y2(0-1)+¦Ã*y3(0-1)			
 */
u16 ADC2_Handle(u8 ch)
{
	static u8 i = 0,j = 0;
  static float x_last = 0,y1_last = 0,y2_last = 0;//,y3_last = 0;
	float ka1 = 0.1367287,kb1 = 0.1367287,kc1 = 0.7265426;
	float ka2 = 0.059191,kb2 = 0.059191,kc2 = 0.881618;
//	float Ka3 = 0.001568,Kb3 = 0.001568,Kc3 = 0.996864;
	
	if(system_pressure_sensor.counter < 50)
	{
		system_pressure_sensor.ADC_temp1[i] = Get_ADC2(ch);

		system_pressure_sensor.x = system_pressure_sensor.ADC_temp1[i] ;

		i++;

		if(i == 10)
		{
			i = 0;

			for(j=0;j<10;j++)
			{
				system_pressure_sensor.ADC_temp2[system_pressure_sensor.counter] += system_pressure_sensor.ADC_temp1[j];
			}
			system_pressure_sensor.ADC_temp2[system_pressure_sensor.counter] = system_pressure_sensor.ADC_temp2[system_pressure_sensor.counter]/10;
			system_pressure_sensor.counter++;
			
			if(system_pressure_sensor.counter == 50)
			{
				for(j=0;j<50;j++)
				{
					system_pressure_sensor.pressure_zero += system_pressure_sensor.ADC_temp2[j];
				}
				system_pressure_sensor.pressure_zero = system_pressure_sensor.pressure_zero/50;
				system_pressure_sensor.ADC_cs_flag = SET;
			}
			
		}
	}
	else
	{
		if(system_pressure_sensor.ADC_cs_flag)
		{
			system_pressure_sensor.x = Get_ADC2(ch);//ADC_Smooth_Filter
			
			system_pressure_sensor.y1 = ka1*system_pressure_sensor.x + kb1*x_last + kc1*y1_last;
			
			system_pressure_sensor.y2 = ka2*system_pressure_sensor.y1 + kb2*y1_last + kc2*y2_last;
			
		//	system_pressure_sensor.y3 = Ka3*system_pressure_sensor.y2 + Kb3*y2_last + Kc3*y3_last;
			
			x_last = system_pressure_sensor.x;
			y1_last = system_pressure_sensor.y1;
			y2_last = system_pressure_sensor.y2;
		//	y3_last = system_pressure_sensor.y3;

			if (system_pressure_sensor.y2 >= system_pressure_sensor.pressure_zero)
			{
				system_pressure_sensor.y = system_pressure_sensor.y2 - system_pressure_sensor.pressure_zero;
			}
			else
			{
				system_pressure_sensor.y = 0;
			}
		//	system_pressure_sensor.y = system_pressure_sensor.y2 - system_pressure_sensor.y3;				
			
		}


	}	
	return 0;
}


/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
