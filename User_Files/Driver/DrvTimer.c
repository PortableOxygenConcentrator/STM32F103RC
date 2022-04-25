/**
  ******************************************************************************
  * @file    DrvTimer.c
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about timers.. 
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
#include "DrvTimer.h" 

FlagStatus key_timer2_100ms_flag = RESET;						/*Used in the vavle-controling and keys-judgement.*/
FlagStatus breath_vavle_timer2_10ms_flag = RESET;		/*Used in the breath-vavle controling.*/
FlagStatus breath_sensor_timer2_10ms_flag = RESET;	/*Used in the breath-sensor time calculating.*/
FlagStatus no_breath_timer2_10ms_flag = RESET;			/*Used in the no-breath time calculating.*/
FlagStatus O2_vavle_timer2_10ms_flag = RESET;				/*Used in the O2-vavle controling.*/
FlagStatus ui_timer2_1s_flag = RESET;								/*Used in the UI-refreshing.*/
FlagStatus modbus_timer2_100ms_flag = RESET;				/*Used in the modbus-refreshing.*/


u16 timer2_100ms_count = 0;
u16 timer2_1s_count = 0;

u16 timer4_1s_count = 0;
u16 pressure_value = 0;



/**
  * @brief  		TIM5_Init function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	*	@note				10ms  
  */
void TIM5_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); 

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 

	TIM_Cmd(TIM5, ENABLE);				 
}

/**
  * @brief  		TIM5_IRQHandler function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void TIM5_IRQHandler(void)  
{
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  
	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  

		O2_Vavle_Control();

	}
}



/**
  * @brief  		TIM8_Init function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	*	@note				10ms   
  */
void TIM8_Init(u32 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);	
			
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); 
  
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	
	TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE);
	
  TIM_Cmd(TIM8,ENABLE );
}

/**
  * @brief  		TIM8_UP_IRQHandler function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void TIM8_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(TIM8, TIM_IT_Update);
		
			if(MODE_AI == system.mode) 
			{
				Breath_Vavle_Control();
			}
			
	}
}


/**
  * @brief  		TIM2_Init function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	*	@note				10ms  
  */
void TIM2_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = arr; 	
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); 

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  

	TIM_Cmd(TIM2, ENABLE); 			 
}

/**
  * @brief  		TIM2_IRQHandler function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	*	@note				Interval:10ms
  */
void TIM2_IRQHandler(void)  
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);   
		
		timer2_100ms_count ++;
		if(timer2_100ms_count >= 10){
			timer2_100ms_count = 0;
			
			key_timer2_100ms_flag = SET;
			modbus_timer2_100ms_flag = SET;	
		}	
		
		timer2_1s_count ++;
		if(timer2_1s_count >= 100){
			timer2_1s_count = 0;
			
			ui_timer2_1s_flag = SET;				
		}	
		
		breath_vavle_timer2_10ms_flag = SET;
		breath_sensor_timer2_10ms_flag = SET;
		no_breath_timer2_10ms_flag = SET;
		O2_vavle_timer2_10ms_flag = SET;	
	}
}



/**
  * @brief  		TIM3_IRQHandler function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	*	@note				None
  */
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
	TIM_Cmd(TIM3, ENABLE);
}


/**
  * @brief  		TIM4_Cap_Init function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void TIM4_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef 					GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  				TIM4_ICInitStructure;
  NVIC_InitTypeDef 					NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);					
	
 
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
  
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4; 
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	
	TIM_ITConfig(TIM4,TIM_IT_Update | TIM_IT_CC4,ENABLE);
	
  TIM_Cmd(TIM4,ENABLE ); 

}
 
/**
  * @brief  		TIM4_IRQHandler function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void TIM4_IRQHandler(void)
{
	static FlagStatus capture_flag = RESET;
	static u32 tim4ch4_capture_val1 = 0;
	static u32 tim4ch4_capture_val2 = 0;
	static u32 tim4ch4_capture_val = 0;  
	
	if(TIM_GetFlagStatus(TIM4,TIM_IT_CC4)){
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC4); 
		
		if(!capture_flag){
			capture_flag = SET;
			tim4ch4_capture_val1 = (u32)TIM_GetCapture4(TIM4);
		}
		else{
			capture_flag = RESET;			
			tim4ch4_capture_val2 = (u32)TIM_GetCapture4(TIM4);
		
			if(tim4ch4_capture_val2 > tim4ch4_capture_val1){
				tim4ch4_capture_val = tim4ch4_capture_val2 - tim4ch4_capture_val1 ;
			}
			else if(tim4ch4_capture_val2 < tim4ch4_capture_val1){
				tim4ch4_capture_val = (0xFFFF - tim4ch4_capture_val1) + tim4ch4_capture_val2 ;
			}
			else{
				tim4ch4_capture_val = 0;
			}			
			
			if(tim4ch4_capture_val > 0){
				system.BLDC_Speed = (u32)(SystemCoreClock/tim4ch4_capture_val/10);
			}
		
		}	
	}
}	

/**
  * @brief  		TIM7_Init function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	*	@note				10ms   
  */
void TIM7_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); 

	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); 

	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); 

	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  

	TIM_Cmd(TIM7, ENABLE); 				 
}

/**
  * @brief  		TIM7_IRQHandler function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void TIM7_IRQHandler(void)  
{
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update); 

		ADC1_Handle(ADC_Channel_8);
		
		ADC2_Handle(ADC_Channel_9);
	}
}



/**
  * @brief  		TIM6_Init function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
	*	@note				1s   
  */
void TIM6_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); 

	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE );

	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  

	TIM_Cmd(TIM6, ENABLE); 					 
}

/**
  * @brief  		TIM6_IRQHandler function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void TIM6_IRQHandler(void) 
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update); 
		
		if(system.mode != MODE_STANDBY){
			TimeHandle();
		}
//			Mid_UI_Display();	
	}
}




/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
