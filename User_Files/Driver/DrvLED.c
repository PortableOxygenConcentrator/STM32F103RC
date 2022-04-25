/**
  ******************************************************************************
  * @file    DrvLed.c
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about LED.
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
#include "DrvLed.h"

/**
  * @brief  		Vavle initial function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	* @note				All the IOs are NPN type.
  */
void LED_Init(void) 
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

}


/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
