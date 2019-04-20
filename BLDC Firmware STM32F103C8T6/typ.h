
/******************************************************************************

   File                :     typ.h
   Version             :     2
   
   Version Temp-File   :     3
   
******************************************************************************/

#ifndef __TYP_H
#define __TYP_H

/******************************************************************************
   Include-Files
******************************************************************************/   

//#include "tmp.h" 

/******************************************************************************
   Global Constants
******************************************************************************/   

#define TYP_U8	0
#define TYP_S8	1
#define TYP_U16	2
#define TYP_S16	3
#define TYP_U32	4
#define TYP_S32	5
#define TYP_STRING	6
#define TYP_DOUBLE	7
#define TYP_FLOAT	8

/******************************************************************************
   Global Type-Definitions
   
******************************************************************************/   

typedef unsigned char	TUINT8;
typedef unsigned char	TINT8;
typedef unsigned short	TUINT16;
typedef	short			TINT16;
typedef unsigned int	TUINT32;
typedef int				TINT32;

/******************************************************************************
   Global Variables
******************************************************************************/  

typedef union
{
  TUINT8	u8Data;
  TINT8		s8Data;
  TUINT16   u16Data;
  TINT16	s16Data;
  TUINT32	u32Data;
  TINT32	s32Data;
  TUINT8	au8Data[8];
  double	dDouble;
  float		fFloat;
  int		iInteger;
} tyun_AnyData; 

/******************************************************************************
   Global Function-Prototypes
******************************************************************************/   


#endif



