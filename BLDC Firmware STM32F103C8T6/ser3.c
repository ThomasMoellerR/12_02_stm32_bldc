
/******************************************************************************

   File                :     ser3.c
   Version             :     12
   
   Version Temp-File   :     3
   
******************************************************************************/

/******************************************************************************
   Include-Files
******************************************************************************/   

#include "hea.h"

/******************************************************************************
   Local Constants
******************************************************************************/  

#define SER3_STX				0x65
#define SER3_ETX				0x0D

#define SER3_SNDBUF_QUELEN 		256
#define SER3_RECBUF_QUELEN 		256

/******************************************************************************
   Local Type-Definitions
******************************************************************************/   

enum tyen_Operation
{
  PROOF_STX,
  STORE_DLC,
  STORE_DATA,
  PROOF_CHK,
  PROOF_ETX
};

/******************************************************************************
   Local Variables
******************************************************************************/   

enum tyen_Operation ser3_Operation = PROOF_STX;

TUINT8 ser3_au8SndBuf[SER3_SNDBUF_QUELEN + 1];
TUINT16 ser3_u16SndBuf_Head = 0;
TUINT16 ser3_u16SndBuf_Tail = 0;

TUINT8 ser3_au8RecBuf[SER3_RECBUF_QUELEN + 1];
TUINT16 ser3_u16RecBuf_Head = 0;
TUINT16 ser3_u16RecBuf_Tail = 0;

TUINT8 ser3_u8Valid_Data;

/******************************************************************************
   Local Function-Prototypes
******************************************************************************/  

void ser3_Start_Sending (void);

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

void SER3_Ini (void)
{
  SER3_u8Running = 0;
  ser3_Operation = PROOF_STX;
  ser3_u8Valid_Data = 0;
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

void SER3_Protocol_Handling(TUINT8 u8Cycles)
{
  static TUINT8 u8Temp;
  static TUINT8 u8DLC;
  static TUINT8 u8Counter;
  static TUINT8 u8Chk;
  static TUINT8 u8i;
  int i;

  for (i = 0; i < u8Cycles; i++)
  {
    if ((!SER3_u8RecBuf_Empty()) && (!ser3_u8Valid_Data))
    {
      switch (ser3_Operation)
      {
        case PROOF_STX:
        {
          u8Temp = SER3_u8RecBuf_Get();

          if (u8Temp == SER3_STX) // Ist das Startzeichen korrekt?
          {
            ser3_Operation = STORE_DLC;
          }

          break;
        }

        case STORE_DLC:
        {
          u8DLC = SER3_u8RecBuf_Get(); // DLC speichern
          u8Counter = 0; // Wichtig, nicht vergessen, hat schon oft Sorgen bereitet
          ser3_Operation = STORE_DATA;

          break;
        }

        case STORE_DATA: // Daten speichern
        {
          if (u8Counter < u8DLC)
          {
            SER3_au8RecBuf[u8Counter] = SER3_u8RecBuf_Get();
            u8Counter++;
          }
          else
          {
      	    ser3_Operation = PROOF_CHK;
          }

          break;
        }

        case PROOF_CHK: // Checksumme berechnen und mit Checksumme von Protokoll vergleichen
        {
          u8Chk = 0;

          u8Chk ^= SER3_STX;
          u8Chk ^= u8DLC;

          for (u8i = 0; u8i < u8DLC; u8i++)
          {
            u8Chk ^=  SER3_au8RecBuf[u8i];
          }

          u8Temp = SER3_u8RecBuf_Get(); // Hole die Checksumme

          if (u8Temp == u8Chk) // Überprüfe die Checksumme
          {
            ser3_Operation = PROOF_ETX;
          }
          else
          {
            ser3_Operation = PROOF_STX; // Versuch verwerfen
          }

          break;
        }

        case PROOF_ETX:
        {
          u8Temp = SER3_u8RecBuf_Get();

         if (u8Temp == SER3_ETX) // Ist das Ende Zeichen korrekt?
          {
            ser3_u8Valid_Data = 1; // Jetzt sind die Daten gültig ansonsten nicht
            SER3_u8Number_Of_Data = u8DLC; // DLC einer globalen Variable übergeben
            ser3_Operation = PROOF_STX; // Von vorne anfangen
          }
          else
          {
            ser3_Operation = PROOF_STX; // Von vorne anfangen
          }

          break;
        }

        default: break;
      }
    }
  }
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

TUINT8 SER3_u8Valid_Data(void)
{
  TUINT8 u8Ret_Val;

  if (ser3_u8Valid_Data)
  {
    ser3_u8Valid_Data = 0;
    u8Ret_Val = 1;
  }
  else
  {
	u8Ret_Val = 0;
  }

  return u8Ret_Val;
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

void SER3_Send_Protocol (TUINT8* pu8Data, TUINT8 u8Len)
{
  TUINT8 u8Chk = 0;
  TUINT8 u8i;

  // SER3_STX
  SER3_SndBuf_Put (SER3_STX);

  // DLC
  SER3_SndBuf_Put (u8Len);

  // DATA
  for (u8i = 0; u8i < u8Len; u8i++)
  {
    SER3_SndBuf_Put (*(pu8Data + u8i));
  }

  // CHK
  u8Chk ^= SER3_STX;
  u8Chk ^= u8Len;

  for (u8i = 0; u8i < u8Len; u8i++)
  {
	  u8Chk ^=  (*(pu8Data + u8i));
  }

  SER3_SndBuf_Put (u8Chk);

  // SER3_ETX
  SER3_SndBuf_Put (SER3_ETX);


  // Sendevorgang anstoßen
  ser3_Start_Sending();
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

void SER3_Send_String (TUINT8* pu8Data, TUINT8 u8Len)
{
  TUINT16 u8i;

  // DATA
  for (u8i = 0; u8i < u8Len; u8i++)
  {
    SER3_SndBuf_Put (*(pu8Data + u8i));
  }

  // Sendevorgang anstoßen
  ser3_Start_Sending();
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

void ser3_Start_Sending (void)
{
  TUINT8 u8Temp;

  // Sendevorgang anstoßen, wenn gerade nichts gesendet wird
  if (!SER3_u8Running)
  {
	SER3_u8Running = 1;
    u8Temp = SER3_u8SndBuf_Get();

	// Benutzerdefiniert
    USART_SendData(USART3, u8Temp);
  }
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

void SER3_SndBuf_Put (TUINT8 u8Data)
{
  ser3_au8SndBuf[ser3_u16SndBuf_Tail++] = u8Data;
  if (ser3_u16SndBuf_Tail > SER3_SNDBUF_QUELEN) ser3_u16SndBuf_Tail = 0;
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

TUINT8 SER3_u8SndBuf_Get (void)
{
  TUINT8 u8Data = ser3_au8SndBuf[ser3_u16SndBuf_Head++];
  if (ser3_u16SndBuf_Head > SER3_SNDBUF_QUELEN) ser3_u16SndBuf_Head = 0;
  return u8Data;
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

TUINT8 SER3_u8SndBuf_Empty (void)
{
  return ser3_u16SndBuf_Head == ser3_u16SndBuf_Tail;
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

void SER3_RecBuf_Put (TUINT8 u8Data)
{
  ser3_au8RecBuf[ser3_u16RecBuf_Tail++] = u8Data;
  if (ser3_u16RecBuf_Tail > SER3_RECBUF_QUELEN) ser3_u16RecBuf_Tail = 0;
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

TUINT8 SER3_u8RecBuf_Get (void)
{
  TUINT8 u8Data = ser3_au8RecBuf[ser3_u16RecBuf_Head++];
  if (ser3_u16RecBuf_Head > SER3_RECBUF_QUELEN) ser3_u16RecBuf_Head = 0;
  return u8Data;
}

/******************************************************************************
   Description    :
   Parameter      :
   Return-Value   :
******************************************************************************/   

TUINT8 SER3_u8RecBuf_Empty (void)
{
  return ser3_u16RecBuf_Head == ser3_u16RecBuf_Tail;
}

/******************************************************************************

   Changes

   a)   In der Funktion SER3_Protocol_Handling:

        if (!SER3_u8RecBuf_Empty())    geändert zu if ((!SER3_u8RecBuf_Empty()) && (!ser3_u8Valid_Data))

   b) void SER3_Protocol_Handling(TUINT8 u8Cycles) cycles eingefügt


******************************************************************************/
