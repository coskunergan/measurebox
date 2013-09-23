/**
  ******************************************************************************
  * @file    extern_reg.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    15 Subat-2013
  * @brief   Register lar1n extern yap1daki hali bulunan dosyad1r c dosyalara ekleyerek reg lere ulastirir.
  ******************************************************************************
  * @copy
  */
 
/* Includes ------------------------------------------------------------------*/

#include "main.h"

extern RTC_InitTypeDef RTC_InitStructure;
extern RTC_TimeTypeDef RTC_TimeStructure;	
extern RTC_DateTypeDef RTC_DateStructure;	
extern RTC_DateTypeDef RTC_DateStruct;	
extern RTC_TimeTypeDef RTC_TimeStruct;

///// ROM CONSTANTS //////////////////////////////////////////////////////////////

	
///// CONNECTIONS DATA ///////////////////////////////////////////////////////////

		extern uint8_t  Log_File_Extension[5];
		extern uint8_t  Log_File_Addr[33];
		extern uint8_t  Boot_File_Addr[48];
		extern uint8_t  Apn[17];
		extern uint8_t  Dom[129];
		extern uint8_t  User[17];
		extern uint8_t  Pass[17];
		
		extern uint32_t * ptr_ram;
		extern uint32_t  Error_Status;
		extern uint32_t  ram;
		
		extern uint8_t   BuffRx[256];
		extern uint8_t   CountRx;
		extern uint8_t   Command;

		extern uint8_t 	  Version_Byte;

		extern uint16_t 	Battery;
		
		extern bool 	Buzzer_Status;

///// FUNCTIONS REGISTERS ///////////////////////////////////////////////////////////////

		extern USART_TypeDef* Sel_Com;

		
		extern char Text_Message_Str[64];
		
		extern char buff[16];
		
		extern uint8_t Buff[72];
		extern uint8_t Buff_Imei[16];
		extern uint8_t Buff_Simno[20];
		
		extern bool Task;
		
		extern uint8_t 	RamRxCount;
		extern uint8_t 	RamTxCount;	
		extern uint8_t 	RamRxTxbuffer[9];	
		
				extern volatile uint32_t  TimingDelay;	
				
				extern FILE *lcd;
				extern FILE *gsm;
				extern FILE *debug;

/***********************************END OF FILE********************************/

		

