/**
  ******************************************************************************
  * @file    DrvSMBus.h
  * @author  Best Team
  * @version V1.0.0
  * @date    1-April-2020
  * @brief   This file provides the function about smbus. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */
	
#ifndef __DRVSMBUS_H__
#define __DRVSMBUS_H__

#include "AplMain.h"

/*Format 7 bits:Slave address is 0x09.For 8 bits,send 0x12 to write and 0x13 to read.*/
#ifndef SLAVE_ADDRESS
#define SLAVE_ADDRESS				0x12
#endif


/*SM BUS IO ASSIGNMENTS*/
#define SDA_IN()  					{GPIOB->CRL&=0X0FFFFFFF; GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() 					{GPIOB->CRL&=0X0FFFFFFF; GPIOB->CRL|=(u32)3<<28;}
#define SM_Bus_SCL    			PBout(6)
#define SM_Bus_SDA    			PBout(7) 
#define READ_SDA   					PBin(7)


extern u8 SM_Bus_Buffer_Tx[20];
extern u8 SM_Bus_Buffer_Rx[20];

void SM_Bus_Start(void);
void SM_Bus_Stop(void);
void SM_Bus_Send_Byte(u8 txd);	
u8 	 SM_Bus_Read_Byte(unsigned char ack);
u8 	 SM_Bus_Wait_Ack(void); 
void SM_Bus_Ack(void);	
void SM_Bus_NAck(void);
void SMbus_Init(void);
void SM_Bus_Master_BufferRead(uint8_t* pBuffer, uint32_t NumByteToRead, uint8_t SlaveAddress, uint8_t SlaveCommand);
void SM_Bus_Master_BufferWrite(uint8_t* pBuffer, uint32_t NumByteToWrite, uint8_t SlaveAddress, uint8_t SlaveCommand);


#endif

/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
