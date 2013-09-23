/**
  ******************************************************************************
  * @file    boot.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    08 Mart 2013
  * @brief   boot modlarinin kontrol edildigi dosya
  ******************************************************************************
  * @copy
  */
 
/* Includes ------------------------------------------------------------------*/

#include "boot.h"
#include "extern_reg.c"
#include "flash_if.h"

#define Bank2_Baslangic_Adresi   (uint32_t)0x08030000
#define Bank1_Baslangic_Adresi   (uint32_t)0x08000000 

#define Bank2_Bitis_Adresi   0x0805FF00
#define Bank1_Bitis_Adresi   0x0802FFFF

/***********************************************************************/
uint8_t Cevap_Bekle(char * Cevap_Buffer, uint32_t zaman)
{
		uint8_t i,tekrar=3,cvp[64];
		
		TimingDelay=zaman/10;
	
	  SysTick->VAL=0;
	
	do{
				
	while(1){	
	
		    if(scanf("%s",cvp) != EOF)break;
		
				if(!TimingDelay)return 1;  // zaman hatasi, belirlenen zaman doldu.
		
					}
					
			i=0;
			while(Cevap_Buffer[i] != '\0' )i++;
										
			while(1){
						
						if( cvp[i] != Cevap_Buffer[i])break;
						if(!i) return 0; 
						i--;
						
							}
							
			}while(tekrar--);

			return 2;  // 3 Kez Yanlis Cvp Geldi.

}	
/***************************************************************************/

/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
void Bootloader(uint32_t Sizeof_Boot_File)
{
	
	uint8_t BuffRx[1024],j,kont;
	uint16_t PaketNo,i;
	uint32_t flashdestination,timeout,crc_calc,crc_file_name;
	uint8_t buffer_lcd[16];
	
//----------------- Ekran mesaj1 gösteriliyor -----------------------	
//			Lcd_Str (Alt1,"Bootloader    "); 
//			Lcd_Str (Alt2,"              "); 	
			Bip();
			DelayS(1);
		//  sprintf(Text_Message_Str,"Download Error..."); // buradan sonra takilirsa down yapamadi mesaji ver.
//-------------------- Buffer Rom siliniyor  ------------------------	

			PaketNo=0;        // paketler 0 dan baslayip istenecek
			// systick timer durduruluyor
			SysTick->CTRL  &= ~SysTick_CTRL_TICKINT_Msk;
			disableInterrupts();
			// flash kilit açiliyor
			FLASH_If_Init();
			// rom siliniyor
			while(FLASH_If_Erase(Bank2_Baslangic_Adresi,Bank2_Bitis_Adresi)); // silme islemi yapilamazsa birtek wdt ç1kar1r

			// Timer tekrar açiliyor					
			SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk; 
			enableInterrupts();

			flashdestination = Bank2_Baslangic_Adresi;			
			
			GPIO_SetBits(Lcd_BL_Port,Lcd_BL_Pin);			
			
			// dosya boyutu kb olarak döngüye belirtiliyor
			
			j=(Sizeof_Boot_File/1024)+1;
	
	while(j--){	 // paket alma döngüsü
				
				// 1024 byte çagriliyor
				printf("AT#FTPRECV=1024\r");
				Cevap_Bekle("#FTPRECV:",2000);
		
			  //-------------------- paket indiriliyor -----------------	
		
							while (1) // gereksiz komut bytelarinin alinip temizlendigi döngü 
							{ 
								timeout=400000;
								while ( USART_GetFlagStatus(STM_COM1, USART_FLAG_RXNE) == RESET)
									{
									if(!timeout)break;		 //hata
									timeout--;
									}
									if(STM_COM1->DR == '\n')break;		
							}
					
							for (i = 0; i < 1024; i++)   // Program verilerinin oldugu 1K paket byte alim döngüsü
							{
								// Son paket ise Timeout Yapilmiyacak Paket boyu 1K dan kisa olabilir
								if(j==0 & timeout==0)
								{							
									BuffRx[i] = 0x0; // dummy byte			
								}
								else
								{	
									timeout=100000;
									while ( USART_GetFlagStatus(STM_COM1, USART_FLAG_RXNE) == RESET)
									{
										timeout--;	
										if(!timeout){
										if(j==0)break;
										else goto cikis;//hata
										}		
									}
									BuffRx[i] = (uint8_t)STM_COM1->DR;
								}		
							}					
							// systick timer kapatiliyor
							SysTick->CTRL  &= ~SysTick_CTRL_TICKINT_Msk;
							// Flash a yaziliyor
							if (FLASH_If_Write(&flashdestination, (uint32_t*)BuffRx, (uint16_t)256)  != 0)
							{
								goto cikis;//hata
							}
							// Timer tekrar açiliyor					
							SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk; 
						
				
						PaketNo++;		
//						Lcd_Str(Alt1,"Download:     ");
						sprintf((char*)buffer_lcd,"%d Byte     ",PaketNo*1024);
//						Lcd_Str(Alt2,(uint8_t*)buffer_lcd); 

						////////////////////////
						IWDG_ReloadCounter();
						////////////////////////	
							
			}//while(j--) paket alim döngüsü
		
		////////////////////////
			IWDG_ReloadCounter();
		////////////////////////
			
//		Lcd_Str(Alt1," Yükleme       ");
//		Lcd_Str(Alt2," TAMAMLANDI... ");
		DelayS(1);

//		Lcd_Str(Alt1,"CRC Kontrolü   ");
//		Lcd_Str(Alt2,"Yapiliyor...   ");				
		DelayS(1);
		crc_calc=CalcCRC32((uint32_t *)Bank2_Baslangic_Adresi,Sizeof_Boot_File/4);	
		
		//Dosya isminden CRC bilgisi okunup çevrilir 	
			
		i=0;
		while(Boot_File_Addr[i] != 0x0)i++;
			
		crc_file_name=0;
			
		for(j=0;j<8;j++)	
			{
			
			kont=Boot_File_Addr[i-5];
				
			if(kont>=97)kont-=87;
			else if(kont>=65)kont-=55;
			else if(kont>=48)kont-=48;
			
			crc_file_name|=kont << j*4;				
				
			i--;
				
			}
		//-------------------------	
		if(crc_calc!=crc_file_name)
		{
//		Lcd_Str(Alt1,"CRC Hatali..! ");
		sprintf((char*)buffer_lcd,"0x%X      ",crc_calc);
//		Lcd_Str(Alt2,(uint8_t*)buffer_lcd); 
	//	sprintf(Text_Message_Str,"CRC Error..."); 
		DelayS(2);
		}	
		else
		{	 
//		Lcd_Str(Alt1,"CRC Ok..!     ");
		DelayS(1);
		Int_Eeprom_WriteStr(EE_CHECK_ADDR,"UP",EE_CHECK_LEN);
//		Lcd_Str(Alt1,"Program       ");
//		Lcd_Str(Alt2,"Güncelleniyor ");	
			
		SysTick->CTRL  &= ~SysTick_CTRL_TICKINT_Msk;
		disableInterrupts();
		FLASH_Unlock();
		// Program Ram üzerinde kosacak ve isi bitince resetle cikacak
		Bellek_Yukleyici();
		}
		
cikis:	// Mevcut programa geri dönülüyor	
		  
			FLASH_Lock();
			// Timer tekrar açiliyor					
			SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk; 
			enableInterrupts();
			GPIO_ResetBits(Lcd_BL_Port,Lcd_BL_Pin);
//			Lcd_Str(Alt1,"Boot Error!  ");
			DelayS(2);
		
 

		
}	
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/

/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
/* Make STM32F CRC compatible with windows/winzip/winrar 
Calculate CRC32 of DWORD data array. 
Input: 
u32 *dworddata -- the array point 
u32 dwordcount -- the data len in DWORD 
Output: 
u32 CRC32 -- the result 
**********************/ 
uint32_t CalcCRC32(uint32_t *dworddata,uint32_t dwordcount) 
{ 
		uint32_t ui32; 
	
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE); 
	
		CRC->CR=1; 
	
		__NOP();__NOP();__NOP();//delay for hardware ready 

		for(;dwordcount>0;dwordcount--) 
		{ 
			ui32=*dworddata; 
			dworddata++; 
			ui32=__RBIT(ui32);//reverse the bit order of input data 
			CRC->DR=ui32; 
		} 
		ui32=CRC->DR; 
		ui32=__RBIT(ui32); //reverse the bit order of output data 

		ui32^=0xffffffff;//xor with 0xffffffff 
		
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,DISABLE); 
		
		return ui32;//now the output is compatible with windows/winzip/winrar 
}
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
