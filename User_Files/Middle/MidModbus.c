/**
  ******************************************************************************
  * @file    MidModbus.c
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about modbus.. 
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
#include "MidModbus.h"

	/**
  * @brief  		CRC16_Modbus function. 
  *         
  * @param[in]	u8 *buf, u16 len
  *         
  * @return 		u16 crc
  *  
  */
u16 CRC16_Modbus(u8 *buf, u16 len)
{
		u16 crc = 0xFFFF;
		int pos = 0;
		int i = 8;
	
		for (pos = 0; pos < len; pos++)
		{
				/*XOR byte into least sig. byte of crc*/
				crc ^= (u16)buf[pos];  
				/*Loop over each bit*/
				for (i = 8; i != 0; i--)   
				{
						/*If the LSB is set*/
						if ((crc & 0x0001) != 0)    
						{
								/*Shift right and XOR 0xA001*/
								crc >>= 1;  
								crc ^= 0xA001;
						}
						/*Else LSB is not set*/
						else 
						{
								/*Just shift right*/
								crc >>= 1; 
						}
				}
		}
 
		/*Exchange the HSB and LSB.*/
		crc = ((crc & 0x00ff) << 8) | ((crc & 0xff00) >> 8);
		return crc;
}

		
	/**
  * @brief  		CMD_Modbus function. 
  *         
  * @param[in]	u8 slave_addr, u8 command, u16 register_addr, u16 data
  *         
  * @return 		none.
  *  
	* @note 			Only write single register command.
  */

void CMD_Modbus(u8 slave_addr, u8 command, u16 register_addr, u16 data)
{
	static u8 data_buf[8] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};	
	u16 crc_result = 0x00;
	u8 counter = 0;
	
	crc_result = CRC16_Modbus(data_buf, 6);
	
	/*slave address.*/
	data_buf[0] = slave_addr;
	
	/*slave command.*/
	data_buf[1] = command;		
	
	/*register address.*/
	data_buf[2] = (u8)(register_addr>>8);		
	data_buf[3] = (u8)(register_addr & 0x00FF);		
	
	/*data.*/
	data_buf[4] = (u8)(data>>8);		
	data_buf[5] = (u8)(data & 0x00FF);		

	/*CRC.*/
	data_buf[6] = (u8)(crc_result>>8);		
	data_buf[7] = (u8)(crc_result & 0x00FF);		

	for(counter = 0;counter < 8;counter ++){
	
		USART_SendData(UART4,data_buf[counter]);
		
		while(RESET == USART_GetFlagStatus(UART4,USART_FLAG_TC))
		{
			;
		}

	}			
		
}





/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
