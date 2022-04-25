/**
  ******************************************************************************
  * @file    MidModbus.h
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about modbus. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS ONLY FOR INTERNAL USE.SPREAD AND COPY SHOULD
  * NOT BE ALLOWED.
  *
  * COPYRIGHT 2021 BSET TEAM
  ******************************************************************************
  */
	
#ifndef __MIDMODBUS_H__
#define __MIDMODBUS_H__

#include "AplMain.h"

u16 CRC16_Modbus(u8 *buf, u16 len);
void CMD_Modbus(u8 slave_addr, u8 command, u16 register_addr, u16 data);

#endif

/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
