/**
  ******************************************************************************
  * @file    MidBLDC.c
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about BLDC.. 
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
#include "MidBLDC.h"

/**
  * @brief  		BLDC initial function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	* @note				All the IOs are PNP type.
  */
void BLDC_Init(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);				
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);				
	
	/*BLDC enable pin*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);   

	/*Set Pins off*/
 	GPIO_ResetBits(GPIOB,GPIO_Pin_8); 
	
	/*Set Pins on*/
	ENBLDC = SET;
	
}

	/**
  * @brief  		BLDC control function. 
  *         
  * @param[in]	u16 speed (0~100)
  *         
  * @return 		None
  *  
  */
void BLDC_Control(u16 speed)
{	

	/*Limit the speed to 4000*/
	if(speed > 4000){
		speed  = 4000;
	}
	
	/*Limit the speed to 400*/
	if(speed < 400){
		speed  = 400;
	}

	/*Speed control*/
	if(modbus_timer2_100ms_flag){
		modbus_timer2_100ms_flag = RESET;
		
		CMD_Modbus(0x01, 0x06, 0x13, speed);
	}
	
}



/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
