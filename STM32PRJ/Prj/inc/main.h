/*
  ******************************************************************************
  * @file    /inc/main.h 
  * @author  Coskun ERGAN
  * @date    26-Kasim-2012
  * @brief    GPRS Sulama sayaci Header  
  ******************************************************************************
  * @attention
  * 
  ****************************************************************************** 
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H


/* Includes ------------------------------------------------------------------*/
#include <stm32l1xx.h>
#include <stdio.h>		
#include <rtl.h>
#include <stdlib.h>         
#include "string.h"
#include "stm32l1xx_it.h"   // kesme fonksiyonlari
#include "stm32l1xx_conf.h"  //  standart gpio,pwr,comp,tim,adc,dac,flash vs. kütüpaneler
#include "stm32l1xx_Board_121016KGS00.h"  // board pin port tanimlamalari
#include "stm32l1xx_hd44780.h"  // pin isim uyarlamalari 
#include "stm32l1xx_define.h"  // pin isim uyarlamalari 

#include "rtc.h"
#include "GL865.h"
#include "common.h"
#include "pwr_mod.h"
#include "int_eeprom.h"
#include "boot.h"
#include "flash_if.h"

#define Version 	"Versiyon V1.0"
#define VersionByte 10

#define Vana_Kapali  0 // kullan1lmaz ak311 e özel ayn1 kütüpaneyi kulland1klar1 için eklendi
#define Cezalar  0 // kullan1lmaz ak311 e özel
#define Uyarilar  0 // kullan1lmaz ak311 e özel

/* Exported types ------------------------------------------------------------*/
#define bool  _Bool
#define FALSE (0)
#define TRUE (!(FALSE))
#define enableInterrupts()   __set_PRIMASK(0);
#define disableInterrupts()  __set_PRIMASK(1);
/* Exported constants --------------------------------------------------------*/
/* Includes macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);
void Bip(void);
void DelayMs(uint32_t nTime);
void DelayS(uint32_t nTime); 
void Vcc_Read(void);
void Pulse_Read(void);
void RTC_Config(void);
uint8_t Card_Working(void);
void Gprs_Working(void);
void Day_Working(void);
void Hours_Working(void);
void Second_Working(void);
void Language_Change(void);


#endif /* __MAIN_H */

/***********************************END OF FILE********************************/
