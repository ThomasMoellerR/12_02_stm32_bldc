
/******************************************************************************

   File                :     USART3.c
   Version             :     1

   Version Temp-File   :     2

******************************************************************************/

/******************************************************************************
   Include-Files
******************************************************************************/

#include "hea.h"

/******************************************************************************
   Local Constants
******************************************************************************/

/******************************************************************************
   Local Type-Definitions
******************************************************************************/

/******************************************************************************
   Local Variables
******************************************************************************/

/******************************************************************************
   Local Function-Prototypes
******************************************************************************/

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void USART3_Ini (void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  // Tx
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; // Tx
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART3, USART_IT_TC, ENABLE);

  USART_Cmd(USART3, ENABLE);
}

/******************************************************************************
   Description    : Interrupt Handler
   Parameter      :
   Return-Value   :
******************************************************************************/

void USART3_IRQHandler (void)
{
  TUINT8 u8Temp;

  if (USART_GetITStatus(USART3, USART_IT_TC) != RESET)
  {
    if (!SER3_u8SndBuf_Empty())
    {
	  u8Temp = SER3_u8SndBuf_Get();
	  USART_SendData(USART3, u8Temp);
    }
    else
    {
    	SER3_u8Running = 0;
    }

    USART_ClearITPendingBit(USART3,USART_IT_TC);
  }

  if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
    u8Temp = USART_ReceiveData(USART3);

    SER3_RecBuf_Put(u8Temp);

    USART_ClearITPendingBit(USART3,USART_IT_RXNE);
  }

}

