
/******************************************************************************

   File                :     ser1.h
   Version             :     11
   
   Version Temp-File   :     2
   
******************************************************************************/

#ifndef __SER3_H
#define __SER3_H

/******************************************************************************
   Include-Files
******************************************************************************/   

/******************************************************************************
   Global Constants
******************************************************************************/   

#define SER3_SNDBUF_LEN	256
#define SER3_RECBUF_LEN	256

/******************************************************************************
   Global Type-Definitions
******************************************************************************/   

/******************************************************************************
   Global Variables
******************************************************************************/   

TUINT8 SER3_u8Running; // Wird beim Anstoßen eines Sendevorgangs auf 1 gesetzt. Wird 0 wenn keine Zeichen mehr zum Senden in der Schlange bereitstehen
TUINT8 SER3_au8SndBuf[SER3_SNDBUF_LEN]; // Dient nur als Zwischenspeicher
TUINT8 SER3_au8RecBuf[SER3_RECBUF_LEN]; // Hier liegen die Daten nach einem gültigen Empfang
TUINT8 SER3_u8Number_Of_Data; // Anzahl der gültigen empfangenen Daten

/******************************************************************************
   Global Function-Prototypes
******************************************************************************/   

void SER3_Ini (void);
void SER3_Send_Protocol (TUINT8* pu8Data, TUINT8 u8Len); // Daten als Protokoll senden
void SER3_Send_String (TUINT8* pu8Data, TUINT8 u8Len); // Daten als roher String senden

TUINT8 SER3_u8Valid_Data(void); // Gibt 1 zurück wenn gültige Daten empfange wurden
void SER3_Protocol_Handling(TUINT8 u8Cycles); // Muss Zyklisch abgearbeitet werden -> State Machine

void SER3_SndBuf_Put (TUINT8 u8Data); // Schlange
TUINT8 SER3_u8SndBuf_Get (void); // Schlange
TUINT8 SER3_u8SndBuf_Empty (void); // Schlange

void SER3_RecBuf_Put (TUINT8 u8Data); // Schlange
TUINT8 SER3_u8RecBuf_Get (void); // Schlange
TUINT8 SER3_u8RecBuf_Empty (void); // Schlange

#endif


