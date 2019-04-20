
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

// Debugging
//#define DEBUG_TASK_SCHEDULER // Über GPIOs den Task Scheduler sichtbar machen

#ifdef DEBUG_TASK_SCHEDULER
#define DEBUG_TASK_A_ENABLE GPIO_WriteBit(GPIOB, GPIO_Pin_6, ENABLE);
#define DEBUG_TASK_A_DISABLE GPIO_WriteBit(GPIOB, GPIO_Pin_6, DISABLE);
#define DEBUG_TASK_B_ENABLE GPIO_WriteBit(GPIOB, GPIO_Pin_7, ENABLE);
#define DEBUG_TASK_B_DISABLE GPIO_WriteBit(GPIOB, GPIO_Pin_7, DISABLE);
#define DEBUG_TASK_C_ENABLE GPIO_WriteBit(GPIOB, GPIO_Pin_8, ENABLE);
#define DEBUG_TASK_C_DISABLE GPIO_WriteBit(GPIOB, GPIO_Pin_8, DISABLE);
#define DEBUG_TASK_D_ENABLE GPIO_WriteBit(GPIOB, GPIO_Pin_9, ENABLE);
#define DEBUG_TASK_D_DISABLE GPIO_WriteBit(GPIOB, GPIO_Pin_9, DISABLE);
#endif

// Externe Interrupts auslösen
#define TOGGLE_PIN_TASK_A   GPIO_WriteBit(GPIOA, GPIO_Pin_0, ENABLE); GPIO_WriteBit(GPIOA, GPIO_Pin_0, DISABLE);
#define TOGGLE_PIN_TASK_B   GPIO_WriteBit(GPIOA, GPIO_Pin_1, ENABLE); GPIO_WriteBit(GPIOA, GPIO_Pin_1, DISABLE);
#define TOGGLE_PIN_TASK_C   GPIO_WriteBit(GPIOA, GPIO_Pin_2, ENABLE); GPIO_WriteBit(GPIOA, GPIO_Pin_2, DISABLE);
#define TOGGLE_PIN_TASK_D   GPIO_WriteBit(GPIOA, GPIO_Pin_3, ENABLE); GPIO_WriteBit(GPIOA, GPIO_Pin_3, DISABLE);

#define TASK_A EXTI0_IRQHandler
#define TASK_B EXTI1_IRQHandler
#define TASK_C EXTI2_IRQHandler
#define TASK_D EXTI3_IRQHandler

/******************************************************************************
   Local Type-Definitions
******************************************************************************/   

/******************************************************************************
   Local Variables
******************************************************************************/   
#ifdef DEBUG_TASK_SCHEDULER
TUINT8 tsc_u8Task_A_Running;
TUINT8 tsc_u8Task_B_Running;
TUINT8 tsc_u8Task_C_Running;
TUINT8 tsc_u8Task_D_Running;
#endif

/******************************************************************************
   Local Function-Prototypes
******************************************************************************/   

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   


void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void TSC_Ini (void)
{
  TSC_u8Flag_1ms = 1;
  TSC_u8Flag_10ms = 1;
  TSC_u8Flag_100ms = 1;
  TSC_u8Flag_1s = 1;


  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // Pull Ups für die Hall-Sensoren
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0 | GPIO_PinSource1 | GPIO_PinSource2 | GPIO_PinSource3);




  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);


  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);


  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);


  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);



  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);


}

/******************************************************************************
   Description    : A
   Parameter      :
   Return-Value   :
******************************************************************************/

void TASK_A (void)
{
  EXTI_ClearITPendingBit(EXTI_Line0);

  #ifdef DEBUG_TASK_SCHEDULER
  tsc_u8Task_A_Running = 1;
  DEBUG_TASK_A_ENABLE;
  DEBUG_TASK_B_DISABLE;
  DEBUG_TASK_C_DISABLE;
  DEBUG_TASK_D_DISABLE;
  //Delay(1000);
  #endif


  CTL_1ms();


  #ifdef DEBUG_TASK_SCHEDULER
  DEBUG_TASK_A_DISABLE;
  tsc_u8Task_A_Running = 0;
  if (tsc_u8Task_B_Running) DEBUG_TASK_B_ENABLE;
  if ((!tsc_u8Task_B_Running) && (tsc_u8Task_C_Running)) DEBUG_TASK_C_ENABLE;
  if ((!tsc_u8Task_B_Running) && (!tsc_u8Task_C_Running) && (tsc_u8Task_D_Running)) DEBUG_TASK_D_ENABLE;
  #endif
}

/******************************************************************************
   Description    : B
   Parameter      :
   Return-Value   :
******************************************************************************/

void TASK_B (void)
{
  EXTI_ClearITPendingBit(EXTI_Line1);

  #ifdef DEBUG_TASK_SCHEDULER
  tsc_u8Task_B_Running = 1;
  DEBUG_TASK_B_ENABLE;
  DEBUG_TASK_C_DISABLE;
  DEBUG_TASK_D_DISABLE;
  //Delay(10000);
  #endif

  CTL_10ms();


  #ifdef DEBUG_TASK_SCHEDULER
  DEBUG_TASK_B_DISABLE;
  tsc_u8Task_B_Running = 0;
  if (tsc_u8Task_C_Running) DEBUG_TASK_C_ENABLE;
  if ((!tsc_u8Task_C_Running) && (tsc_u8Task_D_Running)) DEBUG_TASK_D_ENABLE;
  #endif
}

/******************************************************************************
   Description    : C
   Parameter      :
   Return-Value   :
******************************************************************************/

void TASK_C (void)
{
  EXTI_ClearITPendingBit(EXTI_Line2);

  #ifdef DEBUG_TASK_SCHEDULER
  tsc_u8Task_C_Running = 1;
  DEBUG_TASK_C_ENABLE;
  DEBUG_TASK_D_DISABLE;
  //Delay(50000);
  #endif

  CTL_100ms();


  #ifdef DEBUG_TASK_SCHEDULER
  DEBUG_TASK_C_DISABLE;
  tsc_u8Task_C_Running = 0;
  if (tsc_u8Task_D_Running) DEBUG_TASK_D_ENABLE;
  #endif
}

/******************************************************************************
   Description    : D
   Parameter      :
   Return-Value   :
******************************************************************************/

void TASK_D (void)
{
  EXTI_ClearITPendingBit(EXTI_Line3);

  #ifdef DEBUG_TASK_SCHEDULER
  tsc_u8Task_D_Running = 1;
  DEBUG_TASK_D_ENABLE;
  //Delay(400000);
  #endif


  CTL_1s();


  #ifdef DEBUG_TASK_SCHEDULER
  DEBUG_TASK_D_DISABLE;
  tsc_u8Task_D_Running = 0;
  #endif
}

/******************************************************************************
   Description    : Alle 1ms durch Timer Interrupt aufzurufen. Impementierung Task Scheduler
   Parameter      :
   Return-Value   :
******************************************************************************/

void TSC_1ms (void)
{
  static TUINT8 tsc_u8Prescaler_10ms = 0;
  static TUINT8 tsc_u8Periode_10ms = 10;

  static TUINT8 tsc_u8Prescaler_100ms = 0;
  static TUINT8 tsc_u8Periode_100ms = 10;

  static TUINT8 tsc_u8Prescaler_1s = 0;
  static TUINT8 tsc_u8Periode_1s = 10;



  TOGGLE_PIN_TASK_A;
  TSC_u8Flag_1ms = 1; // 1ms Flag

  if (tsc_u8Prescaler_10ms < tsc_u8Periode_10ms - 1)
  {
	tsc_u8Prescaler_10ms++;
  }
  else
  {
    TOGGLE_PIN_TASK_B;
    TSC_u8Flag_10ms = 1;  // 10ms Flag
    tsc_u8Prescaler_10ms = 0;


    if (tsc_u8Prescaler_100ms < tsc_u8Periode_100ms - 1)
    {
   tsc_u8Prescaler_100ms++;
    }
    else
    {
      TOGGLE_PIN_TASK_C;
      TSC_u8Flag_100ms = 1; // 100ms Flag
      tsc_u8Prescaler_100ms = 0;


      if (tsc_u8Prescaler_1s < tsc_u8Periode_1s - 1)
      {
    	tsc_u8Prescaler_1s++;
      }
      else
      {
    	TOGGLE_PIN_TASK_D;
        TSC_u8Flag_1s = 1; // 1s Flag
        tsc_u8Prescaler_1s = 0;
      }
    }
  }
}

/******************************************************************************

   Changes                  
   
[06.03.15] 
  
   
******************************************************************************/



