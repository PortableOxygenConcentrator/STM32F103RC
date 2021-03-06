/**
  ******************************************************************************
  * @file    DrvFlash.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about flash. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */

#ifndef __DRVFLASH_H__
#define __DRVFLASH_H__
#include "AplMain.h"  

//////////////////////////////////////////////////////////////////////////////////////////////////////
//用户根据自己的需要设置
#define STM32_FLASH_SIZE 512 	 		//所选STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_WREN 1        //使能FLASH写入(0，不使能;1，使能)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址
//FLASH解锁键值
 

u16 STMFLASH_ReadHalfWord(u32 faddr);		  //读出半字  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//指定地址开始写入指定长度的数据
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);											//指定地址开始读取指定长度数据
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);			//从指定地址开始写入指定长度的数据
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   			//从指定地址开始读出指定长度的数据
void ReadParameters(void);		


#endif



/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/

