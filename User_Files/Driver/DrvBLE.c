/**
  ******************************************************************************
  * @file    DrvBLE.c
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about bluetooth.. 
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
#include "DrvBLE.h"

/**
  * @brief  		Bluetooth initial function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	* @note				None.
  */
void Bluetooth_Initial(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);				
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;			
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);   

	/*Set Pins off*/
 	GPIO_ResetBits(GPIOA,GPIO_Pin_15); 
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;			
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);   

	/*Set Pins off*/
 	GPIO_ResetBits(GPIOB,GPIO_Pin_3 | GPIO_Pin_4); 	
	
	
	BLUETOOTH_RESET_OFF;
	Delay_Us(1000);/*At least 600us.*/
	BLUETOOTH_RESET_ON;
	
	BLUETOOTH_WAKEUP;
	

}




		
/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
