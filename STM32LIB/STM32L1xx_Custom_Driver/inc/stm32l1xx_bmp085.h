/**
  ******************************************************************************
  * @file    stm32l1xx_bmp085.h
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    29-Eyl�l-2013
  * @brief   Bosch BMP-085 basin� Sens�r� k�t�panesi 
  *
	*  @verbatim
********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1xx_BMP085_H
#define __STM32L1xx_BMP085_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
	
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

	
uint8_t BMP085_Oku(int16_t *isi,int32_t *basinc);

#ifdef __cplusplus
}
#endif

#endif /*__STM32L1xx_bmp085_H */

/**
  * @}
  */ 

/**
  * @}
  */

/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/
