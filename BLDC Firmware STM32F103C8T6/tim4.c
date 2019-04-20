
/******************************************************************************

   File                :     tim3.c
   Version             :     1
   
   Version Temp-File   :     3
   
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

void TIM3_Ini (void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBase_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;


  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  // 72.000.000 / 18000 = 4000 -> Prescaler
  // 4000 / 4000 = 1Hz = F -> Period
  // T = 1/F = 1 / 1Hz = 1s
  TIM_TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBase_InitStructure.TIM_Period = 400 - 1; // 10ms 4000 - 1;
  TIM_TimeBase_InitStructure.TIM_Prescaler = 180 - 1; // 10ms 180 - 1;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBase_InitStructure);

  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM3, ENABLE);
}

/******************************************************************************
   Description    : 10ms
   Parameter      :
   Return-Value   :
******************************************************************************/

void TIM3_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

  TSC_1ms();


}


/******************************************************************************

   Changes                  
   
   a) 
  
   
******************************************************************************/



