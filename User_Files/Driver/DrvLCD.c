/**
  ******************************************************************************
  * @file		DrvLcd.c
  * @author	Best Team
  * @version	V1.0.0
  * @date		24-June-2021
  * @brief	This file provides the function about display modules.
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
#include "DrvLcd.h"

/**
	* @brief  		Write register function. 
  *         
  * @param[in]	u8 num
  *         
  * @return 		none
  * 
  */
void Drv_LCD_WR_REG(u8 reg)
{   
	Drv_LCD_RS = RESET;
	Drv_SPI2_WriteByte(reg);	
}

/**
	* @brief  		Write data function. 
  *         
  * @param[in]	u8 num
  *         
  * @return 		none
  * 
  */
void Drv_LCD_WR_DATA(u8 data)
{	
	Drv_LCD_RS = SET;
	Drv_SPI2_WriteByte(data);
}



/**
	* @brief  		Write Data to the specified Register function. 
  *         
  * @param[in]	u8 LCD_Reg,u8 LCD_RegValue
  *         
  * @return 		none
  * 
  */
void Drv_LCD_WriteReg(u8 LCD_Reg,u8 LCD_RegValue)
{	
	Drv_LCD_WR_REG(LCD_Reg); 
	
	Delay_Ms(1);
	
	Drv_LCD_WR_DATA(LCD_RegValue); 
}	

/**
	* @brief  		LCD sleeps out. 
  *         
  * @param[in]	none
  *         
  * @return 		none
  * 
  */
void Drv_LCD_SleepOut(void)
{					   
	/*Sleep Out*/
	Drv_LCD_WR_REG(0x11);
	Delay_Ms(120); //Delay 120ms
}	 




/**
	* @brief  		Turn on the LCD. 
  *         
  * @param[in]	none
  *         
  * @return 		none
  * 
  */
void Drv_LCD_On(void)
{					   
	Drv_LCD_WR_REG(0X29);
	Drv_LCD_LED = SET;
}	 

/**
	* @brief  		Turn off the LCD. 
  *         
  * @param[in]	none
  *         
  * @return 		none
  * 
  */

void Drv_LCD_Off(void)
{	   
	Drv_LCD_WR_REG(0X28);
	Drv_LCD_LED = RESET;
}   


/**
	* @brief  		Set the brightness of the LCD. 
  *         
  * @param[in]	none
  *         
  * @return 		none
  * 
  */
void Drv_LCD_Brightness(u8 brightness)
{	
	Drv_LCD_WriteReg(0x51,brightness);
}


/**
	* @brief  		Set the scan direction of LCD
  *         
  * @param[in]	none
  *         
  * @return 		none
	*
	*	@note	
  */
void Drv_LCD_Display_Dir(void)
{
	u16 regval = 0X00;

	/*Bit D2- Display Data Latch Data Order*/
	regval = regval | (0<<2);
	
	/*Bit D3- RGB/BGR Order*/
	regval = regval | (1<<3);
	
	/*Bit D4- Line Address Order*/
	regval = regval | (0<<4);	
	
	/*Bit D5 MV- Page/Column Order*/
	regval = regval | (0<<5);	/*Decide the direction:vertical or horizontal.*/
	
	/*Bit D6 MX- Column Address Order*/
	regval = regval | (1<<6);	/*Decide the scaning direction of X-axis(the short side).*/
	
	/*Bit D7 MY- Page Address Order*/
	regval = regval | (0<<7);	/*Decide the scaning direction of Y-axis(the long side).*/
	
	/*MADCTL (36h): Memory Data Access Control*/
	Drv_LCD_WriteReg(0X36,regval);	
}	 

/**
  * @brief  		The orignal code from the factory. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
void Drv_LCD_Orignal(void)
{
	Drv_LCD_WR_REG(0xFE);
	Drv_LCD_WR_REG(0xEF);

	Drv_LCD_WR_REG(0xEB);
	Drv_LCD_WR_DATA(0x14);

	Drv_LCD_WR_REG(0x84);
	Drv_LCD_WR_DATA(0x40); //40->60 0xb5 en  20200924  james

	Drv_LCD_WR_REG(0x85);
	Drv_LCD_WR_DATA(0xFF);

	Drv_LCD_WR_REG(0x86);
	Drv_LCD_WR_DATA(0xFF);

	Drv_LCD_WR_REG(0x87);
	Drv_LCD_WR_DATA(0xFF);

	Drv_LCD_WR_REG(0x8E);
	Drv_LCD_WR_DATA(0xFF);

	Drv_LCD_WR_REG(0x8F);
	Drv_LCD_WR_DATA(0xFF);

	Drv_LCD_WR_REG(0x88);
	Drv_LCD_WR_DATA(0x0A);

	Drv_LCD_WR_REG(0x89);
	Drv_LCD_WR_DATA(0x23); //spi 2data reg en

	Drv_LCD_WR_REG(0x8A);
	Drv_LCD_WR_DATA(0x00);

	Drv_LCD_WR_REG(0x8B);
	Drv_LCD_WR_DATA(0x80);

	Drv_LCD_WR_REG(0x8C);
	Drv_LCD_WR_DATA(0x01);

	Drv_LCD_WR_REG(0x8D);
	Drv_LCD_WR_DATA(0x01);
	
	Drv_LCD_WR_REG(0xB6);
	Drv_LCD_WR_DATA(0x00);
	//Drv_LCD_WR_DATA(0x00); //GS  SS  0x20

	Drv_LCD_WR_REG(0x36);
	Drv_LCD_WR_DATA(0x48);

	Drv_LCD_WR_REG(0x3A);
	Drv_LCD_WR_DATA(0x05);


	Drv_LCD_WR_REG(0x90);
	Drv_LCD_WR_DATA(0x08);
	Drv_LCD_WR_DATA(0x08);
	Drv_LCD_WR_DATA(0x08);
	Drv_LCD_WR_DATA(0x08);

	Drv_LCD_WR_REG(0xBD);
	Drv_LCD_WR_DATA(0x06);

	Drv_LCD_WR_REG(0xBC);
	Drv_LCD_WR_DATA(0x00);

	Drv_LCD_WR_REG(0xFF);
	Drv_LCD_WR_DATA(0x60);
	Drv_LCD_WR_DATA(0x01);
	Drv_LCD_WR_DATA(0x04);

	Drv_LCD_WR_REG(0xC3);
	Drv_LCD_WR_DATA(0x16);
	Drv_LCD_WR_REG(0xC4);
	Drv_LCD_WR_DATA(0x16);

	Drv_LCD_WR_REG(0xC9);
	Drv_LCD_WR_DATA(0x25);//0x25

	Drv_LCD_WR_REG(0xBE);
	Drv_LCD_WR_DATA(0x11);

	Drv_LCD_WR_REG(0xE1);
	Drv_LCD_WR_DATA(0x10);
	Drv_LCD_WR_DATA(0x0E);

	Drv_LCD_WR_REG(0xDF);
	Drv_LCD_WR_DATA(0x21);
	Drv_LCD_WR_DATA(0x0c);
	Drv_LCD_WR_DATA(0x02);

	Drv_LCD_WR_REG(0xF0);
	Drv_LCD_WR_DATA(0x45);
	Drv_LCD_WR_DATA(0x09);
	Drv_LCD_WR_DATA(0x08);
	Drv_LCD_WR_DATA(0x08);
	Drv_LCD_WR_DATA(0x26);
	Drv_LCD_WR_DATA(0x2A);

	Drv_LCD_WR_REG(0xF1);
	Drv_LCD_WR_DATA(0x43);
	Drv_LCD_WR_DATA(0x70);//0X70
	Drv_LCD_WR_DATA(0x72);
	Drv_LCD_WR_DATA(0x36);
	Drv_LCD_WR_DATA(0x37);
	Drv_LCD_WR_DATA(0x6F);
	
	Drv_LCD_WR_REG(0xF2);
	Drv_LCD_WR_DATA(0x45);
	Drv_LCD_WR_DATA(0x09);
	Drv_LCD_WR_DATA(0x08);
	Drv_LCD_WR_DATA(0x08);
	Drv_LCD_WR_DATA(0x26);
	Drv_LCD_WR_DATA(0x2A);

	Drv_LCD_WR_REG(0xF3);
	Drv_LCD_WR_DATA(0x43);
	Drv_LCD_WR_DATA(0x70);
	Drv_LCD_WR_DATA(0x72);
	Drv_LCD_WR_DATA(0x36);
	Drv_LCD_WR_DATA(0x37);
	Drv_LCD_WR_DATA(0x6F);

	Drv_LCD_WR_REG(0xED);
	Drv_LCD_WR_DATA(0x1B);
	Drv_LCD_WR_DATA(0x0B);

	Drv_LCD_WR_REG(0xAE);
	Drv_LCD_WR_DATA(0x77);

	Drv_LCD_WR_REG(0xCD);
	Drv_LCD_WR_DATA(0x63);


	Drv_LCD_WR_REG(0x70);
	Drv_LCD_WR_DATA(0x07);
	Drv_LCD_WR_DATA(0x07);
	Drv_LCD_WR_DATA(0x04);
	Drv_LCD_WR_DATA(0x0E);//0x0e
	Drv_LCD_WR_DATA(0x10);//0x10
	Drv_LCD_WR_DATA(0x09);
	Drv_LCD_WR_DATA(0x07);
	Drv_LCD_WR_DATA(0x08);
	Drv_LCD_WR_DATA(0x03);

	Drv_LCD_WR_REG(0xE8);
	Drv_LCD_WR_DATA(0x04);//34
/////////////////////////////////////////////
	Drv_LCD_WR_REG(0x60);
	Drv_LCD_WR_DATA(0x38);
	Drv_LCD_WR_DATA(0x0B);
	Drv_LCD_WR_DATA(0x6D);
	Drv_LCD_WR_DATA(0x6D);

	Drv_LCD_WR_DATA(0x39);
	Drv_LCD_WR_DATA(0xF0);
	Drv_LCD_WR_DATA(0x6D);
	Drv_LCD_WR_DATA(0x6D);


	Drv_LCD_WR_REG(0x61);
	Drv_LCD_WR_DATA(0x38);
	Drv_LCD_WR_DATA(0xF4);
	Drv_LCD_WR_DATA(0x6D);
	Drv_LCD_WR_DATA(0x6D);

	Drv_LCD_WR_DATA(0x38);
//Drv_LCD_WR_DATA(0xF7); //20200718
	Drv_LCD_WR_DATA(0xF7);
	Drv_LCD_WR_DATA(0x6D);
	Drv_LCD_WR_DATA(0x6D);
/////////////////////////////////////
	Drv_LCD_WR_REG(0x62);
	Drv_LCD_WR_DATA(0x38);
	Drv_LCD_WR_DATA(0x0D);
	Drv_LCD_WR_DATA(0x71);
	Drv_LCD_WR_DATA(0xED);
	Drv_LCD_WR_DATA(0x70);
	Drv_LCD_WR_DATA(0x70);
	Drv_LCD_WR_DATA(0x38);
	Drv_LCD_WR_DATA(0x0F);
	Drv_LCD_WR_DATA(0x71);
	Drv_LCD_WR_DATA(0xEF);
	Drv_LCD_WR_DATA(0x70);
	Drv_LCD_WR_DATA(0x70);

	Drv_LCD_WR_REG(0x63);
	Drv_LCD_WR_DATA(0x38);
	Drv_LCD_WR_DATA(0x11);
	Drv_LCD_WR_DATA(0x71);
	Drv_LCD_WR_DATA(0xF1);
	Drv_LCD_WR_DATA(0x70);
	Drv_LCD_WR_DATA(0x70);
	Drv_LCD_WR_DATA(0x38);
	Drv_LCD_WR_DATA(0x13);
	Drv_LCD_WR_DATA(0x71);
	Drv_LCD_WR_DATA(0xF3);
	Drv_LCD_WR_DATA(0x70);
	Drv_LCD_WR_DATA(0x70);
///////////////////////////////////////////////////////
	Drv_LCD_WR_REG(0x64);
	Drv_LCD_WR_DATA(0x28);
	Drv_LCD_WR_DATA(0x29);
	Drv_LCD_WR_DATA(0xF1);
	Drv_LCD_WR_DATA(0x01);
	Drv_LCD_WR_DATA(0xF1);
	Drv_LCD_WR_DATA(0x00);
	Drv_LCD_WR_DATA(0x07);

	Drv_LCD_WR_REG(0x66);
	Drv_LCD_WR_DATA(0x3C);
	Drv_LCD_WR_DATA(0x00);
	Drv_LCD_WR_DATA(0xCD);
	Drv_LCD_WR_DATA(0x67);
	Drv_LCD_WR_DATA(0x45);
	Drv_LCD_WR_DATA(0x45);
	Drv_LCD_WR_DATA(0x10);
	Drv_LCD_WR_DATA(0x00);
	Drv_LCD_WR_DATA(0x00);
	Drv_LCD_WR_DATA(0x00);

	Drv_LCD_WR_REG(0x67);
	Drv_LCD_WR_DATA(0x00);
	Drv_LCD_WR_DATA(0x3C);
	Drv_LCD_WR_DATA(0x00);
	Drv_LCD_WR_DATA(0x00);
	Drv_LCD_WR_DATA(0x00);
	Drv_LCD_WR_DATA(0x01);
	Drv_LCD_WR_DATA(0x54);
	Drv_LCD_WR_DATA(0x10);
	Drv_LCD_WR_DATA(0x32);
	Drv_LCD_WR_DATA(0x98);

	Drv_LCD_WR_REG(0x74);
	Drv_LCD_WR_DATA(0x10);
	Drv_LCD_WR_DATA(0xc0);//68 = 90HZ, C0 =50HZ, 4D=80HZ, 7E=100HZ  80=60HZ,5B=85HZ,53 =82HZ,59=84HZ
	Drv_LCD_WR_DATA(0x80);
	Drv_LCD_WR_DATA(0x00);
	Drv_LCD_WR_DATA(0x00);
	Drv_LCD_WR_DATA(0x4E);
	Drv_LCD_WR_DATA(0x00);

	Drv_LCD_WR_REG(0x98);
	Drv_LCD_WR_DATA(0x3e);
	Drv_LCD_WR_DATA(0x07);

	Drv_LCD_WR_REG(0x35);
	Drv_LCD_WR_DATA(0x00);
	Drv_LCD_WR_REG(0x21);

	Delay_Us(120);
	
	Drv_LCD_WR_REG(0x11);
	Delay_Us(120);
	Drv_LCD_WR_REG(0x29);
	Drv_LCD_WR_REG(0x2c);
}

/**
  * @brief  		Handling the initial function of the GPIOS of the LCD. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
void Drv_LCD_IO_Init(void)
{	
	/*Define the Structure of LCD*/ 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*Enable the clock of PortA&C*/
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,ENABLE); 
	
	/*Reset of LCD*/ 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	/*LED of LCD*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	/*RS of LCD*/	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC,&GPIO_InitStructure);	
	
}


/**
	* @brief  		Reset the LCD.
  *         
  * @param[in]	none
  *         
  * @return 		none
	*
	*	@note	
  */
void Drv_LCD_Reset(void)
{
	/*Reset sequence.*/
	Delay_Ms(1); //Delay 1ms
	Drv_LCD_RST = SET;
	Delay_Ms(1); //Delay 1ms
	Drv_LCD_RST = RESET;
	Delay_Ms(10); //Delay 10ms
	Drv_LCD_RST = SET;
	Delay_Ms(120); //Delay 120ms	
}


/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
