/**
  ******************************************************************************
  * @file    DrvSYS.c
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about the system.. 
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
#include "DrvSYS.h"

/**
  * @brief  		Wait for interrupt
  *         
  * @param[in] 	None
  *         
  * @return 		None
  */
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}

/**
  * @brief  		Disable all interrupts
  *         
  * @param[in]  None
  *         
  * @return 		None
  */
void INTX_DISABLE(void)
{
	__ASM volatile("cpsid i");
}

/**
  * @brief  		Enable all interrupts
  *         
  * @param[in]  None
  *         
  * @return 		None
  */
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}

/**
  * @brief  		Set the Main value of the stack address
  *         
  * @param[in]  u32 addr
  *         
  * @return 		None
  */
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}


/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/
