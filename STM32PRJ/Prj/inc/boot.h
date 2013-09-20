/**
  ******************************************************************************
  * @file    Header File 
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    08 Mart 2013
  * @brief   Bu Bir Hedeader dosyadir fonksiyonlari main'e baglar.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BOOT_H
#define __BOOT_H

#include "main.h"

void Bootloader(uint32_t Sizeof_Boot_File);
uint32_t FLASH_If_Erase(uint32_t StartSector,uint32_t StopSector);
uint32_t CalcCRC32(uint32_t *dworddata,uint32_t dwordcount) ;
__RAM_FUNC Bellek_Yukleyici(void);

#endif  /* __H */

/*******************(C)COPYRIGHT 2012 STMicroelectronics *****END OF FILE******/
