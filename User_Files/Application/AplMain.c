/**
  ******************************************************************************
  * @file    AplMain.c
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides all the main functions. 
  ******************************************************************************
  * @attention
  *
  *	THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "AplMain.h"


/**
  * @brief  		Handling all the initial functions and loop function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
int main(void)
{
	
/*Initial function*/
	Initial();
		
/*Loop function*/
	while(1)
	{	
//		point_color = Color2;	
//		back_color = BLACK;

//		Mid_LCD_ShowNum(10,100,breath_pressure_sensor.pressure_zero,4,12);
//		Mid_LCD_ShowNum(10,110,breath_pressure_sensor.x,4,12);
		
//		Mid_LCD_ShowNum(10,130,system_pressure_sensor.pressure_zero,4,12);
//		Mid_LCD_ShowNum(10,140,system_pressure_sensor.x,4,12);
		
//		Mid_LCD_ShowNum(10,160,system.FAN_Speed,5,12);
//	
//		Mid_LCD_ShowNum(10,170,system.BLDC_Speed,5,12);
		
//		Mid_LCD_ShowNum(10,160,t_vavle_last,5,12);
//	
//		Mid_LCD_ShowNum(10,170,t_vavle,5,12);		

//	Mid_LCD_Fill(0,120,120,130,GREEN);
//	Delay_Ms(500);
//		
//	Mid_LCD_Fill(0,120,120,130,YELLOW);
//	Delay_Ms(500);
//		
//	Mid_LCD_Fill(0,120,120,130,RED);
//	Delay_Ms(500);



//	LCD_Address_Set(100,100,100,100);



//	Mid_LCD_SetCursor(120,120);		



/*
if(Key_GetFlagStatus(KEY2_STATUS)){
	Drv_LCD_WR_REG(0X2A); 
	Drv_LCD_WR_DATA(100 >> 8);
	Drv_LCD_WR_DATA(100 & 0XFF); 	
	Drv_LCD_WR_DATA(120 >> 8);
	Drv_LCD_WR_DATA(120 & 0XFF); 		
	
	Drv_LCD_WR_REG(0X2B); 
	Drv_LCD_WR_DATA(100 >> 8);
	Drv_LCD_WR_DATA(100 & 0XFF); 	
	Drv_LCD_WR_DATA(120 >> 8);
	Drv_LCD_WR_DATA(120 & 0XFF); 	
	
	Drv_LCD_WR_REG(0X2C);			

	Drv_LCD_WR_DATA(RED >> 8);		
	Drv_LCD_WR_DATA(RED & 0XFF);	
	
	Drv_LCD_WR_DATA(RED >> 8);		
	Drv_LCD_WR_DATA(RED & 0XFF);

	Drv_LCD_WR_DATA(RED >> 8);		
	Drv_LCD_WR_DATA(RED & 0XFF);
	
	Drv_LCD_WR_DATA(RED >> 8);		
	Drv_LCD_WR_DATA(RED & 0XFF);
}

if(Key_GetFlagStatus(KEY3_STATUS)){
	Drv_LCD_WR_REG(0X2A); 
	Drv_LCD_WR_DATA(200 >> 8);
	Drv_LCD_WR_DATA(200 & 0XFF); 	
	Drv_LCD_WR_DATA(220 >> 8);
	Drv_LCD_WR_DATA(220 & 0XFF); 		
	
	Drv_LCD_WR_REG(0X2B); 
	Drv_LCD_WR_DATA(200 >> 8);
	Drv_LCD_WR_DATA(200 & 0XFF); 	
	Drv_LCD_WR_DATA(220 >> 8);
	Drv_LCD_WR_DATA(220 & 0XFF); 		
	
	Drv_LCD_WR_REG(0X2C);			

	Drv_LCD_WR_DATA(BLUE >> 8);		
	Drv_LCD_WR_DATA(BLUE & 0XFF);	
	
	Drv_LCD_WR_DATA(BLUE >> 8);		
	Drv_LCD_WR_DATA(BLUE & 0XFF);	
	
	Drv_LCD_WR_DATA(BLUE >> 8);		
	Drv_LCD_WR_DATA(BLUE & 0XFF);	
	
	Drv_LCD_WR_DATA(BLUE >> 8);		
	Drv_LCD_WR_DATA(BLUE & 0XFF);	
	
	
}
*/

if(Key_GetFlagStatus(KEY1_STATUS)){
/*Clear LCD with black*/	
	Mid_LCD_Clear(WHITE);	
}
if(Key_GetFlagStatus(KEY2_STATUS)){
/*Clear LCD with black*/	
	Mid_LCD_Clear(BLACK);	
}
if(Key_GetFlagStatus(KEY3_STATUS)){
/*Clear LCD with black*/	
	Mid_LCD_Clear(RED);	
}
if(Key_GetFlagStatus(KEY4_STATUS)){
/*Clear LCD with black*/	
	Mid_LCD_Clear(BLUE);	
	LCD_ShowIcon(8,60,CASE_ELLIPSE,Color1,BLACK,0);
}

//	DrawLine(0,120,120,140,RED);

//	DispStr("test",100,200,RED,GREEN,8,16); 
//	
	

//	Mid_LCD_WriteOnePix(120,80,RED);

//Delay_Ms(500);
	
//		Mid_LCD_ShowNum(170,10,system.grade,2,12);
		
//		Handle_O2_Sensor_Data();
		
//		Mode_Judgement();
	
//		WriteChargerParameters();

//		ReadChargerParameters();
	}

}




/**
  * @brief		Initial all divices and CPU
  *         
  * @param[in]	None
  *         
  * @return		None
  */
void Initial(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	Delay_Init();	 
	
	Key_Init();				
	
	Vavle_Init();		
	
	Fan_Init();
	
	Power_12V_Init();
	
//	LED_Init();		
	
//	Adapter_Check_Init();
	
//	Bluetooth_Initial();
	
///*ADC1 Init.*/	
//	ADC1_Init();	
//	
///*ADC2 Init.*/	
//	ADC2_Init();
//	
///*BLE module.*/
////	UART5_Init(9600);

///*BLDC module.*/
//	BLDC_Init();

///*SMbus module.*/
//	SMbus_Init();

///*BLDC module.*/	
//	UART4_Init(9600);

///*O2 sensor module.*/
//	USART3_Init(9600);	
//	
///*Initial TIM2 */
//	TIM2_Init(99,7199);			//10Khz，100 10ms  The base timer

///*Initial TIM4 */	
////	TIM4_Cap_Init(0XFFFFFFFF,8);	//8Mhz 
//	
///*Initial TIM5 */	
//	TIM5_Init(99,7199);			//7199:10Khz，100: 10ms  O2 vavle
//	
///*Initial TIM6 */	
//	TIM6_Init(9999,7199);		//7199:10Khz，10000: 1s Time and UI display
//	
///*Initial TIM7 */	
//	TIM7_Init(99,7199);			//7199:10Khz，100: 10ms ADC of pressure 

///*Initial TIM8 */	
//	TIM8_Init(99,7199);			//7199:10Khz，100: 10ms  Breath vavle

	ReadParameters();

	system.mode = MODE_STANDBY;
	
	system.grade = 1;
	
/*Initial LCD*/
	Mid_LCD_Init();	

}



/**
  * @brief  		Standby mode function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void Mode_Standby_Function(void)
{			
/*Disable BLDC*/
	ENBLDC = RESET;
	
/*system start up.*/	
	system.vavle_start_up_flag = RESET;
		
/*Disable 12V power.*/
	EN12V = RESET;				
		
/*Turn off all the fans*/
	FAN_EN  = RESET;

/*Turn off all the vavles*/
	VAVLE_O2_1 = RESET;
	VAVLE_O2_2 = RESET;
	VAVLE_AVG  = RESET;
	VAVLE_DIR  = RESET;
	VAVLE_AI   = RESET;			
	
/*System grade will be set to 1*/	
	system.grade = 1;
}

/**
  * @brief  		Oxygen generate mode function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void Mode_Oxygen_Generate_Function(void)
{
/*Turn on all the fans.*/
	Fan_Ctrl(system.FAN_Speed);
	FAN_EN  = SET;
		
/*Enable BLDC.*/
	ENBLDC = SET;
	
/*Enable 12V power.*/
	EN12V = SET;
	
/*system start up*/			
	if(!system.vavle_start_up_flag){
	/*Turn on all the o2 vavles*/
		VAVLE_O2_1 = SET;
		VAVLE_O2_2 = SET;
		VAVLE_DIR  = SET;
		
		system.vavle_start_up_flag = SET;  
	}
	
/*BLDC speed control*/		
 	BLDC_Control(system.BLDC_Speed);

}


/**
  * @brief  		Atomization mode function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void Mode_Atomization_Function(void)
{
/*Turn on all the fans*/
	Fan_Ctrl(system.FAN_Speed);
	FAN_EN  = SET;

/*Turn on the direct-O2-supply vavle.*/
	VAVLE_DIR  = SET;
	
/*Turn off the AI vavle.*/	
	VAVLE_AI   = RESET;

/*Turn on all the o2 vavles*/
	VAVLE_O2_1 = SET;
	VAVLE_O2_2 = SET;	
	
/*Enable BLDC*/
	ENBLDC = SET;
	
/*Enable 12V power*/
	EN12V = SET;
	

/*BLDC speed control*/		
	BLDC_Control(system.BLDC_Speed);

}	


/**
  * @brief  		AI mode function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void Mode_AI_Function(void)
{
/*Turn on all the fans*/
	Fan_Ctrl(system.FAN_Speed);
	FAN_EN  = SET;
	
/*Turn off the direct-O2-supply vavle.*/
	VAVLE_DIR  = RESET;
		
/*Enable BLDC*/
	ENBLDC = SET;
	
/*Enable 12V power*/
	EN12V = SET;
	
/*BLDC speed control*/		
	BLDC_Control(system.BLDC_Speed);

}



/**
  * @brief  		Debug mode function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void Mode_Debug_Function(void)
{
	s8 menu = 0;

	point_color = Color2;
	back_color = BLACK;	

	debug_state:
		
		if(Key_GetFlagStatus(KEY1_STATUS)){
			menu --;
			if(menu < 1){
				menu = 0;
			}
		}
		
		if(Key_GetFlagStatus(KEY2_STATUS)){
			menu ++;
			if(menu > 5){
				menu = 5;
			}		
		}	
		
		if(Key_GetFlagStatus(KEY4_STATUS)){
			system.mode = MODE_STANDBY;
			/*Return from debug state.*/
			return;
		}			

		/*Select the parameter to set.*/	
		switch (menu)
		{
			case 0:

				back_color = WHITE;	
				Mid_LCD_ShowNum(150,35,system.pressure_time1,12,12);		
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,65,system.pressure_time2,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,95,system.pressure_time3,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,125,system.pressure_time4,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,155,system.pressure_time5,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,185,system.pressure_time6,12,12);
			
				if(Key_GetFlagStatus(KEY3_STATUS)){
					while(1){
						if(Key_GetFlagStatus(KEY2_STATUS)){
							/*Set the pressure time1*/
							system.pressure_time1 -= 1;
							if(system.pressure_time1 < 1){
								system.pressure_time1 = 0;
							}
						}
						
						if(Key_GetFlagStatus(KEY1_STATUS)){
							/*Set the pressure_time1*/
							system.pressure_time1 += 1;
							if(system.pressure_time1 > 1000){
								system.pressure_time1 = 1000;
							}		
						}	
						if(Key_GetFlagStatus(KEY3_STATUS)){
							system.flash_memory[2] = (u16)system.pressure_time1;
							STMFLASH_Write(FLASH_BASE_ADDRESS,(u16 *)system.flash_memory,10);
							break;
						}
						
						back_color = RED;
						Mid_LCD_ShowNum(150,35,system.pressure_time1,12,12);	
					}
				}
				break;
			
			case 1:

				back_color = BLACK;	
				Mid_LCD_ShowNum(150,35,system.pressure_time1,12,12);		
			
				back_color = WHITE;			
				Mid_LCD_ShowNum(150,65,system.pressure_time2,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,95,system.pressure_time3,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,125,system.pressure_time4,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,155,system.pressure_time5,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,185,system.pressure_time6,12,12);
			
				if(Key_GetFlagStatus(KEY3_STATUS)){					
					while(1){
						if(Key_GetFlagStatus(KEY2_STATUS)){
							/*Set the pressure_time2*/
							system.pressure_time2 -= 1;
							if(system.pressure_time2 < 1){
								system.pressure_time2 = 0;
							}
						}
						
						if(Key_GetFlagStatus(KEY1_STATUS)){
							/*Set the pressure_time2*/
							system.pressure_time2 += 1;
							if(system.pressure_time2 > 1000){
								system.pressure_time2 = 1000;
							}		
						}	
						if(Key_GetFlagStatus(KEY3_STATUS)){
							system.flash_memory[3] = (u16)system.pressure_time2;
							STMFLASH_Write(FLASH_BASE_ADDRESS,(u16 *)system.flash_memory,10);
							break;
						}
						back_color = RED;
						Mid_LCD_ShowNum(150,65,system.pressure_time2,12,12);
					}
				}			
				break;

			case 2:

				back_color = BLACK;	
				Mid_LCD_ShowNum(150,35,system.pressure_time1,12,12);		
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,65,system.pressure_time2,12,12);
			
				back_color = WHITE;			
				Mid_LCD_ShowNum(150,95,system.pressure_time3,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,125,system.pressure_time4,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,155,system.pressure_time5,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,185,system.pressure_time6,12,12);
			
				if(Key_GetFlagStatus(KEY3_STATUS)){					
					while(1){
						if(Key_GetFlagStatus(KEY2_STATUS)){
							/*Set the pressure_time3*/
							system.pressure_time3 -= 1;
							if(system.pressure_time3 < 1){
								system.pressure_time3 = 0;
							}
						}
						
						if(Key_GetFlagStatus(KEY1_STATUS)){
							/*Set the pressure_time3*/
							system.pressure_time3 += 1;
							if(system.pressure_time3 > 1000){
								system.pressure_time3 = 1000;
							}		
						}	
						if(Key_GetFlagStatus(KEY3_STATUS)){
							system.flash_memory[4] = (u16)system.pressure_time3;
							STMFLASH_Write(FLASH_BASE_ADDRESS,(u16 *)system.flash_memory,10);
							break;
						}
						back_color = RED;
						Mid_LCD_ShowNum(150,95,system.pressure_time3,12,12);	
					}
				}
				break;
			
			case 3:

				back_color = BLACK;	
				Mid_LCD_ShowNum(150,35,system.pressure_time1,12,12);		
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,65,system.pressure_time2,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,95,system.pressure_time3,12,12);
			
				back_color = WHITE;			
				Mid_LCD_ShowNum(150,125,system.pressure_time4,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,155,system.pressure_time5,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,185,system.pressure_time6,12,12);
			
				if(Key_GetFlagStatus(KEY3_STATUS)){
					while(1){
						if(Key_GetFlagStatus(KEY2_STATUS)){
							/*Set the pressure_time4*/
							system.pressure_time4 -= 1;
							if(system.pressure_time4 < 1){
								system.pressure_time4 = 0;
							}
						}
						
						if(Key_GetFlagStatus(KEY1_STATUS)){
							/*Set the pressure_time4*/
							system.pressure_time4 += 1;
							if(system.pressure_time4 > 1000){
								system.pressure_time4 = 1000;
							}		
						}	
						if(Key_GetFlagStatus(KEY3_STATUS)){
							system.flash_memory[5] = (u16)system.pressure_time4;
							STMFLASH_Write(FLASH_BASE_ADDRESS,(u16 *)system.flash_memory,10);
							break;
						}
						back_color = RED;
						Mid_LCD_ShowNum(150,125,system.pressure_time4,12,12);
					}
				}			
				break;
				
			case 4:

				back_color = BLACK;	
				Mid_LCD_ShowNum(150,35,system.pressure_time1,12,12);		
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,65,system.pressure_time2,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,95,system.pressure_time3,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,125,system.pressure_time4,12,12);
			
				back_color = WHITE;			
				Mid_LCD_ShowNum(150,155,system.pressure_time5,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,185,system.pressure_time6,12,12);
			
				if(Key_GetFlagStatus(KEY3_STATUS)){

					while(1){
						if(Key_GetFlagStatus(KEY2_STATUS)){
							/*Set the pressure_time5*/
							system.pressure_time5 -= 1;
							if(system.pressure_time5 < 1){
								system.pressure_time5 = 0;
							}
						}
						
						if(Key_GetFlagStatus(KEY1_STATUS)){
							/*Set the pressure_time5*/
							system.pressure_time5 += 1;
							if(system.pressure_time5 > 1000){
								system.pressure_time5 = 1000;
							}		
						}	
						if(Key_GetFlagStatus(KEY3_STATUS)){
							system.flash_memory[6] = (u16)system.pressure_time5;
							STMFLASH_Write(FLASH_BASE_ADDRESS,(u16 *)system.flash_memory,10);
							break;
						}
						back_color = RED;
						Mid_LCD_ShowNum(150,155,system.pressure_time5,12,12);	
					}
				}
				break;
			
			case 5:

				back_color = BLACK;	
				Mid_LCD_ShowNum(150,35,system.pressure_time1,12,12);		
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,65,system.pressure_time2,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,95,system.pressure_time3,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,125,system.pressure_time4,12,12);
			
				back_color = BLACK;			
				Mid_LCD_ShowNum(150,155,system.pressure_time5,12,12);
			
				back_color = WHITE;			
				Mid_LCD_ShowNum(150,185,system.pressure_time6,12,12);
			
				if(Key_GetFlagStatus(KEY3_STATUS)){
					while(1){
						if(Key_GetFlagStatus(KEY2_STATUS)){
							/*Set the pressure_time6*/
							system.pressure_time6 -= 1;
							if(system.pressure_time6 < 1){
								system.pressure_time6 = 0;
							}
						}
						
						if(Key_GetFlagStatus(KEY1_STATUS)){
							/*Set the pressure_time6*/
							system.pressure_time6 += 1;
							if(system.pressure_time6 > 1000){
								system.pressure_time6 = 1000;
							}		
						}	
						if(Key_GetFlagStatus(KEY3_STATUS)){
							system.flash_memory[7] = (u16)system.pressure_time6;
							STMFLASH_Write(FLASH_BASE_ADDRESS,(u16 *)system.flash_memory,10);
							break;
						}
						back_color = RED;
						Mid_LCD_ShowNum(150,185,system.pressure_time6,12,12);
					}
				}			
				break;
				
			default:
				break;
			
		}		
	goto debug_state;
}

/**
  * @brief  		Judge mode function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void Mode_Judgement(void)
{
	static u8 key4_toggle = 0x00;
	static u8 key3_toggle = 0x00;
	
	if((system.keys_ack) && (system.mode == MODE_STANDBY)){	
		system.keys_ack = RESET;
		system.mode = MODE_DEBUG;
	}
	
	if(Key_GetFlagStatus(KEY4_STATUS)){
		key4_toggle ^= 0x01;

		if(0x00 == key4_toggle){
			system.mode = MODE_STANDBY;
		}
		else{
			system.mode = MODE_OXYGENERATE;
		}			
	}
	
	if(Key_GetFlagStatus(KEY3_STATUS)){
		key3_toggle += 0x01;
		if(key3_toggle > 2){
			key3_toggle = 0x00;
		}
		
		if(MODE_OXYGENERATE == system.mode){
			if(0x00 == key3_toggle){
				system.mode = MODE_OXYGENERATE;
			}
			if(0x01 == key3_toggle){
				system.mode = MODE_AI;
			}
			if(0x02 == key3_toggle){
				system.mode = MODE_ATOMIZATION;
			}
		}
		
		if(MODE_ATOMIZATION == system.mode){
			if(0x00 == key3_toggle){
				system.mode = MODE_OXYGENERATE;
			}
			if(0x01 == key3_toggle){
				system.mode = MODE_AI;
			}
			if(0x02 == key3_toggle){
				system.mode = MODE_ATOMIZATION;
			}
		}
		
		if(MODE_AI == system.mode){
			if(0x00 == key3_toggle){
				system.mode = MODE_OXYGENERATE;
			}
			if(0x01 == key3_toggle){
				system.mode = MODE_AI;
			}
			if(0x02 == key3_toggle){
				system.mode = MODE_ATOMIZATION;
			}
		}		
	}
	
	if(Key_GetFlagStatus(KEY2_STATUS)){
			system.grade -= 1;
			if(system.grade <= 1){
				system.grade = 1;
			}
	}
	
	if(Key_GetFlagStatus(KEY1_STATUS)){
			system.grade += 1;
		if(system.grade >= 3)
			system.grade = 3;
	}
	
	switch(system.mode)
	{
		case MODE_STANDBY:
			Mode_Standby_Function();
			break;

		case MODE_OXYGENERATE:
			Mode_Oxygen_Generate_Function();
			break;

		case MODE_ATOMIZATION:
			Mode_Atomization_Function();
			break;
		
		case MODE_DEBUG:
			Mode_Debug_Function();
			break;	
		
		case MODE_AI:
			Mode_AI_Function();
			break;	
		
		default:
			break;
	}

	/*FAN:55 65 75  BLDC:1050 1320 1680*/
	switch(system.grade)
	{
		case 1:
				system.FAN_Speed = 899*0.50;
				system.BLDC_Speed = 1050;	
			break;
		
		case 2:
				system.FAN_Speed = 899*0.55;
				system.BLDC_Speed = 1320;	
			break;
		
		case 3:
				system.FAN_Speed = 899*0.60;
				system.BLDC_Speed = 1680;	
			break;
		
		default:
			break;		
	}		
}




/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
