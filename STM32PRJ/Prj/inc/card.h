/**
  ******************************************************************************
  * @file    Header File 
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    27-AraLik-2012
  * @brief   Bu Bir Hedeader dosyadir fonksiyonlari main'e baglar.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CARD_H
#define __CARD_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define Sector_0 0x00
#define Sector_1 0x04
#define Sector_2 0x08
#define Sector_3 0x0C
#define Sector_4 0x10
#define Sector_5 0x14


/* Private variables ---------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
 uint8_t Sector_5_Write(void);
 uint8_t Command_Sector_Read(void);
 uint8_t Sector_0_Read(void);
 void Message_Show_Card(void);
	
#endif  /* __H */

/*******************(C)COPYRIGHT 2012 STMicroelectronics *****END OF FILE******/
