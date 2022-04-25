/**
  ******************************************************************************
  * @file    DrvSMBus.c
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

/* Includes ------------------------------------------------------------------*/
#include"DrvSMBus.h"

u8 SM_Bus_Buffer_Tx[20];
u8 SM_Bus_Buffer_Rx[20];

/**
  * @brief  		SM Bus Start function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  * @note 			START:when CLK is high,DATA change form high to low 
  */  
void SM_Bus_Start(void)
{
	SDA_OUT();
	SM_Bus_SDA=1;	  	  
	SM_Bus_SCL=1;
	Delay_Us(4);
 	SM_Bus_SDA=0;
	Delay_Us(4);
	/*Lock the SM bus,and prepare to send data.*/
	SM_Bus_SCL=0;
}


/**
  * @brief  		SM Bus Stop function. 
  *         
  * @param[in]	unsigned char ack
  *         
  * @return 		None
  *  
  */  
void SM_Bus_Stop(void)
{
	SDA_OUT();
	SM_Bus_SCL=0;
	/*STOP:when CLK is high DATA change form low to high*/
	SM_Bus_SDA=0;
 	Delay_Us(4);
	SM_Bus_SCL=1; 
	SM_Bus_SDA=1;
	Delay_Us(4);							   	
}



/**
  * @brief  		SM Bus Wait Ack function. 
  *         
  * @param[in]	unsigned char ack
  *         
  * @return 		None
  *  
  */  
u8 SM_Bus_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN(); 
	SM_Bus_SDA=1;
	Delay_Us(1);	   
	SM_Bus_SCL=1;
	Delay_Us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			SM_Bus_Stop();
			return 1;
		}
	}
	SM_Bus_SCL=0;   
	return 0;  
} 


/**
  * @brief  		SM Bus Ack function. 
  *         
  * @param[in]	unsigned char ack
  *         
  * @return 		None
  *  
  */  
void SM_Bus_Ack(void)
{
	SM_Bus_SCL=0;
	SDA_OUT();
	SM_Bus_SDA=0;
	Delay_Us(2);
	SM_Bus_SCL=1;
	Delay_Us(2);
	SM_Bus_SCL=0;
}


/**
  * @brief  		SM Bus NAck function. 
  *         
  * @param[in]	unsigned char ack
  *         
  * @return 		None
  *  
  */  	    
void SM_Bus_NAck(void)
{
	SM_Bus_SCL=0;
	SDA_OUT();
	SM_Bus_SDA=1;
	Delay_Us(2);
	SM_Bus_SCL=1;
	Delay_Us(2);
	SM_Bus_SCL=0;
}	

/**
  * @brief  		SM Bus initial function. 
  *         
  * @param[in]	unsigned char ack
  *         
  * @return 		None
  *  
  */  		  
void SM_Bus_Send_Byte(u8 data)
{                        
  u8 t;   
	SDA_OUT(); 	    
  SM_Bus_SCL=0;
	for(t=0;t<8;t++)
	{              
		SM_Bus_SDA=(data&0x80)>>7;
		data<<=1; 	  
		Delay_Us(2);
		SM_Bus_SCL=1;
		Delay_Us(2); 
		SM_Bus_SCL=0;	
		Delay_Us(2);
	}	 
}


/**
  * @brief  		SM Bus Read Byte function. 
  *         
  * @param[in]	unsigned char ack
  *         
  * @return 		None
  *  
  */  
u8 SM_Bus_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
  for(i=0;i<8;i++ )
	{
		SM_Bus_SCL=0; 
		Delay_Us(2);
		SM_Bus_SCL=1;
		receive<<=1;
		if(READ_SDA){
			receive++; 
		}			
		Delay_Us(1); 
	}		 
    if (!ack){
        SM_Bus_NAck();
		}
    else{
        SM_Bus_Ack();  
		}
		
    return receive;
}

/**
  * @brief  		SM Bus initial function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  *  
  */
void SMbus_Init(void) 
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 
}   

/**
  * @brief  		SM_Bus_Master_BufferWrite function. 
  *          
  * @param[in]  pBuffer: the buffer to write.
	* @param[in]	NumByteToWrite : the number to write.
	* @param[in]	SlaveAddress : slave's address.
  *  
	* @return 		SET : no data sent; RESET : data sent succeed.
  *  
  */
void SM_Bus_Master_BufferWrite(uint8_t* pBuffer, uint32_t NumByteToWrite, uint8_t SlaveAddress, uint8_t SlaveCommand)
{
    if(NumByteToWrite == 0){
       return;
		}
		
    /* 1.Start IIC.*/		
		SM_Bus_Start();
		
    /* 2.Write slave's address. */
		SM_Bus_Send_Byte(SlaveAddress);
		SM_Bus_Wait_Ack();
		
    /* 3.Write command byte.*/
		SM_Bus_Send_Byte(SlaveCommand);
		SM_Bus_Wait_Ack();
		
    /* 4.Write data. */
    while(NumByteToWrite--)
    {
      SM_Bus_Send_Byte(*pBuffer);
			SM_Bus_Wait_Ack();
      pBuffer++;
    }

    /* 5.Stop IIC. */
		SM_Bus_Stop();

}

/**
  * @brief  		SM_Bus_Master_BufferRead function. 
  *         
  * @param[in]  pBuffer: the buffer to write.
	* @param[in]	NumByteToRead : the number to read.
	* @param[in]	SlaveAddress : slave's address.
  *         
  * @return 		SET : no data sent; RESET : data sent succeed.
  *  
  */
void SM_Bus_Master_BufferRead(uint8_t* pBuffer, uint32_t NumByteToRead, uint8_t SlaveAddress, uint8_t SlaveCommand)
{
    if(NumByteToRead == 0){
			return;  
		}
		
    /* 1.Start IIC.*/		
		SM_Bus_Start();
		
    /* 2.Write slave's address. */
		SM_Bus_Send_Byte(SlaveAddress);
		SM_Bus_Wait_Ack();
		
    /* 3.Write command byte.*/
		SM_Bus_Send_Byte(SlaveCommand);
		SM_Bus_Wait_Ack();
	
    /* 4.Start IIC.*/
		SM_Bus_Start();
		
    /* 5.Write slave's address in read mode. */
		SM_Bus_Send_Byte(SlaveAddress+0x01);
		SM_Bus_Wait_Ack();

    /* 6.Read slave's data. */
    while (NumByteToRead)
    {
			if(NumByteToRead == 1){
				*pBuffer++ = SM_Bus_Read_Byte(0);
				SM_Bus_Stop();
			}
			else{
				*pBuffer++ = SM_Bus_Read_Byte(1);
			}
			
			NumByteToRead--;
    }

}




/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/


