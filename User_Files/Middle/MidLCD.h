/**
  ******************************************************************************
  * @file    MidLCD.h
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

#ifndef __MIDLCD_H__
#define __MIDLCD_H__		

#include "AplMain.h"


typedef struct  
{										    
	u16 width;									
	u16 height;																	
	u16 wramcmd;								
											
	u8  setxcmd;								
	u8  setycmd;								
					
}_lcddev; 	  


extern _lcddev lcddev;   
extern u16 point_color;  
extern u16 back_color; 

 

//Define the colors								//R(5)	G(6)	 B(5)
#define WHITE         	 	0xFFFF	//11111 111111 11111
#define BLACK         	 	0x0000	//00000 000000 00000  
#define BLUE							0x001F	//00000 000000 11111    
#define BRED							0XF81F
#define GRED 			 				0XFFE0
#define GBLUE							0X07FF	//
#define RED								0xF800	//11111 000000 00000
#define MAGENTA						0xF81F
#define GREEN							0x07E0
#define CYAN 							0x7FFF
#define YELLOW						0xFFE0
#define BROWN							0XBC40 	
#define BRRED							0XFC07 	
#define GRAY							0X8430 	
#define DARKBLUE      	 	0X01CF
#define LIGHTBLUE      	 	0X7D7C	 
#define GRAYBLUE       	 	0X5458	
#define LIGHTGREEN     	 	0X841F	
#define LIGHTGRAY        	0XEF5B	
#define LGRAY 			 			0XC618	
#define LGRAYBLUE      		0XA651	
#define LBBLUE           	0X2B12	
#define Color1						0X420A	//01000 010000 01010	
																	//11110	110101 10011 0XF6B3
																	
#define Color2						0XF532	//11110	101001 10010

void DrawLine(u16 Xstart,u16 Xend,u16 Ystart,u16 Yend,u16 color);
void DispStr(u8 *str,u16 Xstart,u16 Ystart,u16 TextColor,u16 BackColor,u16 FontWidth,u16 FontHeight); 
void LCD_ShowIcon(u16 x,u16 y,u16 icon,u16 front_color,u16 back_color,u8 mode);
void Mid_LCD_WriteOnePix(u16 x,u16 y,u16 color);
void BlockWrite(u16 Xstart,u16 Xend,u16 Ystart,u16 Yend);
void Mid_LCD_WriteOneDot(u16 color);


void Mid_LCD_Init(void);													   																			
void Mid_LCD_DisplayOn(void);																															
void Mid_LCD_DisplayOff(void);		

void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);
void Mid_LCD_SetCursor(u16 Xpos, u16 Ypos);

void Mid_LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void Mid_LCD_ShowChar(u16 x,u16 y,u16 num,u16 size,u8 mode);															
void Mid_LCD_ShowRespiratoryRate(u16 x,u16 y,u8 num,u8 size);	
void Mid_LCD_ShowFlow(u16 x,u16 y,u8 num,u8 size);	
void Mid_LCD_ShowIcon(u16 x,u16 y,u16 Icon,u8 mode);
void Mid_LCD_Clear(u16 color);

void Mid_LCD_ShowRunningTime(u16 x,u16 y,u32 num,u8 size);															
void Mid_LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);									

void Mid_LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  																
void Mid_LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);												

void Mid_UI_Standby(void);
void Mid_UI_OxygenProduction(void);
void Mid_UI_Atomization(void);
void Mid_UI_AI(void);
void Mid_UI_Debug(void);
void Mid_UI_Display(void);

//LCD RESOLUTION
#define SSD_HOR_RESOLUTION		240		
#define SSD_VER_RESOLUTION		240		

//LCD PARAMETERS
//#define SSD_HOR_PULSE_WIDTH		1			
//#define SSD_HOR_BACK_PORCH		210	
//#define SSD_HOR_FRONT_PORCH		45		

//#define SSD_VER_PULSE_WIDTH		1			
//#define SSD_VER_BACK_PORCH		34		
//#define SSD_VER_FRONT_PORCH		10		

//#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_PULSE_WIDTH+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
//#define SSD_HPS	(SSD_HOR_PULSE_WIDTH+SSD_HOR_BACK_PORCH)
//#define SSD_VT 	(SSD_VER_PULSE_WIDTH+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH+SSD_VER_RESOLUTION)
//#define SSD_VSP (SSD_VER_PULSE_WIDTH+SSD_VER_BACK_PORCH)

#define CASE_XNUO							1
#define CASE_PERCENTAGE				2
#define CASE_AI								3
#define CASE_BLUETOOTH				4
#define CASE_DOT							5
#define CASE_CONCENTRATION		6
#define CASE_FLOW							7
#define CASE_HOUR							8
#define CASE_MINUTE						9
#define CASE_O2								10
#define CASE_TOTAL						11
#define CASE_SHORT_LINE				12
#define CASE_LONG_LINE				13
#define CASE_BELL							14
#define CASE_ATOMIZATION			15
#define CASE_OMRON						16
#define CASE_ELLIPSE					17
#define CASE_TEST							18

#endif  

/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
