/******************************************************************************

 File                :     tmp.h
 Letze Ã„nderung	   :     06.03.15 10:34

 ******************************************************************************/

#ifndef __BLDC_H
#define __BLDC_H

/******************************************************************************
 Include-Files
 ******************************************************************************/

#include "tim2.h"

/******************************************************************************
 Global Constants
 ******************************************************************************/

#define BLDC_DEBUG_MOSFETS_PWM 1000 // Für einzelne Mosfet Tests
#define BLDC_MAX_PWM 3800 // 3800 = 95%
// Defines für Manuelle Kommuation
#define BLDC_MANUAL_COMMUTATION_DELAY	2000


// Mosfet Testing
//#define BLDC_DEBUG_ALL_HIGH_SIDE_MOSFETS_ENABLE
//#define BLDC_DEBUG_ALL_LOW_SIDE_MOSFETS_ENABLE
//#define BLDC_DEBUG_STATE_1 // kein strom
//#define BLDC_DEBUG_STATE_2 // fließst strom
//#define BLDC_DEBUG_STATE_3
//#define BLDC_DEBUG_STATE_4
//#define BLDC_DEBUG_STATE_5
//#define BLDC_DEBUG_STATE_6

// External Interrupts Testing
//#define BLDC_DEBUG_EXT_INT_PHASE_A
//#define BLDC_DEBUG_EXT_INT_PHASE_B
//#define BLDC_DEBUG_EXT_INT_PHASE_C
//#define BLDC_DEBUG_EXT_INT_PHASE_ABC


#define BLDC_PWM_HIGH_SIDE_MOSFETS

#define BLDC_MODE_HALL 0
#define BLDC_MODE_SENSORLESS 1
#define BLDC_MODE_MANUAL_KOMMUTATION 2

/******************************************************************************
 Global Type-Definitions
 ******************************************************************************/

/******************************************************************************
 Global Variables
 ******************************************************************************/


TUINT32 BLDC_u32HallInterrupt_Counter_A;
TUINT32 BLDC_u32HallInterrupt_Counter_B;
TUINT32 BLDC_u32HallInterrupt_Counter_C;
TUINT32 BLDC_u32Counter_With_Overflow_Respecting;
TUINT32 BLDC_au32Physical_Period[7];
TUINT32 BLDC_u32Latest_Period;

typedef enum {BLDC_HALL, BLDC_SENSORLESS, BLDC_MAN_KOMM} BLDC_enMode;



/******************************************************************************
 Global Function-Prototypes
 ******************************************************************************/

void BLDC_Ini(void);
void BLDC_Hall_Interrupt(void);
void BLDC_Set_PWM(TUINT16 u16PWM);
TUINT16 BLDC_u16Get_PWM(void);
void BLDC_Set_Direction(TUINT8 u8Direction);
void BLDC_Manual_Commutation(void);
TUINT8* BLDC_pu8Automatic_Hall_Detection(void);
void BLDC_pu8Automatic_Hall_Detection_Hex(TUINT8* pHall_Detection);
void BLDC_Set_Hall(TUINT8* pHall);
void BLDC_Set_Mode(TUINT8 u8MotorTyp);
TUINT8 BLDC_Get_Motortyp(void);


TUINT16 BLDC_u16GetPeriode(void);


/******************************************************************************

 Changes

 [06.03.15]


 ******************************************************************************/

#endif

