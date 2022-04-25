/**
  ******************************************************************************
  * @file    DrvCharger.c
  * @author  Best Team
  * @version V1.0.0
  * @date    1-April-2020
  * @brief   This file provides the function about charger. 
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
#include"DrvCharger.h"

Charger_ParaTypeDef charger;

/**
  * @brief  		WriteChargerParameters function. 
  *         
  * @param[in]  none.
  *         
  * @return 		none.
  *  
  */
void WriteChargerParameters(void)
{
	charger.ac_status = AC_STAT ? SET : RESET;
	if(charger.ac_status){
		/*CHARGER_OPTION0*/
		SM_Bus_Buffer_Tx[1] = 0x07;
		SM_Bus_Buffer_Tx[0] = 0x0E;
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[0],2,SLAVE_ADDRESS, CHARGER_OPTION0);


//		if(SM_Bus_Buffer_Rx[16] * 64 >= 16800){
//			/*CHARGER_CURRENT*/
//			SM_Bus_Buffer_Tx[3] = 0x00;	
//			SM_Bus_Buffer_Tx[2] = 0x00;
//		}
//		else if(SM_Bus_Buffer_Rx[16] * 64 <= 15000){
//			/*CHARGER_CURRENT*/
//			SM_Bus_Buffer_Tx[3] = 0x08;	
//			SM_Bus_Buffer_Tx[2] = 0xC0;
//		}		
		/*CHARGER_CURRENT*/
		charger.charge_current_setpoint = 2240;/*unit:mA*/
		
		SM_Bus_Buffer_Tx[3] = (u8)( charger.charge_current_setpoint >> 8 );	
		SM_Bus_Buffer_Tx[2] = (u8)( charger.charge_current_setpoint);		
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[2],2,SLAVE_ADDRESS, CHARGER_CURRENT);

		/*CHARGER_VOLTAGE*/
		charger.charge_voltage_setpoint = 16840;/*unit:mV*/
		
		SM_Bus_Buffer_Tx[5] = (u8)( charger.charge_voltage_setpoint >> 8 );	
		SM_Bus_Buffer_Tx[4] = (u8)( charger.charge_voltage_setpoint );	
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[4],2,SLAVE_ADDRESS, CHARGER_VOLTAGE);

		/*CHARGER_STATUS*/	
//		SM_Bus_Buffer_Tx[7] = 0x80;
		SM_Bus_Buffer_Tx[6] = 0x00;
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[6],2,SLAVE_ADDRESS, CHARGER_STATUS);

		/*INPUT_VOLTAGE*/
		SM_Bus_Buffer_Tx[9] = 0x35;
		SM_Bus_Buffer_Tx[8] = 0x40;	
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[8],2,SLAVE_ADDRESS, INPUT_VOLTAGE);
		
		/*MIN_SYSTEM_VOLTAGE*/
		SM_Bus_Buffer_Tx[11] = 0x30;
		SM_Bus_Buffer_Tx[10] = 0x00;	
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[10],2,SLAVE_ADDRESS, MIN_SYSTEM_VOLTAGE);
		
		/*IIN_HOST*/
		SM_Bus_Buffer_Tx[13] = 0x41;
		SM_Bus_Buffer_Tx[12] = 0x00;	
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[12],2,SLAVE_ADDRESS, IIN_HOST);
		
		/*ADC_OPTION*/
		SM_Bus_Buffer_Tx[15] = 0xE0;
		SM_Bus_Buffer_Tx[14] = 0xFF;	
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[14],2,SLAVE_ADDRESS, ADC_OPTION);
	}
	else{
		/*CHARGER_OPTION0*/
		SM_Bus_Buffer_Tx[1] = 0x06;
		SM_Bus_Buffer_Tx[0] = 0x0E;
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[0],2,SLAVE_ADDRESS, CHARGER_OPTION0);
		
		/*CHARGER_CURRENT*/
		SM_Bus_Buffer_Tx[3] = 0x00;	
		SM_Bus_Buffer_Tx[2] = 0x00;
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[2],2,SLAVE_ADDRESS, CHARGER_CURRENT);

		/*CHARGER_VOLTAGE*/
		SM_Bus_Buffer_Tx[5] = 0x41;
		SM_Bus_Buffer_Tx[4] = 0xA0;
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[4],2,SLAVE_ADDRESS, CHARGER_VOLTAGE);

		/*CHARGER_STATUS*/	
//		SM_Bus_Buffer_Tx[7] = 0x80;
		SM_Bus_Buffer_Tx[6] = 0x00;
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[6],2,SLAVE_ADDRESS, CHARGER_STATUS);

		/*INPUT_VOLTAGE*/
		SM_Bus_Buffer_Tx[9] = 0x35;
		SM_Bus_Buffer_Tx[8] = 0x40;	
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[8],2,SLAVE_ADDRESS, INPUT_VOLTAGE);
		
		/*MIN_SYSTEM_VOLTAGE*/
		SM_Bus_Buffer_Tx[11] = 0x30;
		SM_Bus_Buffer_Tx[10] = 0x00;	
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[10],2,SLAVE_ADDRESS, MIN_SYSTEM_VOLTAGE);
		
		/*IIN_HOST*/
		SM_Bus_Buffer_Tx[13] = 0x41;
		SM_Bus_Buffer_Tx[12] = 0x00;	
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[12],2,SLAVE_ADDRESS, IIN_HOST);
		
		/*ADC_OPTION*/
		SM_Bus_Buffer_Tx[15] = 0xE0;
		SM_Bus_Buffer_Tx[14] = 0xFF;	
		SM_Bus_Master_BufferWrite(&SM_Bus_Buffer_Tx[14],2,SLAVE_ADDRESS, ADC_OPTION);
	}
}

/**
  * @brief  		ReadChargerParameters function. 
  *         
  * @param[in]  none.
  *         
  * @return 		none.
  *  
  */
void ReadChargerParameters(void)
{
	/*CHARGER_OPTION0*/
	SM_Bus_Master_BufferRead(&SM_Bus_Buffer_Rx[0],2,SLAVE_ADDRESS, CHARGER_OPTION0);
	
	/*CHARGER_CURRENT*/
	SM_Bus_Master_BufferRead(&SM_Bus_Buffer_Rx[2],2,SLAVE_ADDRESS, CHARGER_CURRENT);
	charger.charge_current_setted = (u16)( ( (SM_Bus_Buffer_Rx[3] << 8) | SM_Bus_Buffer_Rx[2] )  ) ;
	
	/*CHARGER_VOLTAGE*/
	SM_Bus_Master_BufferRead(&SM_Bus_Buffer_Rx[4],2,SLAVE_ADDRESS, CHARGER_VOLTAGE);
	charger.charge_voltage = (u16)( ( (SM_Bus_Buffer_Rx[5] << 8) | SM_Bus_Buffer_Rx[4] ) );
	
	/*CHARGER_STATUS*/
	SM_Bus_Master_BufferRead(&SM_Bus_Buffer_Rx[6],2,SLAVE_ADDRESS, CHARGER_STATUS);
	
	/*INPUT_VOLTAGE*/
	SM_Bus_Master_BufferRead(&SM_Bus_Buffer_Rx[8],2,SLAVE_ADDRESS, INPUT_VOLTAGE);

	/*MIN_SYSTEM_VOLTAGE*/
	SM_Bus_Master_BufferRead(&SM_Bus_Buffer_Rx[10],2,SLAVE_ADDRESS, MIN_SYSTEM_VOLTAGE);
	
	/*IIN_HOST*/
	SM_Bus_Master_BufferRead(&SM_Bus_Buffer_Rx[12],2,SLAVE_ADDRESS, IIN_HOST);
	
	/*ADCIBAT*/
	SM_Bus_Master_BufferRead(&SM_Bus_Buffer_Rx[14],2,SLAVE_ADDRESS, ADCIBAT);	
	charger.charge_current = (u16)( (SM_Bus_Buffer_Rx[15] & 0x7f) * 64 );			/*unit:mA*/
	charger.discharge_current = (u16)( (SM_Bus_Buffer_Rx[14] & 0x7f) * 256 );	/*unit:mA*/
			
	/*ADCVSYSVBAT*/
	SM_Bus_Master_BufferRead(&SM_Bus_Buffer_Rx[16],2,SLAVE_ADDRESS, ADCVSYSVBAT);		
	charger.battery_voltage = (u16)( (SM_Bus_Buffer_Rx[17]) * 64 + 2880 );	/*unit:mV*/
	charger.system_voltage = (u16)( (SM_Bus_Buffer_Rx[16]) * 64 + 2880 );		/*unit:mV*/
	
	
}


/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/


