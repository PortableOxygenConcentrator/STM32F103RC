/**
  ******************************************************************************
  * @file		DrvValve.c
  * @author	Best Team
  * @version	V1.0.0
  * @date		6-April-2021
  * @brief	This file provides the functions about valve control. 
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
#include "DrvVavle.h"

/**
  * @brief  		Vavle initial function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	* @note				All the IOs are PNP type.
  */
void Vavle_Init(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC,ENABLE);				
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_11 ;			
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);   

	/*Set Pins off*/
 	GPIO_ResetBits(GPIOA,GPIO_Pin_12 | GPIO_Pin_11); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;			
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);   

	/*Set Pins off*/
 	GPIO_ResetBits(GPIOC,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2); 
	
}

/**
  * @brief  		O2 Vavle control function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void O2_Vavle_Control(void)
{	
	static u16	valve_toggle_time_count = 0;
	static u16 t1 = 0,t2 = 0,t3 = 0,t4 = 0,t5 = 0,t6 = 0;
	static u8 valve_toggle_count = 0;
	static FlagStatus vavle_toggle_done_flag = RESET;
		
	/*Time calculate*/
	t1 = system.pressure_time1;
	t2 = system.pressure_time1 + system.pressure_time2;
	t3 = system.pressure_time1 + system.pressure_time2 + system.pressure_time3;
	t4 = (2*system.pressure_time1) + system.pressure_time2 + system.pressure_time3;
	t5 = (2*system.pressure_time1) + (2*system.pressure_time2) + system.pressure_time3;
	t6 = (2*system.pressure_time1) + (2*system.pressure_time2) + (2*system.pressure_time3);
	
	if(system.vavle_start_up_flag){
		if(!vavle_toggle_done_flag){
			if(O2_vavle_timer2_10ms_flag){
				O2_vavle_timer2_10ms_flag = RESET;
				
				valve_toggle_time_count++;
				
				if(valve_toggle_time_count == 50){
					VAVLE_O2_1 = SET;
					VAVLE_O2_2 = RESET;	
				}
				
				if(valve_toggle_time_count >= 100){
					VAVLE_O2_1 = RESET;
					VAVLE_O2_2 = SET;	
					valve_toggle_count ++;			 
					valve_toggle_time_count = 0;	
				}
			
			}
			
			if(valve_toggle_count >= 5){			
				valve_toggle_count = 0;
				vavle_toggle_done_flag = SET;
			}
		}	
		else if((system.mode == MODE_OXYGENERATE) || (system.mode == MODE_AI)){		

			if(O2_vavle_timer2_10ms_flag){
				O2_vavle_timer2_10ms_flag = RESET;

				valve_toggle_time_count ++;	

				if(valve_toggle_time_count == t1){
				
					VAVLE_O2_1 = SET;
					VAVLE_O2_2 = SET;	
					VAVLE_AVG  = SET;	
				}
				
				if(valve_toggle_time_count == t2){
				
					VAVLE_O2_1 = RESET;
					VAVLE_O2_2 = SET;	
					VAVLE_AVG  = RESET;
				}
				
				if(valve_toggle_time_count == t3){ 
				
					VAVLE_O2_1 = RESET;
					VAVLE_O2_2 = SET;	
					VAVLE_AVG  = SET;	
				}
				
				if(valve_toggle_time_count == t4){ 
				
					VAVLE_O2_1 = SET;
					VAVLE_O2_2 = SET;	
					VAVLE_AVG  = SET;	
				}

				if(valve_toggle_time_count == t5){ 
				
					VAVLE_O2_1 = SET;
					VAVLE_O2_2 = RESET;	
					VAVLE_AVG  = RESET;	
				}
				
				if(valve_toggle_time_count >= t6){
				
					VAVLE_O2_1 = SET;
					VAVLE_O2_2 = RESET;	
					VAVLE_AVG  = SET;	
								
					valve_toggle_time_count = 0;	
				}
				
			}
		}
	}
	else{
		valve_toggle_count = 0;
		vavle_toggle_done_flag = RESET;
		
	}
}



/**
  * @brief  		Breath Vavle control function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  * @formula		t_vavle = 10xy + 20y;
  *  
  */	
	u16 t_vavle = 0;	
	u16 t_vavle_last = 0;
	u16 t_vavle_no_breath = 0;
	u16 t_breath = 0;
	u16 t_no_breath = 0;
	u16 respiratory_rate = 0;	
	u16 breath_vavle_timer2_10ms_count = 0;	

void Breath_Vavle_Control(void)
{		
//	static u16 t_vavle = 0;	
//	static u16 t_vavle_last = 0;
//	static u16 t_vavle_no_breath = 0;
//	static u16 t_breath = 0;
//	static u16 t_no_breath = 0;
//	static u16 respiratory_rate = 0;	
//	static u16 breath_vavle_timer2_10ms_count = 0;	

	static FlagStatus breath_start_up_flag = RESET;
	static FlagStatus first_breath_done_flag = RESET;
	static FlagStatus second_breath_done_flag = RESET;
	static FlagStatus breath_flag = RESET;
	static FlagStatus vavle_close_flag = RESET;

	VAVLE_DIR = RESET;
	
	/*Calculate the time between the latest two breath.*/
	{
		/*Start the time counter.*/	
		if( (!first_breath_done_flag) && (!vavle_close_flag) ){
			if(breath_pressure_sensor.y > 60){		
				breath_start_up_flag = SET;	
			}
			
			/*Wait the pressure return to 0. Then set the first_breath_done_flag.*/
			if( (breath_pressure_sensor.y < 5) && (breath_start_up_flag)){
				first_breath_done_flag = SET;
			}	
		}
		
		/*Stop the time counter.*/
		if(first_breath_done_flag){
			if(breath_pressure_sensor.y > 60){		
				breath_start_up_flag = RESET;
				second_breath_done_flag = SET;
			}
		}
		
		/*Calculate the breath time.*/
		if(breath_start_up_flag){
				if(breath_sensor_timer2_10ms_flag){
					breath_sensor_timer2_10ms_flag = RESET;
					t_breath++;
					
					if(t_breath >= 6000){
						t_breath = 6000;
					}
				}
		}
		
		/*Calculate the no breath time.*/
		if(!breath_flag){
				if(no_breath_timer2_10ms_flag){
					no_breath_timer2_10ms_flag = RESET;
					t_no_breath++;
				}
		}	

		/*If the time is larger than 4s,open the vavle 500ms to release the pressure.*/
		if(t_no_breath >= 500){
			VAVLE_AI = SET;
			t_vavle_no_breath = (0.2 * system.grade + 0.4) * 0.05 * 400;
			
			/*Count the time the vavle opens.*/
			if(breath_vavle_timer2_10ms_flag){
				breath_vavle_timer2_10ms_flag = RESET;
				breath_vavle_timer2_10ms_count ++;
				
				/*Close the vavle when the time is up.*/
				if(breath_vavle_timer2_10ms_count > t_vavle_no_breath){
					breath_vavle_timer2_10ms_count = 0;					
					VAVLE_AI = RESET;
					t_breath = 0;
					t_no_breath = 0;					
				}
			}
		}
		else{
		
		}
		
		/*Calculate the time that the vavle needs.*/
		t_vavle = (0.2 * system.grade + 0.4) * 0.05 * t_breath;		
		
		
	}


	/*Control the breath vavle.*/
	{	
		/*Open the breath vavle.*/
		if(second_breath_done_flag){
			t_vavle_last = t_vavle;
			/*System respiratory rate*/
			if(t_breath > 0){
				respiratory_rate = 6000/t_breath;
			}
			system.respiratory_rate = (respiratory_rate > 60 ? 60 : respiratory_rate);								
			breath_flag = SET;	
			VAVLE_AI = SET;		
			first_breath_done_flag = RESET;
			second_breath_done_flag  = RESET;	
			breath_pressure_sensor.ADC_cs_flag = RESET;		
			t_no_breath = 0;			
		}

		/*Close the breath vavle.*/
		if(breath_flag){
			/*Count the time the vavle opens.*/
			if(breath_vavle_timer2_10ms_flag){
				breath_vavle_timer2_10ms_flag = RESET;
				breath_vavle_timer2_10ms_count ++;
				
				/*Limit the time the vavle opens.*/
				if(breath_vavle_timer2_10ms_count > 1000){
					breath_vavle_timer2_10ms_count = 1000;
				}
			}
			/*Judge the time when the vavle should close.*/
			if(breath_vavle_timer2_10ms_count >= t_vavle_last){
				VAVLE_AI = RESET;
				vavle_close_flag = SET;
				breath_flag = RESET;				
				breath_vavle_timer2_10ms_count = 0;	
				t_breath = 0;							
			}		
		}		
			
		/*Wait 1.0s to enable the ADC of breath.*/
		if(vavle_close_flag){
			if(breath_vavle_timer2_10ms_flag){
				breath_vavle_timer2_10ms_flag = RESET;
				breath_vavle_timer2_10ms_count ++;
			}

			if(breath_vavle_timer2_10ms_count >= 90){
				breath_pressure_sensor.ADC_cs_flag = SET;
			}				
			
			if(breath_vavle_timer2_10ms_count >= 100){
				breath_vavle_timer2_10ms_count = 0;
				vavle_close_flag = RESET;
			}
		}		
		
	}

}
		
/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
