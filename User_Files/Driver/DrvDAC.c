/**
  ******************************************************************************
  * @file    DrvDac.c
  * @author  Best Team
  * @version V1.0.0
  * @date    24-June-2021
  * @brief   This file provides the function about DAC.. 
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
#include "DrvDac.h"

/**
  * @brief  		Handling the DAC1_Init function. 
  *         
  * @param[in]	None
  *         
  * @return 		None
  */
void DAC2_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��PORTAͨ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //ʹ��DACͨ��ʱ�� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 // �˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //ģ������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_5)	;//PA.5 �����
					
	DAC_InitType.DAC_Trigger = DAC_Trigger_None;	//��ʹ�ô������� TEN1=0
	DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
	DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Disable ;	//DAC1�������ر� BOFF1=1
	DAC_Init(DAC_Channel_1,&DAC_InitType);	 //��ʼ��DACͨ��1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DAC1

	DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12λ�Ҷ������ݸ�ʽ����DACֵ

}


/******************* (C) COPYRIGHT 2021 Best team *****END OF FILE****/



