/**
  ******************************************************************************
  * @file    DrvPower.c
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about the power. 
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
#include "DrvPower.h"

/**
  * @brief  		Initial GPIO for power.
  *         
  * @param[in] 	None
  *         
  * @return 		None
  *  
	* @note				
  */
void Adapter_Check_Init(void)  
{ 
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

/**
  * @brief  		Power 12V initial function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	* @note				All the IOs are PNP type.
  */
void Power_12V_Init(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);				
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);   

	/*Set Pins off*/
 	GPIO_ResetBits(GPIOC,GPIO_Pin_3); 
	

	
}


/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
