/**
  ******************************************************************************
  * @file    stm32l1xx_sht11.h
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    25-Eylül-2013
  * @brief   SHT11 Isi Nem Sensöru kütüpanesi 
  *
	*  @verbatim
********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1xx_SHT11_H
#define __STM32L1xx_SHT11_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
	
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


uint8_t SHT11_Oku(float *isi, float *nem); 
void SHT11_Reset(void);
uint8_t SHT11_Yaz_Config(uint8_t status);


#ifdef __cplusplus
}
#endif

#endif /*__STM32L1xx_sht11_H */

/**
  * @}
  */ 

/**
  * @}
  */

/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/
