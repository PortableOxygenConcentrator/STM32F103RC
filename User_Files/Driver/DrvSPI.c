/**
  ******************************************************************************
  * @file    DrvSPI.c
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about SPI.. 
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
#include "DrvSPI.h"

/**
  * @brief  		Handling the SPI2_Init function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
void Drv_SPI2_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE ); 
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE ); 	
 
	/*Configure pin CS*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/*Configure pin Clock¡¢MOSI*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	 /*Set PB13/PB15 on*/
 	GPIO_SetBits(GPIOB,GPIO_Pin_13 |GPIO_Pin_15); 

	/*Configure pin MISO which is not used.*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	

	 /*Configure SPI2*/	
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;  
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	
	SPI_InitStructure.SPI_CRCPolynomial = 7;	
	SPI_Init(SPI2, &SPI_InitStructure);  

	SPI_Cmd(SPI2, ENABLE); 
	
	SPI2_CS = RESET;
}   

/**
  * @brief  		Handling the SPI2 Speed Set function. 
  *         
  * @param[in]	u8 SPI_BaudRatePrescaler_2
  * 						u8 SPI_BaudRatePrescaler_8
  * 						u8 SPI_BaudRatePrescaler_16
  * 						u8 SPI_BaudRatePrescaler_256
  *         
  * @return 		None
  */ 
void Drv_SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI2->CR1&=0XFFC7;
	SPI2->CR1|=SPI_BaudRatePrescaler;	
	SPI_Cmd(SPI2,ENABLE); 
}

/**
  * @brief  		Handling the Byte sending function of SPI2. 
  *         
  * @param[in]	u8 TxData
  *         
  * @return 		None
  */ 
void Drv_SPI2_WriteByte(u8 TxData)
{				 	
	while( SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) ) 
	{
		;
	}			 
	
	SPI_I2S_SendData(SPI2, TxData); 
}


/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
