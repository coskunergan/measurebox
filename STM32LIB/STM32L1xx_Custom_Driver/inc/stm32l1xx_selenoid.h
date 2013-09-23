/**
  ******************************************************************************
  * @file    stm32l1xx_selenoid.h
  * @author  Coskun ERGAN
  * @version V1.0.4
  * @date    03-Ekim-2012
  * @brief   Selenoid Valf Kontrol(SVK) k�t�panesi 
  *
	*  @verbatim
******************************************************************************
	*   BiLGi;
	*
	*						
	*
	******************************************************************************
	*   Notlar;
	*		
	*		- Zamanlama degisikliklerini stm32l1xx_selenoid.h" dosyasi icerisindeki define satirlayla yapabilirsiniz. 
	*		- ADC_IN0 ile ADC_IN25 dahil arasinda kalan t�m pinler VrefPin olarak Tanimlanabilir.
	*				�rnek; PB12 => ADC_IN18 => RI_IOSwitch_CH18
	*		- T�m IO pinler GND ref. enable Pin olarak tan1mlanabilir bu pinin g�revi LP uygulamalarda kacak akimlari �nlemektir.
	*		- T�m IO pinler Valf_Ac/Kapat pinleri olarak kullan1labilir.
	*
	******************************************************************************	
  *
	*  Valf_Hata(uint8_t) 
	*
	* 0 => Basarili;         	 Valf Basarili bir sekilde Acildi/Kapatildi
	* 1 => ZamanAsimi Hatasi;	 Voltaj y�kseltme islemi zaman sinirini asti.
	*												 		Sebepleri:
	*												  	- Pil voltaji d�s�k, pil arizali.
	*														- Sarj devresi arizali
	*														- Selenoid devresi kompanentleri arizali.
  *
	******************************************************************************
	*
	*
	******************************************************************************
	*@endverbatim
	*****************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1xx_SELENOID_H
#define __STM32L1xx_SELENOID_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "main.h"
	
/* Exported types ------------------------------------------------------------*/
		 
/* Exported constants --------------------------------------------------------*/
#define CH1     1
#define CH2     2
#define CH3     3
#define CH4     4 
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
 

void SVK_Init(void);
uint8_t SVK_Open(void);
uint8_t SVK_Close(void);



#ifdef __cplusplus
}
#endif

#endif /*__STM32L1xx_SELENOID_H */

/**
  * @}
  */ 

/**
  * @}
  */

/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/
