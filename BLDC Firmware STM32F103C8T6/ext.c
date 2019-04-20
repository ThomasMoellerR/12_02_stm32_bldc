
/******************************************************************************

   File                :     tmp.c
   Letze Ã„nderung	   :     06.03.15 10:34
   
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

void EXT_Ini (void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Pull Ups für die Hall-Sensoren
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5 | GPIO_PinSource6 | GPIO_PinSource7);





  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void EXTI9_5_IRQHandler (void)
{
  EXTI_ClearITPendingBit(EXTI_Line5 | EXTI_Line6 | EXTI_Line7);
  BLDC_Hall_Interrupt();
}








/******************************************************************************

   Changes                  
   
[06.03.15] 
  
   
******************************************************************************/



