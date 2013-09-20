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
#ifndef __INT_EEPROM_H
#define __INT_EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"


#define DATA_EEPROM_START_ADDR      0x08080000
#define DATA_EEPROM_END_ADDR        0x080803FF
//------------- Baglanti Adresleri ----------------
#define  EE_LOG_ADDR        0x08080000  // 32
#define  EE_BOOT_ADDR       0x08080020  // 32
#define  EE_PIN_ADDR			  0x08080040  // 4
#define  EE_APN_ADDR        0x08080044  // 16
#define  EE_DOM_ADDR        0x08080054  // 128
#define  EE_USER_ADDR       0x080800D4  // 16
#define  EE_PASS_ADDR       0x080800E4  // 16
#define  EE_CHECK_ADDR			0x080800F4  // 2

#define EE_LOG_LEN          32
#define EE_BOOT_LEN         32
#define EE_PIN_LEN 			    4
#define EE_APN_LEN          16
#define EE_DOM_LEN          128
#define EE_USER_LEN         16
#define EE_PASS_LEN         16
#define EE_CHECK_LEN 				2
//------------ Degisken Adresleri -----------------
#define  EE_CTIME_ADDR			0x080800F6  // 4
#define  EE_WDTIME_ADDR			0x080800FA  // 1
#define  EE_VALVE_ADDR			0x080800FB  // 1
#define  EE_INDEX_ADDR			0x080800FC  // 4
#define  EE_BUZZER_ADDR			0x08080100  // 1 
#define  EE_LANGUAGE_ADDR		0x08080101  // 2
#define  EE_SERIAL_ADDR	 	  0x08080103  // 4  
#define  EE_DIVIDER_ADDR	 	0x08080107  // 1   
#define  EE_NULL_ADDR  	 	  0x08080108  // 1 <<<  1 byte null 
#define  EE_BALANCE_ADDR  	0x08080109  // 4   
#define  EE_DEBT_ADDR  	  	0x0808010D  // 4   
#define  EE_CONNCOUNT_ADDR  0x08080112  // 4  
#define  EE_CLOSE_ADDR      0x08080116  // 4
#define  EE_INSTITU_ADDR    0x0808011A  // 4
#define  EE_ERROR_ADDR      0x0808011E  // 4
#define  EE_SERIAL_CARD_ADDR  0x08080123  // 4
#define  EE_CONNCOUNT_ERR_ADDR  0x08080127  // 4
#define  EE_BAYLAN_NO_ADDR  0x0808012B  // 4
//#define  EE__ADDR  0x0808012F  // 4
  
#define EE_CTIME_LEN 				4
#define EE_WDTIME_LEN	   		1   
#define EE_VALVE_LEN 				1
#define EE_INDEX_LEN 				4
#define EE_BUZZER_LEN 			1
#define EE_LANGUAGE_LEN     2
#define EE_SERIAL_LEN       4
#define EE_DEVIDER_LEN	 	  1
#define EE_NULL_LEN	 	      1
#define EE_BALANCE_LEN	 	  4
#define EE_DEPT_LEN	 	      4
#define EE_CONNCOUNT_LEN	  4
#define EE_CLOSE_LEN	      4
#define EE_INSTITUTE_LEN    4
#define EE_ERROR_LEN	 	    4
#define EE_SERIAL_CARD_LEN  4
#define EE_CONNCOUNT_ERR_LEN 4
#define EE_BAYLAN_NO_LEN  4

/* Private variables ---------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void Int_Eeprom_ReadStr(uint32_t Addr, uint8_t* buff_data, uint8_t len);
void Int_Eeprom_WriteStr(uint32_t Addr, uint8_t* buff_data, uint8_t len);
uint32_t Int_Eeprom_ReadWord(uint32_t address);
uint8_t Int_Eeprom_WriteWord(uint32_t address, uint32_t data);
uint8_t Int_Eeprom_ReadByte(uint32_t Addr) ;
uint8_t Int_Eeprom_WriteByte(uint32_t address, uint8_t data);
void Int_Eeprom_GprsDataCheck(void);
void Serial_Convert(void);

#endif  /* __H */

/*******************(C)COPYRIGHT 2012 STMicroelectronics *****END OF FILE******/
