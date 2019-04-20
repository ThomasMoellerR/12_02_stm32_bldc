
/******************************************************************************

   File                :     TIM2.c
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

void TIM2_Ini (void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBase_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;


  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  // 72.000.000 / 18000 = 4000 -> Prescaler
  // 4000 / 4000 = 1Hz = F -> Period
  // T = 1/F = 1 / 1Hz = 1s
  TIM_TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBase_InitStructure.TIM_Period = TIM2_PERIOD_COUNTER ; // Gleicher Wert wie in TIM2_IRQHandler
  TIM_TimeBase_InitStructure.TIM_Prescaler = 10;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBase_InitStructure);



  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);


  TIM_Cmd(TIM2, ENABLE);



  // Debug
  /*
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  while (1);
  */
}

/******************************************************************************
   Description    : Überlauf bei 10,01ms (gemessen mit Logic Analyzer)
   	   	   	   	    Die Überlaufzeit ist nicht wichtig. Können auch 10,15ms sein. Wichitg ist für die Drehzahlberechnung, dass die Zeit bekannt ist.
   	   	   	   	    TIM_Period = 65535;
   	   	   	   	    TIM_Prescaler = 10;
   Parameter      :
   Return-Value   :
******************************************************************************/

void TIM2_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

  //GPIO_WriteBit(GPIOB, GPIO_Pin_5, ENABLE);
  //GPIO_WriteBit(GPIOB, GPIO_Pin_5, DISABLE);

  // Debug auf Pin (Phase A+)
  //GPIO_WriteBit(GPIOA, GPIO_Pin_8, ENABLE);
  //GPIO_WriteBit(GPIOA, GPIO_Pin_8, DISABLE);

  BLDC_u32Counter_With_Overflow_Respecting += TIM2_PERIOD_COUNTER;
}


/******************************************************************************

   Changes                  
   
   a) 
  
   
******************************************************************************/



