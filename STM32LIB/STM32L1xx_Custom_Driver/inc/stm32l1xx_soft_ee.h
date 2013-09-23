/**
  ******************************************************************************
  * @file    stm32l1xx_soft_ee.h
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    13-Aralik-2012
  * @brief   Yazilimsal E2prom haberlesme kütüpanesi 
  *
	*  @verbatim
  ******************************************************************************
	*   Notlar;
	*
	*		
	*					
	******************************************************************************
	*
	*    Kullanmadan önce sirasiyla;
	*
	* 
  *
	******************************************************************************
	*@endverbatim
	*****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"


#ifndef __STM32L1XX_SOFT_EE_H 
#define __STM32L1XX_SOFT_EE_H 

#define Sda 	( SOFT_I2C_SDA_PORT -> IDR & SOFT_I2C_SDA_PIN )

#define SDA(x) (x) ? (SOFT_I2C_SDA_PORT->BSRRL =SOFT_I2C_SDA_PIN)  : (SOFT_I2C_SDA_PORT->BSRRH =SOFT_I2C_SDA_PIN);
#define SCL(x) (x) ? (SOFT_I2C_SCL_PORT->BSRRL =SOFT_I2C_SCL_PIN)  : (SOFT_I2C_SCL_PORT->BSRRH =SOFT_I2C_SCL_PIN);

#define TRIS_SDA(x) (x) ? (SOFT_I2C_SDA_PORT->MODER|=1<<(SOFT_I2C_SDA_SOURCE*2)) : (SOFT_I2C_SDA_PORT->MODER &=~(3<<(SOFT_I2C_SDA_SOURCE*2)));

#define in   0
#define out  1

#define	EE_TRUE	0
#define	EE_FALSE	1

#define	WRITE_CONTROL_BYTE	0xA0
#define	READ_CONTROL_BYTE	  0xA1



void Soft_Ee_Init_Pin(void);
void ee_delay(void);
void start(void);
uint8_t WaitAck(void);
void NoAck(void);
void Ack(void);
void Gonder8Bit(unsigned char x);
void Oku8Bit(unsigned char *x);
uint8_t I2c_Write_512( uint8_t addresH , uint8_t addresL,   uint16_t length , uint8_t* pBuffer);
uint8_t I2c_Read_512(uint8_t addres_h,uint8_t addres_l,uint8_t length,uint8_t * pBuffer);

#endif 
/****************************************************************************
**                            End 
*****************************************************************************/
