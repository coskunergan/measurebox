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
#ifndef __RTC_H
#define __RTC_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"



/* Private variables ---------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Date_Set(const uint8_t * Buffer);
void Date_Load(uint32_t * reg);
void Tarihi_Lcd_Yaz(void);
uint8_t Week_Day_Search(uint8_t Year, uint8_t Month, uint8_t Day);
void Rtc_Alarm_Hours(void);
void Rtc_Alarm_Day(void);
#endif  /* __H */

/*******************(C)COPYRIGHT 2012 STMicroelectronics *****END OF FILE******/
