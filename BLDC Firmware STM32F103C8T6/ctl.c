
/******************************************************************************

   File                :     ctl.c
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


// Protocol Positions
#define CMD						0
#define DIRECTION				1
#define PWM						2
#define DATA					1
#define DELAY					4

// Commands
#define CMD_INIT 					0x11
#define CMD_TEST_MOSFETS 			0x12
#define CMD_HALL 					0x13
#define CMD_SENSORLESS				0x14
#define CMD_MANUAL_COMMUTATION		0x15
#define CMD_SET_HALL_INFORMATION	0x16
#define CMD_STEUERUNG				0x17
#define CMD_REGELUNG				0x18
#define CMD_GET_STATE_REQUEST		0x19
#define CMD_GET_STATE_RESPONSE		0x20
#define SET_MOSFETS					0x21
#define SET_HALL_DETECTION			0x22
#define GET_HALL_INFO				0x23
#define SET_DIR_PWM_DELAY			0x24
#define SET_DIR_PWM					0x25
#define SET_RPS_INFO				0x26
#define GET_RPS_INFO				0x27

#define TEST_MOSFETS_1H     1
#define TEST_MOSFETS_1L     2
#define TEST_MOSFETS_2H     3
#define TEST_MOSFETS_2L     4
#define TEST_MOSFETS_3H     5
#define TEST_MOSFETS_3L     6

/******************************************************************************
   Local Type-Definitions
******************************************************************************/   

/******************************************************************************
   Local Variables
******************************************************************************/   

tyun_AnyData unAnyData;
TUINT8 au8Temp[256];

TUINT16 u16TimeoutCounter = 0;
TUINT16 ctl_u16Man_Kom_Time;
TUINT16 ctl_u16Man_Kom_Cnt = 0;
enum {INIT = 0, WAIT_FOR_APPLICATION_MODE = 1, MOSFET_TEST = 2, WAIT_FOR_HALL_INFORMATION = 3, MANUAL_COMMUTATION = 4, WAIT_FOR_OPERATION_MODE = 5, STEUERUNG = 6, REGELUNG = 7, COMMUNICATION_TIMEOUT = 8} ctl_State = INIT;
TUINT8 ctl_u8Recess_State;
TUINT32 ctl_u16Usek;
TUINT8 ctl_u8RPS_Info_Enabled = 0;
TUINT8 ctl_u8Hall_Detection_Enabled = 0;


/******************************************************************************
   Local Function-Prototypes
******************************************************************************/

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

void CTL_Ini (void)
{

}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

void CTL_Main (void)
{
  IWDG_ReloadCounter();



  if (!SER3_u8Valid_Data())
  {
    SER3_Protocol_Handling(100);
  }
  else
  {
	// Get State
	if (SER3_au8RecBuf[CMD] == CMD_GET_STATE_REQUEST)
	{
		au8Temp[CMD] = CMD_GET_STATE_RESPONSE;
		au8Temp[DATA] = ctl_State;
		SER3_Send_Protocol(au8Temp, 2);
	}

	// RPS Info Enable/Disable
	if (SER3_au8RecBuf[CMD] == SET_RPS_INFO)
	{
		ctl_u8RPS_Info_Enabled = au8Temp[DATA];
	}

	// Hall Detection Enable/Disable
	if (SER3_au8RecBuf[CMD] == SET_HALL_DETECTION)
	{
		BLDC_Set_Mode(BLDC_MODE_MANUAL_KOMMUTATION);

		ctl_u8Hall_Detection_Enabled = au8Temp[DATA];
	}


	switch (ctl_State)
	{
		case INIT:

			ctl_State = WAIT_FOR_APPLICATION_MODE;
			break;


			case WAIT_FOR_APPLICATION_MODE:

				switch(SER3_au8RecBuf[CMD])
				{
					case CMD_TEST_MOSFETS:		BLDC_Set_Mode(BLDC_MODE_MOSFET_TEST);
												ctl_State = MOSFET_TEST;
												break;

					case CMD_HALL :				BLDC_Set_Mode(BLDC_MODE_HALL);
												ctl_State = WAIT_FOR_HALL_INFORMATION;
												break;

					case CMD_SENSORLESS:		BLDC_Set_Mode(BLDC_MODE_SENSORLESS);
												ctl_State = WAIT_FOR_OPERATION_MODE;
												break;

					case CMD_MANUAL_COMMUTATION:ctl_State = MANUAL_COMMUTATION;
												break;

					default: break;
				}

				break;



		case WAIT_FOR_HALL_INFORMATION:

			if (SER3_au8RecBuf[CMD] == CMD_SET_HALL_INFORMATION)
			{
		    	BLDC_Set_Hall(&SER3_au8RecBuf[1]);

		    	ctl_State = WAIT_FOR_OPERATION_MODE;
			}
			break;



		case WAIT_FOR_OPERATION_MODE:


			if (SER3_au8RecBuf[CMD] == CMD_STEUERUNG)
			{
				ctl_State = STEUERUNG;
			}

			break;



	  case STEUERUNG:

	    if (SER3_au8RecBuf[CMD] == SET_DIR_PWM)
		{
	      // Immer wenn eine Nachricht für die PWM empfangen wurde, Timeout Conter zurücksetzen
	      u16TimeoutCounter = 0;

	      BLDC_Set_Direction(SER3_au8RecBuf[DIRECTION]);
		  memcpy((char*)unAnyData.au8Data, (char*)&SER3_au8RecBuf[PWM], 2);
	      BLDC_Set_PWM(unAnyData.u16Data);
		}


	    break;




	  case COMMUNICATION_TIMEOUT: // Wenn ich im Zustand Timeout bin und es kommt ein neuer Befehlt, dann neuen Modus einnehmen.

		  if ((SER3_au8RecBuf[CMD] == CMD_STEUERUNG) || (SER3_au8RecBuf[CMD] == SET_DIR_PWM))
		  {
			  u16TimeoutCounter = 0;
			  ctl_State = ctl_u8Recess_State; // Kehre zum Zustand vor dem Timeout zurück
		  }


		break;


	  case MANUAL_COMMUTATION: // Wenn ich im Zustand Timeout bin und es kommt ein neuer Befehlt, dann neuen Modus einnehmen.

		  if (SER3_au8RecBuf[CMD] == SET_DIR_PWM_DELAY)
		  {
			  // Direction
			  BLDC_Set_Direction(SER3_au8RecBuf[DIRECTION]);

		      // PWM
		      memcpy((char*)unAnyData.au8Data, (char*)&SER3_au8RecBuf[PWM], 2);
		      BLDC_Set_PWM(unAnyData.u16Data);

		      // Delay
		      memcpy((char*)unAnyData.au8Data, (char*)&SER3_au8RecBuf[DELAY], 2);
		      ctl_u16Man_Kom_Time = unAnyData.u16Data;
		  }

		break;


	  case MOSFET_TEST: // Wenn ich im Zustand Timeout bin und es kommt ein neuer Befehlt, dann neuen Modus einnehmen.

		  if (SER3_au8RecBuf[CMD] == SET_MOSFETS)
		  {

			  BLDC_Test_Mosfets(SER3_au8RecBuf);
		  }

		break;


	  default: break;
	}
  }


  // Immer ausführen
  switch (ctl_State)
  {
    case MANUAL_COMMUTATION:  if (ctl_u16Man_Kom_Cnt < ctl_u16Man_Kom_Time)
     	 	 	 	{
    				  ctl_u16Man_Kom_Cnt++;
     	 	 	 	}
    				else
    				{
    				  BLDC_Manual_Commutation();
    				  ctl_u16Man_Kom_Cnt = 0;
    				}

    				break;

    default: 		break;
  }


}



/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void CTL_1ms (void)
{
    switch (ctl_State)
    {
	  case STEUERUNG:

		  // Timeout
		  if (u16TimeoutCounter < 500) // 500ms max
		  {
		    u16TimeoutCounter++;
		  }
		  else
		  {
		    BLDC_Set_PWM(0);

		    ctl_u8Recess_State = ctl_State; // Merke den Zustand vor dem Timeout

		    ctl_State = COMMUNICATION_TIMEOUT;

		  }

	      break;




      default: break;
    }
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void CTL_10ms (void)
{

}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void CTL_100ms (void)
{
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/

void CTL_1s (void)
{
	if (ctl_u8RPS_Info_Enabled)
	{
		ctl_u16Usek = BLDC_u32HallInterrupt_Counter_A;
		BLDC_u32HallInterrupt_Counter_A = 0;
		ctl_u16Usek /= 6;

		unAnyData.u16Data = ctl_u16Usek;
		au8Temp[0] = GET_RPS_INFO;
		au8Temp[1] = unAnyData.au8Data[0];
		au8Temp[2] = unAnyData.au8Data[1];
		SER3_Send_Protocol(au8Temp, 3);
	}

	  switch (ctl_State)
	  {
	    case MANUAL_COMMUTATION:  	if (ctl_u8Hall_Detection_Enabled)
									{
										au8Temp[CMD] = GET_HALL_INFO;
										BLDC_pu8Automatic_Hall_Detection_Hex(&au8Temp[DATA]);

										// Test
										/*
										au8Temp[DATA] = 1;
										au8Temp[DATA+1] = 2;
										au8Temp[DATA+2] = 3;
										au8Temp[DATA+3] = 4;
										au8Temp[DATA+4] = 5;
										au8Temp[DATA+5] = 6;*/

										SER3_Send_Protocol(au8Temp, 7);
									}

		    				break;

	    default: 		break;
	  }


/*
  switch (ctl_State)
  {
    case MAN_KOMM:  	BLDC_pu8Automatic_Hall_Detection_Hex(&au8Temp[1]);
    					au8Temp[0] = HALL_VALUES;
    					SER3_Send_Protocol(au8Temp, 7);
	    				break;

    default: 		break;
  }
  */
}
