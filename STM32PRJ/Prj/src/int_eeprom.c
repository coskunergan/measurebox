/**
  ******************************************************************************
  * @file    int_eeprom.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    24 Aralik-2012
  * @brief   dahili eeprom haberlesme kodlar1
  ******************************************************************************
  * @copy
  */
 
/* Includes ------------------------------------------------------------------*/

#include "int_eeprom.h"
#include "extern_reg.c"

uint32_t Address=0,NbrOfPage;
uint8_t  i,Check[2];

__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;


/***************************************************************************************/
void Int_Eeprom_ReadStr(uint32_t Addr, uint8_t* buff_data, uint8_t len)  // dizi okur
{
	uint32_t  Addr_End=Addr+len;
	
			disableInterrupts();
			DATA_EEPROM_Unlock();
	
	 while(Addr < Addr_End){
				/* eeprom okunuyor. */
				*buff_data=*(__IO uint8_t*)Addr;
				 buff_data++;
				 Addr= Addr + 1;
				}		
				
			DATA_EEPROM_Lock();
			enableInterrupts();
}	
/**************************************************************************************/
void Int_Eeprom_WriteStr(uint32_t Addr, uint8_t* buff_data, uint8_t len) // Dizi yazar
{
	    uint32_t  Addr_End=Addr+len;
			disableInterrupts();
			DATA_EEPROM_Unlock();
	
	//		while(FLASH_GetStatus()!=FLASH_COMPLETE); 
 	
				
				while(Addr < Addr_End )
					{
						
					/* Adrese veri yaziliyor */	
					FLASHStatus = DATA_EEPROM_ProgramByte(Addr,*buff_data);
						
						if(FLASHStatus == FLASH_COMPLETE)
						{
							Addr = Addr + 1;
							buff_data++;
						}
						else
						{
						FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR
															 | FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR);
						}
						
					}
					
				DATA_EEPROM_Lock();	
				enableInterrupts();
}	
/**************************************************************************************/
uint32_t Int_Eeprom_ReadWord(uint32_t address)     // 4 byte word okur 
{ 
		uint32_t tmp=0;
				disableInterrupts();
				DATA_EEPROM_Unlock();
 
//				while(FLASH_GetStatus()==FLASH_BUSY);
 	
				tmp=*(__IO uint32_t*)address;
				DATA_EEPROM_Lock();
				enableInterrupts();
	
		return tmp;
}
/**************************************************************************************/
uint8_t Int_Eeprom_WriteWord(uint32_t address, uint32_t data)  // 4 byte word yazar
{
			disableInterrupts();
			DATA_EEPROM_Unlock();

    // 	while(FLASH_GetStatus()!=FLASH_COMPLETE); 

			FLASHStatus = DATA_EEPROM_ProgramWord (address, data);

			DATA_EEPROM_Lock();
			enableInterrupts();
	
			if(FLASHStatus==FLASH_COMPLETE)return 0;
		  return 1;

}	
/***************************************************************************************/
uint8_t Int_Eeprom_ReadByte(uint32_t Addr)  // byte okur
{
	uint8_t kont;
				disableInterrupts();
				DATA_EEPROM_Unlock();
 
    //  	while(FLASH_GetStatus()!=FLASH_COMPLETE); 

				kont=*(__IO uint8_t*)Addr;
	
				DATA_EEPROM_Lock();
				enableInterrupts();
	return kont;
}	
/**************************************************************************************/
uint8_t Int_Eeprom_WriteByte(uint32_t address, uint8_t data) // 1 byte veri yazar
{
			disableInterrupts();
			DATA_EEPROM_Unlock();

    //  	while(FLASH_GetStatus()!=FLASH_COMPLETE); 

			FLASHStatus = DATA_EEPROM_ProgramByte (address, data);

			DATA_EEPROM_Lock();
			enableInterrupts();
	
			if(FLASHStatus==FLASH_COMPLETE)return 0;
		  return 1;

}	
/**************************************************************************************/
void Int_Eeprom_GprsDataCheck(void)
{

			/*Default ayarlarini eepromdakiyle degistirsin istiyorsan bu satiri aktif et */	
// 	   	Int_Eeprom_Write(EE_CHECK_ADDR,"  ",EE_CHECK_LEN/);

			Int_Eeprom_ReadStr( EE_CHECK_ADDR,Check, EE_CHECK_LEN);	

		  /* daha once eeprom adresine veri yaz1lm1s mi yoksa ilk mi */
			if(!((Check[0]=='O') && (Check[1]=='K')))
			{

			/* eepromda veri yok default ip,user,pass yaz1lacak */
			/* eeprom a Apn,ip,user,pass sirasiyla ve sonuna "OK" ekleyerek yükleniyor */	
			/* OK -> ibaresi eeproma veri yüklendigini ve  art1k bu verinin kullan1lacagini bildirir. */					
				
			if((Check[0]=='U') && (Check[1]=='P'))
			{	
			//	sprintf(Text_Message_Str,"Fimware Update Successfully..."); 
			}else{	

			}
			
//			Int_Eeprom_WriteWord( EE_INDEX_ADDR   ,Pulse_Counter[0]);
//			Int_Eeprom_WriteWord( EE_BALANCE_ADDR	,Balance); 		
//			Int_Eeprom_WriteWord( EE_DEBT_ADDR	,Debt); 

		
			//---------------- Ilk Ayarlar Mühürleniyor --------------
			Check[0]='O';
			Check[1]='K';				
		  Int_Eeprom_WriteStr( EE_CHECK_ADDR,Check, EE_CHECK_LEN);	
		  //--------------------------------------------------------
			
			}	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			
	


}
/*********************************************************************************/
/*********************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/


