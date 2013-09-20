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
#ifndef __COMMON_H
#define __COMMON_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"


#define CMD_STRING_SIZE       128

/* Common routines */
#define IS_AF(c)  ((c >= 'A') && (c <= 'F'))
#define IS_af(c)  ((c >= 'a') && (c <= 'f'))
#define IS_09(c)  ((c >= '0') && (c <= '9'))
#define ISVALIDHEX(c)  IS_AF(c) || IS_af(c) || IS_09(c)
#define ISVALIDDEC(c)  IS_09(c)
#define CONVERTDEC(c)  (c - '0')

#define CONVERTHEX_alpha(c)  (IS_AF(c) ? (c - 'A'+10) : (c - 'a'+10))
#define CONVERTHEX(c)   (IS_09(c) ? (c - '0') : CONVERTHEX_alpha(c))

#define SerialPutString(x) Serial_PutString((uint8_t*)(x))




/* Private variables ---------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum);
void Int2Str(uint8_t* str, int32_t intnum);
void Usart_Init(COM_TypeDef COM ,uint32_t baud);
void Ram_Islem_Com_Init(void);

#endif  /* __H */

/*******************(C)COPYRIGHT 2012 STMicroelectronics *****END OF FILE******/
