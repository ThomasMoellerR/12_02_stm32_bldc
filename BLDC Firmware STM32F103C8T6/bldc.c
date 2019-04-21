
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

#define EN_1		TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable)
#define DIS_1		TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable)
#define EN_1N		TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable)
#define DIS_1N		TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable)

#define EN_2		TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable)
#define DIS_2		TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable)
#define EN_2N		TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable)
#define DIS_2N		TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable)

#define EN_3		TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable)
#define DIS_3		TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable)
#define EN_3N		TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable)
#define DIS_3N		TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable)

#define PWM_1		TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1) // TIM_OCMode_PWM1
#define PWM_2		TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1)
#define PWM_3		TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1)

#define ACTIVE_1	TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_ForcedAction_Active)
#define ACTIVE_2	TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_ForcedAction_Active)
#define ACTIVE_3	TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_ForcedAction_Active)


#define LISTEN_TO_PHASE_A_FALLING		0
#define LISTEN_TO_PHASE_B_FALLING		1
#define LISTEN_TO_PHASE_C_FALLING		2

#define LISTEN_TO_PHASE_A_RISING		3
#define LISTEN_TO_PHASE_B_RISING		4
#define LISTEN_TO_PHASE_C_RISING		5

#define LISTEN_TO_PHASE_A_RISING_FALLING		6
#define LISTEN_TO_PHASE_B_RISING_FALLING		7
#define LISTEN_TO_PHASE_C_RISING_FALLING		8

#define LISTEN_TO_PHASE_ABC_RISING_FALLING		9

#define BLDC_FORWARDS	0
#define BLDC_BACKWARDS	1

/******************************************************************************
   Local Type-Definitions
******************************************************************************/   

/******************************************************************************
   Local Variables
******************************************************************************/

// LookUpTable Sensorless                         1 2 3 4 5 6      1 2 3 4 5 6
TUINT8 bldc_au8LookUpTable_Sensorless[2][7] = {{0,2,3,4,5,6,1}, {0,6,1,2,3,4,5}};

// Hall
TUINT8 bldc_au8LookUpTable_Hall[2][7];


// Startup Hall
TUINT8 bldc_au8LookUpTable_Hall_Startup[2][7];

// Automatic Hall Detection
TUINT8 bldc_au8LookUpTable_Automatic_Hall_Detection [7];


TUINT8 au8Temp[256];
TUINT16 bldc_PWM;

TUINT8 bldc_u8Hall_Pattern;
TUINT8 bldc_u8State = 1;
TUINT8 bldc_u8Direction = 0;

TUINT32 bldc_au32Speed_Counters[7]; // [0] unused für die Geschwindigkeit
TUINT16 bldc_u16Speed_Counter_Overflow;


TUINT8 bldc_Mode = BLDC_MODE_HALL;

TUINT8 bldc_u8MotorType; // 0 = Hall, 1 = Sensorless

TUINT32 bldc_au32Time_Counter[7]; // Überlauf * Maximaler Zählwer + Aktueller Zählwert
TUINT32 bldc_au32Time_Counter_Backup[7];

TUINT16 bldc_au16HallsignalPeriode[7];

TUINT16 bldc_au16Periode;



/******************************************************************************
   Local Function-Prototypes
******************************************************************************/   

TUINT8 bldc_Get_Hall(void);
TUINT32 bldc_Get_Period(TUINT8 u8Pattern, TUINT32 u32Counter_Value);

void bldc_Commute(void);
void bldc_Prepare_Interrupts(void);
void bldc_Configure_Interrupts(TUINT8 u8Config);
void bldc_Invert_Index_and_Value (TUINT8* pu8Ptr);



/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

void BLDC_Ini (void)
{
  // Sicherer Zustand
  DIS_1;
  DIS_2;
  DIS_3;
  DIS_1N;
  DIS_2N;
  DIS_3N;

#ifdef BLDC_DEBUG_ALL_HIGH_SIDE_MOSFETS_ENABLE
  ACTIVE_1;
  EN_1;

  ACTIVE_2;
  EN_2;

  ACTIVE_3;
  EN_3;

  while (1);
#endif

#ifdef BLDC_DEBUG_ALL_LOW_SIDE_MOSFETS_ENABLE
  ACTIVE_1;
  EN_1N;

  ACTIVE_2;
  EN_2N;

  ACTIVE_3;
  EN_3N;

  while (1);
#endif

#ifdef BLDC_DEBUG_STATE_1
  DIS_1;
  DIS_2;
  DIS_3;
  DIS_1N;
  DIS_2N;
  DIS_3N;

  ACTIVE_1;
  EN_1;
  ACTIVE_2;
  EN_2N;

  while(1);
#endif

#ifdef BLDC_DEBUG_STATE_2
  DIS_1;
  DIS_2;
  DIS_3;
  DIS_1N;
  DIS_2N;
  DIS_3N;

  ACTIVE_3;
  EN_3;
  ACTIVE_2;
  EN_2N;

  while(1);
#endif

#ifdef BLDC_DEBUG_STATE_3
  DIS_1;
  DIS_2;
  DIS_3;
  DIS_1N;
  DIS_2N;
  DIS_3N;

  ACTIVE_3;
  EN_3;
  ACTIVE_1;
  EN_1N;

  while(1);
#endif

#ifdef BLDC_DEBUG_STATE_4
  DIS_1;
  DIS_2;
  DIS_3;
  DIS_1N;
  DIS_2N;
  DIS_3N;

  ACTIVE_2;
  EN_2;
  ACTIVE_1;
  EN_1N;

  while(1);
#endif

#ifdef BLDC_DEBUG_STATE_5
  DIS_1;
  DIS_2;
  DIS_3;
  DIS_1N;
  DIS_2N;
  DIS_3N;

  ACTIVE_2;
  EN_2;
  ACTIVE_3;
  EN_3N;

  while(1);
#endif

#ifdef BLDC_DEBUG_STATE_6
  DIS_1;
  DIS_2;
  DIS_3;
  DIS_1N;
  DIS_2N;
  DIS_3N;

  ACTIVE_1;
  EN_1;
  ACTIVE_3;
  EN_3N;

  while(1);
#endif


 // BLDC_Set_Hall(Init_Hall_Pattern);






#ifdef BLDC_SENSORLESS

  BLDC_Set_PWM(300);
  bldc_u8State = bldc_au8LookUpTable_Sensorless[bldc_u8Direction][bldc_u8State];
  bldc_Commute();
  bldc_Prepare_Interrupts();

#endif


#ifdef BLDC_DEBUG_EXT_INT_PHASE_A
  bldc_Configure_Interrupts(LISTEN_TO_PHASE_A_RISING_FALLING);
#endif

#ifdef BLDC_DEBUG_EXT_INT_PHASE_B
  bldc_Configure_Interrupts(LISTEN_TO_PHASE_B_RISING_FALLING);
#endif

#ifdef BLDC_DEBUG_EXT_INT_PHASE_C
  bldc_Configure_Interrupts(LISTEN_TO_PHASE_C_RISING_FALLING);
#endif

#ifdef BLDC_DEBUG_EXT_INT_PHASE_ABC
  bldc_Configure_Interrupts(LISTEN_TO_PHASE_ABC_RISING_FALLING);
#endif
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void BLDC_Set_Hall(TUINT8* pHall)
{
	// Hall Vorwärtslauf
	bldc_au8LookUpTable_Hall[0][1] = pHall[0];
	bldc_au8LookUpTable_Hall[0][2] = pHall[1];
	bldc_au8LookUpTable_Hall[0][3] = pHall[2];
	bldc_au8LookUpTable_Hall[0][4] = pHall[3];
	bldc_au8LookUpTable_Hall[0][5] = pHall[4];
	bldc_au8LookUpTable_Hall[0][6] = pHall[5];

	// Hall Rückwärtslauf
	bldc_au8LookUpTable_Hall[1][1] = bldc_au8LookUpTable_Hall[0][6];
	bldc_au8LookUpTable_Hall[1][2] = bldc_au8LookUpTable_Hall[0][5];
	bldc_au8LookUpTable_Hall[1][3] = bldc_au8LookUpTable_Hall[0][4];
	bldc_au8LookUpTable_Hall[1][4] = bldc_au8LookUpTable_Hall[0][3];
	bldc_au8LookUpTable_Hall[1][5] = bldc_au8LookUpTable_Hall[0][2];
	bldc_au8LookUpTable_Hall[1][6] = bldc_au8LookUpTable_Hall[0][1];

	// Hall Startup Vorwärtslauf
	memcpy(bldc_au8LookUpTable_Hall_Startup[0], bldc_au8LookUpTable_Hall[0], 7);
	bldc_Invert_Index_and_Value (bldc_au8LookUpTable_Hall_Startup); // Hall Startup Backup invertieren

	// Hall Startup Rückwärtslauf
	bldc_au8LookUpTable_Hall_Startup[1][1] = bldc_au8LookUpTable_Hall_Startup[0][6];
	bldc_au8LookUpTable_Hall_Startup[1][2] = bldc_au8LookUpTable_Hall_Startup[0][5];
	bldc_au8LookUpTable_Hall_Startup[1][3] = bldc_au8LookUpTable_Hall_Startup[0][4];
	bldc_au8LookUpTable_Hall_Startup[1][4] = bldc_au8LookUpTable_Hall_Startup[0][3];
	bldc_au8LookUpTable_Hall_Startup[1][5] = bldc_au8LookUpTable_Hall_Startup[0][2];
	bldc_au8LookUpTable_Hall_Startup[1][6] = bldc_au8LookUpTable_Hall_Startup[0][1];

	// Abhängig von der Rotorposition die Endstufe vorbereiten. Wenn eine PWM kommt, fließt Strom
	bldc_u8Hall_Pattern = bldc_Get_Hall();
	bldc_u8State = bldc_au8LookUpTable_Hall_Startup[bldc_u8Direction][bldc_u8Hall_Pattern];
	bldc_Commute();

}




/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void BLDC_Hall_Interrupt(void)
{
  static TUINT8 u8Hall_Old;

  switch (bldc_Mode)
  {
    case BLDC_MODE_HALL:  		bldc_u8Hall_Pattern = bldc_Get_Hall();
    						bldc_u8State = bldc_au8LookUpTable_Hall[bldc_u8Direction][bldc_u8Hall_Pattern];
    						bldc_Commute();
    						break;

    case BLDC_MODE_SENSORLESS:  	bldc_u8State = bldc_au8LookUpTable_Sensorless[bldc_u8Direction][bldc_u8State];
    						bldc_Commute();
    						bldc_Prepare_Interrupts(); // bei bestimmten Interrupt auslösen, im Gegensatz zu Hall (auf alle Interrupts hören)
    						break;

    // Es wird außerhalb des BLDC Moduls kommutiert
    case BLDC_MODE_MANUAL_KOMMUTATION:  	bldc_au8LookUpTable_Automatic_Hall_Detection[bldc_u8State] = u8Hall_Old;
    						u8Hall_Old = bldc_Get_Hall();
    						break;

    default:				break;

  }





  // Messverfahren A
  BLDC_u32HallInterrupt_Counter_A++;
  BLDC_u32HallInterrupt_Counter_B++;
  BLDC_u32HallInterrupt_Counter_C++;

  // Messverfahren B
  BLDC_au32Physical_Period[bldc_u8State] =  BLDC_u32Counter_With_Overflow_Respecting + TIM_GetCounter(TIM2);
  TIM_SetCounter(TIM2, 0);
  BLDC_u32Counter_With_Overflow_Respecting = 0;

  BLDC_u32Latest_Period = BLDC_au32Physical_Period[bldc_u8State];

}




/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void bldc_Commute(void)
{
	/*
  if (bldc_u8Direction == BLDC_FORWARDS)
  {
    switch (bldc_u8State)
    {
      case 1:	DIS_3N;

    			ACTIVE_2;
    			EN_2N;
    			break;

      case 2:	DIS_1;

    			PWM_3;
    			EN_3;
    			break;

      case 3:	DIS_2N;

    			ACTIVE_1;
    			EN_1N;
	    		break;

      case 4:	DIS_3;

      	  	  	PWM_2;
      	  	  	EN_2;
      	  	  	break;

      case 5:	DIS_1N;

    			ACTIVE_3;
    			EN_3N;
    			break;

      case 6:	DIS_2;

    			PWM_1;
    			EN_1;
    			break;

      default: break;
    }
  }
  else
  {
    switch (bldc_u8State)
    {
      case 1:	DIS_3;

      	  	  	PWM_1;
    			EN_1;
    			break;

      case 2:	DIS_1N;

      	  	    ACTIVE_2;
    			EN_2N;
    			break;

      case 3:	DIS_2;

      	  	  	PWM_3;
    			EN_3;
	    		break;

      case 4:	DIS_3N;

      	  	    ACTIVE_1;
      	  	  	EN_1N;
      	  	  	break;

      case 5:	DIS_1;

      	  	    PWM_2;
    			EN_2;
    			break;

      case 6:	DIS_2N;

      	  	    ACTIVE_3;
    			EN_3N;
    			break;

      default: break;
    }
  }

*/




	switch (bldc_u8State)
	    {
	      case 1:	DIS_1N;
	    			DIS_3N;
	    			DIS_2;
	    			DIS_3;

#ifdef BLDC_PWM_HIGH_SIDE_MOSFETS

	    			ACTIVE_2;
	    			EN_2N;

	    			PWM_1;
	    			EN_1;

#else

	    			ACTIVE_1;
	    			EN_1;

	    			PWM_2;
	    			EN_2N;

#endif

	    			break;

	      case 2:	DIS_1N;
	                DIS_3N;
	                DIS_1;
	                DIS_2;

#ifdef BLDC_PWM_HIGH_SIDE_MOSFETS

	    			ACTIVE_2;
	    			EN_2N;

	    			PWM_3;
	    			EN_3;
#else

	    			ACTIVE_3;
	    			EN_3;

	    			PWM_2;
	    			EN_2N;

#endif
	    			break;

	      case 3:	DIS_2N;
	                DIS_3N;
	                DIS_1;
	                DIS_2;

#ifdef BLDC_PWM_HIGH_SIDE_MOSFETS

	    			ACTIVE_1;
	    			EN_1N;

	    			PWM_3;
	    			EN_3;
#else

	    			ACTIVE_3;
	    			EN_3;

	    			PWM_1;
	    			EN_1N;

#endif
	    			break;

	      case 4:	DIS_2N;
	                DIS_3N;
	                DIS_1;
	                DIS_3;

#ifdef BLDC_PWM_HIGH_SIDE_MOSFETS

	    			ACTIVE_1;
	    			EN_1N;

	    			PWM_2;
	    			EN_2;
#else

	    			ACTIVE_2;
	    			EN_2;

	    			PWM_1;
	    			EN_1N;

#endif
	    			break;

	      case 5:	DIS_1N;
	                DIS_2N;
	                DIS_1;
	                DIS_3;

#ifdef BLDC_PWM_HIGH_SIDE_MOSFETS

	    			ACTIVE_3;
	    			EN_3N;

	    			PWM_2;
	    			EN_2;
#else

	    			ACTIVE_2;
	    			EN_2;

	    			PWM_3;
	    			EN_3N;

#endif
	    			break;

	      case 6:	DIS_1N;
	                DIS_2N;
	                DIS_2;
	                DIS_3;

#ifdef BLDC_PWM_HIGH_SIDE_MOSFETS

	    			ACTIVE_3;
	    			EN_3N;

	    			PWM_1;
	    			EN_1;
#else

	    			ACTIVE_1;
	    			EN_1;

	    			PWM_3;
	    			EN_3N;

#endif
	    			break;


	      default: break;
	    }



}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void bldc_Prepare_Interrupts(void)
{
  if (bldc_u8Direction == BLDC_FORWARDS)
  {
    switch (bldc_u8State)
    {
      case 1:	bldc_Configure_Interrupts(LISTEN_TO_PHASE_C_RISING);
    			break;

      case 2:	bldc_Configure_Interrupts(LISTEN_TO_PHASE_A_FALLING);
    			break;

      case 3:	bldc_Configure_Interrupts(LISTEN_TO_PHASE_B_RISING);
	    		break;

      case 4:	bldc_Configure_Interrupts(LISTEN_TO_PHASE_C_FALLING);
      	  	  	break;

      case 5:	bldc_Configure_Interrupts(LISTEN_TO_PHASE_A_RISING);
    			break;

      case 6:	bldc_Configure_Interrupts(LISTEN_TO_PHASE_B_FALLING);
    			break;

      default: break;
    }
  }
  else
  {
    switch (bldc_u8State)
	{
	  case 1:	bldc_Configure_Interrupts(LISTEN_TO_PHASE_C_FALLING);
	  	  	    break;

	  case 2:	bldc_Configure_Interrupts(LISTEN_TO_PHASE_A_RISING);
	  	  	  	break;

	  case 3:	bldc_Configure_Interrupts(LISTEN_TO_PHASE_B_FALLING);
		    	break;

	  case 4:	bldc_Configure_Interrupts(LISTEN_TO_PHASE_C_RISING);
	      	  	break;

	  case 5:	bldc_Configure_Interrupts(LISTEN_TO_PHASE_A_FALLING);
	    		break;

	  case 6:	bldc_Configure_Interrupts(LISTEN_TO_PHASE_B_RISING);
	    		break;

	  default: break;
    }
  }


 // if ((bldc_u8State == 1) || (bldc_u8State == 4)) bldc_Configure_Interrupts(LISTEN_TO_PHASE_C_RISING_FALLING);
 // if ((bldc_u8State == 2) || (bldc_u8State == 5)) bldc_Configure_Interrupts(LISTEN_TO_PHASE_A_RISING_FALLING);
 // if ((bldc_u8State == 3) || (bldc_u8State == 6)) bldc_Configure_Interrupts(LISTEN_TO_PHASE_B_RISING_FALLING);

}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void bldc_Configure_Interrupts(TUINT8 u8Config)
{
  EXTI_InitTypeDef EXTI_InitStructure;

  switch (u8Config)
  {
    case LISTEN_TO_PHASE_A_FALLING:	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	  	  	  	  	  				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  	  	  	  	  				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	  	  	  	  	  				EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  	  	  	  	  				EXTI_Init(&EXTI_InitStructure);
	  	  	  	  	  				break;

    case LISTEN_TO_PHASE_B_FALLING:	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	  	  	  	  	  				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  	  	  	  	  				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	  	  	  	  	  				EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  	  	  	  	  				EXTI_Init(&EXTI_InitStructure);
	  	  	  	  	  				break;

    case LISTEN_TO_PHASE_C_FALLING:	EXTI_InitStructure.EXTI_Line = EXTI_Line7;
	  	  	  	  	  				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  	  	  	  	  				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	  	  	  	  	  				EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  	  	  	  	  				EXTI_Init(&EXTI_InitStructure);
	  	  	  	  	  				break;

    case LISTEN_TO_PHASE_A_RISING:	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	  	  	  	  	  				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  	  	  	  	  				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	  	  	  	  	  				EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  	  	  	  	  				EXTI_Init(&EXTI_InitStructure);
	  	  	  	  	  				break;

    case LISTEN_TO_PHASE_B_RISING:	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	  	  	  	  	  				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  	  	  	  	  				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	  	  	  	  	  				EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  	  	  	  	  				EXTI_Init(&EXTI_InitStructure);
	  	  	  	  	  				break;

    case LISTEN_TO_PHASE_C_RISING:	EXTI_InitStructure.EXTI_Line = EXTI_Line7;
	  	  	  	  	  				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  	  	  	  	  				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	  	  	  	  	  				EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  	  	  	  	  				EXTI_Init(&EXTI_InitStructure);
	  	  	  	  	  				break;

   case LISTEN_TO_PHASE_A_RISING_FALLING:	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
 	  	  	  	  	  				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
 	  	  	  	  	  				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
 	  	  	  	  	  				EXTI_InitStructure.EXTI_LineCmd = ENABLE;
 	  	  	  	  	  				EXTI_Init(&EXTI_InitStructure);
 	  	  	  	  	  				break;

   case LISTEN_TO_PHASE_B_RISING_FALLING:	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
 	  	  	  	  	  				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
 	  	  	  	  	  				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
 	  	  	  	  	  				EXTI_InitStructure.EXTI_LineCmd = ENABLE;
 	  	  	  	  	  				EXTI_Init(&EXTI_InitStructure);
 	  	  	  	  	  				break;

   case LISTEN_TO_PHASE_C_RISING_FALLING:	EXTI_InitStructure.EXTI_Line = EXTI_Line7;
 	  	  	  	  	  				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
 	  	  	  	  	  				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
 	  	  	  	  	  				EXTI_InitStructure.EXTI_LineCmd = ENABLE;
 	  	  	  	  	  				EXTI_Init(&EXTI_InitStructure);
 	  	  	  	  	  				break;


   case LISTEN_TO_PHASE_ABC_RISING_FALLING:	  EXTI_InitStructure.EXTI_Line = EXTI_Line5 | EXTI_Line6 | EXTI_Line7;
    	 	 	 	 	 	 	 	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    	 	 	 	 	 	 	 	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    	 	 	 	 	 	 	 	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    	 	 	 	 	 	 	 	EXTI_Init(&EXTI_InitStructure);
    	 	 	 	 	 	 	 	break;


  default :							 break;
  }

}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void BLDC_Set_PWM(TUINT16 u16PWM)
{
  if (bldc_PWM != u16PWM)
  {
    if (u16PWM > BLDC_MAX_PWM) u16PWM = BLDC_MAX_PWM;
    TIM1->CCR1 = u16PWM;
    TIM1->CCR2 = u16PWM;
    TIM1->CCR3 = u16PWM;

    bldc_PWM = u16PWM;
  }
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

TUINT16 BLDC_u16Get_PWM(void)
{
  return bldc_PWM;
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void BLDC_Set_Direction (TUINT8 u8Direction)
{
  if(u8Direction != bldc_u8Direction) // Richtungswechsel? Einmaliger Aufruf
  {
    bldc_u8Direction = u8Direction;
    bldc_u8State = bldc_au8LookUpTable_Hall[bldc_u8Direction][bldc_u8Hall_Pattern];
    bldc_Commute();
  }
}



/******************************************************************************
   Description    : Der Timer läuft immer weiter, auch nach einem Überlauf wird er nicht zurückgesetzt.
   	   	   	   	    Die Zeit wird rückgerechnet.
   	   	   	   	    Dieses Verfahren ist für mehr als eine Zeitmessung notwendig.
					Bei nur einer einzigen Zeitmessung könnte man einfach den Zähler zurücksetzen. Hier jedoch nicht
   Parameter      :
   Return-Value   :
******************************************************************************/

TUINT32 bldc_Get_Period(TUINT8 u8State, TUINT32 u32Counter_Value)
{
  static TUINT32 u32Ret;

  // Alter Wert - Aktueller Wert
  u32Ret = bldc_au32Speed_Counters[u8State] - u32Counter_Value;


  bldc_au32Speed_Counters[u8State] = u32Counter_Value;

  return u32Ret;
}

/******************************************************************************
   Description    : Liefert Hall Muster zurück.
                    Überprüfung, ob Pattern Zwischen 1 - 6. Ist das nicht der Fall, liefere 1.
                    Wenn kein Hall-Sensor angeschlossen ist (Alle Bits auf 1) enstpricht einer 7, darf die 7 nicht
                    weiterverarbeitet werden.
   Parameter      :
   Return-Value   :
******************************************************************************/

TUINT8 bldc_Get_Hall(void)
{
  static TUINT8 u8Pattern;
  u8Pattern = (TUINT8) GPIO_ReadInputData(GPIOA);
  u8Pattern >>= 5;

  if ((u8Pattern >= 1) && (u8Pattern <= 6))
  {
    // Alles OK
  }
  else
  {
    u8Pattern = 1;
  }

  return u8Pattern;
}

/******************************************************************************
   Description    : Setzt das Drehfeld einen Schritt weiter
   Parameter      :
   Return-Value   :
******************************************************************************/

void BLDC_Manual_Commutation(void)
{
  bldc_u8State = bldc_au8LookUpTable_Sensorless[bldc_u8Direction][bldc_u8State];
  bldc_Commute();
}

/******************************************************************************
   Description    : Gibt das automatich erkannte Kommutierungsmuster als String zurück
   Parameter      :
   Return-Value   :
******************************************************************************/

TUINT8* BLDC_pu8Automatic_Hall_Detection(void)
{
  TUINT8 au8arr[7];

  memcpy(au8arr, bldc_au8LookUpTable_Automatic_Hall_Detection, 7);
  bldc_Invert_Index_and_Value(au8arr);

  sprintf((char*)au8Temp, "{0,%d,%d,%d,%d,%d,%d}", au8arr[1], au8arr[2], au8arr[3], au8arr[4], au8arr[5], au8arr[6]); // {0,3,1,2,5,4,6}
  au8Temp[strlen(au8Temp)] = 0; // Nullterminator

  return au8Temp;
}

/******************************************************************************
   Description    : Gibt das automatich erkannte Kommutierungsmuster als String zurück
   Parameter      :
   Return-Value   :
******************************************************************************/

void BLDC_pu8Automatic_Hall_Detection_Hex(TUINT8* pHall_Detection)
{
	TUINT8 au8arr[7];

	memcpy(au8arr, bldc_au8LookUpTable_Automatic_Hall_Detection, 7);
	bldc_Invert_Index_and_Value(au8arr);

	memcpy((char*)pHall_Detection, (char*)&au8arr[1], 6); // because [0] not in use
}

/******************************************************************************
   Description    :  Index und Value eines Array werden vertauscht
   Parameter      :
   Return-Value   :
******************************************************************************/

void bldc_Invert_Index_and_Value (TUINT8* pu8Ptr)
{
  TUINT8 i, j;
  TUINT8 au8arr[7];

  memcpy(au8arr,pu8Ptr,7);

  for (i = 1; i < 7; i++)
  {
    for (j = 1; j < 7; j++)
    {
	  if (au8arr[i] == j)
	  {
		pu8Ptr[j] = i;
	    break;
	  }
	}
  }
}


/******************************************************************************
   Description    : Motor mit Hall oder Sensorlos
   Parameter      :
   Return-Value   :
******************************************************************************/

void BLDC_Set_Mode(TUINT8 u8Mode)
{
	bldc_Mode = u8Mode;

	if ((u8Mode == BLDC_MODE_HALL) || (u8Mode == BLDC_MODE_MANUAL_KOMMUTATION))
	{
		bldc_Configure_Interrupts(LISTEN_TO_PHASE_ABC_RISING_FALLING);

		BLDC_Manual_Commutation();
	}

	if (u8Mode == BLDC_MODE_SENSORLESS)
	{

	}

	if (u8Mode == BLDC_MODE_MOSFET_TEST)
	{

	}
}

/******************************************************************************
   Description    : Mosfets einzeln durchschalten
                    [0][1][2][3][4][5][6]
                    [0] = not used
                    [1] = 1H
                    [2] = 1L
                    [3] = 2H
                    [4] = 2L
                    [5] = 3H
                    [6] = 3L
   Parameter      :
   Return-Value   :
******************************************************************************/

void BLDC_Test_Mosfets(TUINT8 *pu8Mosfets)
{
	#define CH_1H_PIN	GPIO_Pin_8
	#define CH_1H_PORT	GPIOA

	#define CH_1L_PIN	GPIO_Pin_13
	#define CH_1L_PORT	GPIOB

	#define CH_2H_PIN	GPIO_Pin_9
	#define CH_2H_PORT	GPIOA

	#define CH_2L_PIN	GPIO_Pin_14
	#define CH_2L_PORT	GPIOB

	#define CH_3H_PIN	GPIO_Pin_10
	#define CH_3H_PORT	GPIOA

	#define CH_3L_PIN	GPIO_Pin_15
	#define CH_3L_PORT	GPIOB


	static TUINT8 ActiveOnce = 1;

	if (ActiveOnce)
	{
		ActiveOnce = 0;


		GPIO_InitTypeDef GPIO_InitStruct;

	    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	    GPIO_Init(GPIOA, &GPIO_InitStruct);

	    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	    GPIO_Init(GPIOB, &GPIO_InitStruct);
	}

	// 1H
	if (pu8Mosfets[BLDC_TEST_MOSFETS_1H]) GPIO_WriteBit(CH_1H_PORT, CH_1H_PIN, ENABLE);
	else GPIO_WriteBit(CH_1H_PORT, CH_1H_PIN, DISABLE);

	// 1L
	if (pu8Mosfets[BLDC_TEST_MOSFETS_1L]) GPIO_WriteBit(CH_1L_PORT, CH_1L_PIN, ENABLE);
	else GPIO_WriteBit(CH_1L_PORT, CH_1L_PIN, DISABLE);

	// 2H
	if (pu8Mosfets[BLDC_TEST_MOSFETS_2H]) GPIO_WriteBit(CH_2H_PORT, CH_2H_PIN, ENABLE);
	else GPIO_WriteBit(CH_2H_PORT, CH_2H_PIN, DISABLE);

	// 2L
	if (pu8Mosfets[BLDC_TEST_MOSFETS_2L]) GPIO_WriteBit(CH_2L_PORT, CH_2L_PIN, ENABLE);
	else GPIO_WriteBit(CH_2L_PORT, CH_2L_PIN, DISABLE);

	// 3H
	if (pu8Mosfets[BLDC_TEST_MOSFETS_3H]) GPIO_WriteBit(CH_3H_PORT, CH_3H_PIN, ENABLE);
	else GPIO_WriteBit(CH_3H_PORT, CH_3H_PIN, DISABLE);

	// 3L
	if (pu8Mosfets[BLDC_TEST_MOSFETS_3L]) GPIO_WriteBit(CH_3L_PORT, CH_3L_PIN, ENABLE);
	else GPIO_WriteBit(CH_3L_PORT, CH_3L_PIN, DISABLE);

}



/******************************************************************************

   Changes                  
   
[06.03.15] 
  
   
******************************************************************************/



