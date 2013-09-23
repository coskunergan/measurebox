/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32l1xx_i2c_ee.h
* Author             : Coskun ERGAN
* Version            : V1.0.1
* Date               : 30/Kasim/212
* Description        : 24Cxx Eeprom Haberleþme Kütüpanesi
********************************************************************************
	I2Cx kadar kurulabilir.
	
	pin tanýmlamalari board kütüpanesinde yapýlmalýdýr.
	
	örnek:
	_________________________________________________________
			
#define sEE_I2C                          I2C2
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C2
   
#define sEE_I2C_SCL_PIN                  GPIO_Pin_10              
#define sEE_I2C_SCL_GPIO_PORT            GPIOB                    
#define sEE_I2C_SCL_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define sEE_I2C_SCL_SOURCE               GPIO_PinSource10
#define sEE_I2C_SCL_AF                   GPIO_AF_I2C2

#define sEE_I2C_SDA_PIN                  GPIO_Pin_11                 
#define sEE_I2C_SDA_GPIO_PORT            GPIOB                     
#define sEE_I2C_SDA_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define sEE_I2C_SDA_SOURCE               GPIO_PinSource11
#define sEE_I2C_SDA_AF                   GPIO_AF_I2C2

#define e2prom                 512				// eeprom boyutu
#define I2C_Speed              50000      // haberleþme hýzý
#define I2Cx_SLAVE_ADDRESS7    0xA0       // eeprom adresi			

*******************************************************************************/

#ifndef __I2C_EE_H
#define __I2C_EE_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported functions ------------------------------------------------------- */

 void I2C_EE_Init(void);
 char I2C_EE_PageWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t NumByteToWrite);
 char I2C_EE_BufferWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
 char I2C_EE_BufferRead(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead);
 char I2C_EE_WaitEepromStandbyState(void);

#endif /* __I2C_EE_H */

/************************END OF FILE************************/
