/**
  ******************************************************************************
  * @file    Header File 
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    14-AraLik-2012
  * @brief   Bu Bir Hedeader dosyadir fonksiyonlari main'e baglar.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PWR_MOD_H
#define __PWR_MOD_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define Swd_On  1
#define Swd_Off  0


/* Private variables ---------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Pwr_Init(uint8_t swd);
void Stop_Mod_Init(void);
void Stop(void);
void Vcc_Read(void);
uint32_t GetLSIFrequency(void);
#endif  /* __H */

/*******************(C)COPYRIGHT 2012 STMicroelectronics *****END OF FILE******/
