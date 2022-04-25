/**
  ******************************************************************************
  * @file    MidTime.c
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about time. 
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
#include "MidTime.h"

u8 minutes_count = 0;

/**
  * @brief  		Calculate accumulate time function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	* @note				None
  */
void CalculateAccumulateTime(void)
{
	if(system.vavle_start_up_flag){		
		system.time_1s_count ++;
	}	
	
	if(system.time_1s_count >= 60){ //1min = 60s
		system.time_1s_count = 0;
		
		system.single_time ++;/*The value will be cleared when the power is off.*/
	
		minutes_count ++;
	}
	
	system.real_accumulate_time = system.single_time + system.accumulate_time;

	system.accumulate_display_time = system.real_accumulate_time/60;/*Display units:hour*/
	if(system.accumulate_display_time > 99999){
		system.accumulate_display_time = 99999;
	}
	
	
}

/**
  * @brief  		Save accumulated time function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	* @note				None
  */
void SaveAccumulatedTime(void)
{
	/*Store the time per minute,and the flash can live about 6 years.*/
	if(minutes_count >= 1){ 	
		minutes_count = 0;
		
		system.flash_memory[1] = (u16) system.real_accumulate_time; 
		system.flash_memory[0] = (u16) (system.real_accumulate_time>>16); 
		
		STMFLASH_Write(FLASH_BASE_ADDRESS,(u16 *)system.flash_memory,2);			

	}		
}

/**
  * @brief  		Handle time function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	* @note				None
  */
void TimeHandle(void)
{
	CalculateAccumulateTime();
	SaveAccumulatedTime();
}




/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
