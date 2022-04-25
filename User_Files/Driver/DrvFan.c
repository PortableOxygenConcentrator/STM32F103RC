/**
  ******************************************************************************
  * @file		DrvFan.c
  * @author	Best Team
  * @version	V1.0.0
  * @date		24-June-2021
  * @brief	This file provides the functions about valve fan. 
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
#include "DrvFan.h"

/**
  * @brief  		Fan initial function. 
  *         
  * @param[in]	None.
  *         
  * @return 		None.
  *  
	* @note				All the IOs are PNP type.
	*
	* @note				PA7:Fan speed; PA10:Fan enable.
	*
  */
void Fan_Init(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);				
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);   

/*Set Pins off*/
 	GPIO_ResetBits(GPIOA,GPIO_Pin_10); 
	
	
	/*Initial TIM3,the speed control function. */
	TIM3_PWM_Init(899,0);		//72000000/900=80Khz
	
}

/**
  * @brief  		Fan control function. 
  *
  * @param[in]	u16 speed.
  *
  * @return 		None.
  *
	* @note				All the IOs are PNP type.
  */
void Fan_Ctrl(u16 speed)
{
/*Enable the fan.*/
	FAN_EN  = SET;
	
	TIM_SetCompare2(TIM3,speed);	
	
}

		
/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
