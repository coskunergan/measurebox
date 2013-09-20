/**
  ******************************************************************************
  * @file    constants.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    27 Aralik-2012
  * @brief   kart modlarinin kontrol edildigi dosya
  ******************************************************************************
  * @copy
  */
 
/* Includes ------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"


				RTC_TimeTypeDef  RTC_TimeStruct;
				RTC_DateTypeDef  RTC_DateStruct;
				
///// ROM CONSTANTS //////////////////////////////////////////////////////////////

		
	
///// CONNECTIONS DATA //////////////////////////////////////////////////////////////	

		uint8_t  Log_File_Extension[5]  __attribute__ ((at(0x20000200))); 
		uint8_t  Log_File_Addr[33]  		__attribute__ ((at(0x20000205))); 
		uint8_t  Boot_File_Addr[48]			__attribute__ ((at(0x20000238))); 
		uint8_t  Apn[17]								__attribute__ ((at(0x20000280))); 
		uint8_t  Dom[129]								__attribute__ ((at(0x20000297))); 
		uint8_t  User[17]								__attribute__ ((at(0x200003C0))); 
		uint8_t  Pass[17]								__attribute__ ((at(0x200003D7))); 

		uint32_t * ptr_ram = (uint32_t *)0x20000200;
		uint32_t  Error_Status 		__attribute__ ((at(0x200067F8)));  
		uint32_t  ram			 			 	__attribute__ ((at(0x200067FC))); //0x6800
		
		uint8_t BuffRx[256] 			__attribute__ ((at(0x20000400)));
		uint8_t CountRx  					__attribute__ ((at(0x20000600)));
		uint8_t Command					  __attribute__ ((at(0x20000601)));

		
///// SECTOR X DATA ///////////////////////////////////////////////////////////////////////
		
//------------------  Sector_5 Data --------------------------
		uint8_t 	Version_Byte		__attribute__ ((at(0x20001104)));

		uint16_t 	Battery 		    __attribute__ ((at(0x20001108)));

		



///// FLAG REGISTERS ///////////////////////////////////////////////////////////////////

		bool 	Task													__attribute__ ((at(0x20001205)));	
		bool 	Gprs_Task											__attribute__ ((at(0x20001206)));	
		bool 	Buzzer_Status									__attribute__ ((at(0x2000120b)));	

	

///// TIME REGISTERS //////////////////////////////////////////////////////////////
		
		volatile uint32_t  TimingDelay;	
		
///// KEY REGISTERS ///////////////////////////////////////////////////////////////



///// FUNCTIONS REGISTERS ///////////////////////////////////////////////////////////////

 
		USART_TypeDef* Sel_Com;	
		
			
		uint8_t 	RamRxCount						__attribute__ ((at(0x200022EF)));	
		uint8_t 	RamTxCount						__attribute__ ((at(0x200022F0)));		
		uint8_t 	RamRxTxbuffer[9]			__attribute__ ((at(0x200022F9)));		


/***********************************END OF FILE********************************/
