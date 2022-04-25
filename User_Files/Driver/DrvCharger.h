/**
  ******************************************************************************
  * @file    charger.h
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
	
#ifndef _CHARGER_H_
#define _CHARGER_H_

#include "AplMain.h"

/*SLAVE COMMAND*/
#define	CHARGER_OPTION0			0x12
#define	CHARGER_CURRENT			0x14
#define	CHARGER_VOLTAGE			0x15
#define	CHARGER_STATUS			0x20
#define	ADC_OPTION					0x35
#define	INPUT_VOLTAGE				0x3D
#define	MIN_SYSTEM_VOLTAGE	0x3E
#define	IIN_HOST						0x3F
#define	ADCIBAT							0x24
#define	ADCVSYSVBAT					0x26

/*BITS OF CHARGER_OPTION0(0x12) (READ ONLY)*/
#define RX_BUF_CHARGER_OPTION0	(SM_Bus_Buffer_Rx[0] | (SM_Bus_Buffer_Rx[1] << 8))
#define EN_LWPWR 								((0x8000 & RX_BUF_CHARGER_OPTION0) == 0x8000)
#define DIS_WTD 								((0x6000 & RX_BUF_CHARGER_OPTION0) == 0x0600)
#define SYS_SHORT_DISABLE				((0x0040 & RX_BUF_CHARGER_OPTION0) == 0x0040)
#define EN_LEARN				 				((0x0020 & RX_BUF_CHARGER_OPTION0) == 0x0020)
#define ADPT_GAIN				 				((0x0010 & RX_BUF_CHARGER_OPTION0) == 0x0010)
#define IBAT_GAIN				 				((0x0008 & RX_BUF_CHARGER_OPTION0) == 0x0008)
#define EN_LDO 									((0x0004 & RX_BUF_CHARGER_OPTION0) == 0x0004)
#define EN_IDPM				 					((0x0002 & RX_BUF_CHARGER_OPTION0) == 0x0002)
#define CHRG_INHIBIT 						((0x0001 & RX_BUF_CHARGER_OPTION0) == 0x0001)

/*BITS OF CHARGER_STATUS(0x20) (READ ONLY)*/
#define RX_BUF_CHARGER_STATUS	(SM_Bus_Buffer_Rx[6] | (SM_Bus_Buffer_Rx[7] << 8))
#define AC_STAT 							((0x8000 & RX_BUF_CHARGER_STATUS) == 0x8000)
#define ICO_DONE 							((0x4000 & RX_BUF_CHARGER_STATUS) == 0x4000)
#define IN_VAP	 							((0x2000 & RX_BUF_CHARGER_STATUS) == 0x2000)
#define IN_VINDPM 						((0x1000 & RX_BUF_CHARGER_STATUS) == 0x1000)
#define IN_IINDPM 						((0x0800 & RX_BUF_CHARGER_STATUS) == 0x0800)
#define IN_FCHRG 							((0x0400 & RX_BUF_CHARGER_STATUS) == 0x0400)
#define IN_PCHRG 							((0x0200 & RX_BUF_CHARGER_STATUS) == 0x0200)
#define IN_OTG 								((0x0100 & RX_BUF_CHARGER_STATUS) == 0x0100)
#define FAULT_ACOV 						((0x0080 & RX_BUF_CHARGER_STATUS) == 0x0080)
#define FAULT_BATOC 					((0x0040 & RX_BUF_CHARGER_STATUS) == 0x0040)
#define FAULT_ACOC	 					((0x0020 & RX_BUF_CHARGER_STATUS) == 0x0020)
#define FAULT_STAT 						((0x0010 & RX_BUF_CHARGER_STATUS) == 0x0010)
#define FAULT_SYS_SHORT 			((0x0008 & RX_BUF_CHARGER_STATUS) == 0x0008)
#define FAULT_LATCHOFF 				((0x0004 & RX_BUF_CHARGER_STATUS) == 0x0004)
#define FAULT_OTG_OVP 				((0x0002 & RX_BUF_CHARGER_STATUS) == 0x0002)
#define FAULT_OTG_UVP 				((0x0001 & RX_BUF_CHARGER_STATUS) == 0x0001)

/*BITS OF CHARGER_STATUS(0x20) (WRITE ONLY)*/
#define TX_BUF_CHARGER_STATUS			(SM_Bus_Buffer_Tx[6] | (SM_Bus_Buffer_Tx[7] << 8))	
#define CLEAR_FAULT_STAT 					((~0x0010) & TX_BUF_CHARGER_STATUS)
#define CLEAR_FAULT_SYS_SHORT 		((~0x0008) & TX_BUF_CHARGER_STATUS)

typedef struct
{
	u16 charge_current_setted;
	u16 charge_voltage;
	u16 charge_current;
	u16 discharge_current;
	u16 battery_voltage;
	u16 system_voltage;

	u16 charge_current_setpoint;
	u16 charge_voltage_setpoint;	

	FlagStatus ac_status;
	
}Charger_ParaTypeDef;

extern Charger_ParaTypeDef charger;


void WriteChargerParameters(void);
void ReadChargerParameters(void);

#endif

/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
