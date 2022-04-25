/**
  ******************************************************************************
  * @file    DrvKey.c
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about the buttons.
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
#include "DrvKey.h"

/**
  * @brief  		Initial GPIO for buttons.
  *         
  * @param[in] 	None
  *         
  * @return 		None
  *  
	* @note				All the IOs are NPN type.
  */
void Key_Init(void)  
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * @brief  		Get the status of the key.
  *         
  * @param[in] 	u8 key_num.
  *         
  * @return 		bitstatus.
  */
FlagStatus Key_GetFlagStatus(u8 key_num)
{
  FlagStatus bitstatus = RESET;
	u8 counter = 0;
	
	switch(key_num){
		case KEY1_STATUS:	
				if(!KEY1){
					Delay_Ms(5);
					if(!KEY1){
						while(!KEY1){
								if(!KEY2){
									Delay_Ms(5);
									if(!KEY2){
										while(!KEY2){
											if(key_timer2_100ms_flag){
												key_timer2_100ms_flag = RESET;
												counter ++;
											}
											if(counter > 30){/*Waiting the key1 and key2 to be triggered for 5s at the same time.*/
												counter = 0;
												if(system.mode == MODE_STANDBY){
//													system.mode = MODE_DEBUG;
//													bitstatus = RESET;
//												}
//												else if(system.mode == MODE_DEBUG){
													system.keys_ack = SET;
													bitstatus = RESET;
												}
												return bitstatus;
											}
										}
									}
								}
								else{
									bitstatus = SET;
								}
						}
					}
				}
				break;
	
		case KEY2_STATUS:	
				if(!KEY2){
					Delay_Ms(5);
					if(!KEY2){
						while(!KEY2){
								if(!KEY1){
									Delay_Ms(5);
									if(!KEY1){
										while(!KEY1){
											if(key_timer2_100ms_flag){
												key_timer2_100ms_flag = RESET;
												counter ++;
											}
											if(counter > 30){/*Waiting the key1 and key2 to be triggered for 5s at the same time.*/
												counter = 0;
												if(system.mode == MODE_STANDBY){
//													system.mode = MODE_DEBUG;
//													bitstatus = RESET;
//												}
//												else if(system.mode == MODE_DEBUG){
													system.keys_ack = SET;
													bitstatus = RESET;
												}
												return bitstatus;
											}
										}
									}
								}
								else{
									bitstatus = SET;
								}
						}
					}
				}
				break;

		case KEY3_STATUS:	
				if(!KEY3){
					Delay_Ms(5);
					if(!KEY3){
						while(!KEY3){
									;
								}
						bitstatus = SET;
						}
					}
				break;				
						
		case KEY4_STATUS:	
				if(!KEY4){
					Delay_Ms(5);
					if(!KEY4){
						while(!KEY4){
									;
								}
						bitstatus = SET;
						}
					}
				break;				

		case KEY5_STATUS:	
				if(!KEY5){
					Delay_Ms(5);
					if(!KEY5){
						while(!KEY5){
									;
								}
						bitstatus = SET;
						}
					}
				break;							
	
		default:	
			bitstatus = RESET;	
			break;
	}
	
	return bitstatus;
}


/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
