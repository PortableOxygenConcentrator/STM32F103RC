/**
  ******************************************************************************
  * @file    DrvLCD.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about lcd. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */

#ifndef __DRVLCD_H__
#define __DRVLCD_H__

#include "AplMain.h"

#define	Drv_LCD_RST PCout(8) 	
#define	Drv_LCD_LED PBout(12) 	
#define	Drv_LCD_RS 	PCout(7)	 
									
void Drv_LCD_WR_REG(u8 regval);
void Drv_LCD_WR_DATA(u8 num);
void Drv_LCD_WriteReg(u8 LCD_Reg, u8 LCD_RegValue);
void Drv_LCD_SleepOut(void);
void Drv_LCD_On(void);
void Drv_LCD_Off(void);
void Drv_LCD_Brightness(u8 brightness);
void Drv_LCD_Display_Dir(void);
void Drv_LCD_IO_Init(void);
void Drv_LCD_Reset(void);
void Drv_LCD_Orignal(void);


#endif  

/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
