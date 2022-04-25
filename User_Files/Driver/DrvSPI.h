/**
  ******************************************************************************
  * @file    DrvSPI.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about SPI. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */

#ifndef __DRVSPI_H__
#define __DRVSPI_H__

/* Includes ------------------------------------------------------------------*/ 
#include "AplMain.h"
 
			  	    													  
void Drv_SPI2_Init(void);			 			
void Drv_SPI2_SetSpeed(u8 SpeedSet); 	  
void Drv_SPI2_WriteByte(u8 TxData);	

#define	SPI2_CS 	PCout(6)


#endif


/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/


