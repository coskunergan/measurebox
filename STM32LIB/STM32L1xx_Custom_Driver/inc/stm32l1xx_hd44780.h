/**
  ******************************************************************************
  * @file    stm32l1xx_hd44780.h
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    22-Eylül-2013
  * @brief   4x20 lcd kütüpanesi 
  *
	*  @verbatim
********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1xx_HD44780_H
#define __STM32L1xx_HD44780_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
	
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


void delay_us(int us);
void LCD_SendByte(unsigned char cmd); //Sends a data byte to LCD (byte 'cmd').
void LCD_SendCmd (unsigned char cmd); //Sends a command byte to LCD (byte 'cmd').
void LCD_SendData(unsigned char data);
void LCD_SendText(char *text);
void LCD_GoTo (unsigned char line, unsigned char column);
void LCD_Clear (void);
void LCD_Lp_Off(void);
void LCD_Pin_Init(void);
void LCD_Init (void);


#ifdef __cplusplus
}
#endif

#endif /*__STM32L1xx_HD44780_H */

/**
  * @}
  */ 

/**
  * @}
  */

/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/
