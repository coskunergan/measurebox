/**
  ******************************************************************************
  * @file    GL865.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    14-Aralik-2012
  * @brief   GL865 haberlesme fonksiyonlari
  *
	******************************************************************************
	*@endverbatim
	*****************************************************************************/
 
#include "GL865.h"
#include "extern_reg.c"

#define CommandSize   210
#define gprs 1
#define card 0

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
uint8_t Gsm_Rx_Wait(char * Quest_Buff, uint32_t time)
{
	
	return 0;
}
/****************************************************************************/
/****************************************************************************/
uint8_t CommandGsm(char * data, char * Cevap_Buffer, uint32_t time)
{


		return 0;
}	
/****************************************************************************/
uint8_t Apn_AddressPut(uint32_t time)
{

	

		return 0;
}	
/****************************************************************************/
uint8_t FTP_Login(uint32_t time)
{
	 uint8_t quest=0;
	
		while(++quest)
		{
			if(quest>10)return 1;	
			printf("AT#FTPOPEN=\"%s\",\"%s\",\"%s\",0\r",Dom,User,Pass);
			if(!Gsm_Rx_Wait(OK,time))break;				
		}	
		return 0;
}	
/****************************************************************************/
uint8_t FTP_Close(uint32_t time)
{
	 uint8_t quest=0;
	
		while(++quest)
		{
			if(quest>10)return 1;	
			printf(ATFTPCLOSE);
			if(!Gsm_Rx_Wait(OK,time))break;				
		}	
		return 0;
}	
/****************************************************************************/
uint8_t IP_Get(uint32_t time)
{
	 uint8_t quest=0;
	
		while(++quest)
		{
			if(quest>6)return 1;	
			printf(IP_GET);
			if(!Gsm_Rx_Wait(OK,time))break;				
		}	
		return 0;
}	

/****************************************************************************/
void Gsm_Reset(void)
{
		Pin_Low(Gsm_Rst);
		DelayMs(100);
		Pin_High(Gsm_Rst);
}	
/****************************************************************************/
uint8_t Gsm_Pwr_On(void)
{	
		uint8_t t=50; // timeout = 5 sn

		Pin_Input_PD(Gsm_Enb); // pin input yap1l1r
		DelayS(2);             // 2x470uf kondansetörler bekleniyor
		Pin_Output_OD(Gsm_Enb);   // pin out yap1l1yor
		Pin_Low(Gsm_Enb);      // enerji tamamen veriliyor
		DelayS(2);
		while(!Pin_Get(Led_PwrMon))
		{
			DelayMs(100);		
			if(!t)return 1; else t--;
		}

		Gsm_Reset();
		DelayS(1);
		
		return 0;	
}	
/****************************************************************************/
void Gsm_Pwr_Off(void)
{	
		Pin_High(Gsm_Enb);  // gsm enerjisi kesilir	
	  DelayS(2);
}	
/****************************************************************************/
uint8_t Gsm_Pwr_Reset(void)
{
	uint8_t t=50; // timeout = 5 sn
	
		Gsm_Reset();
		Pin_High(Gsm_Enb);
		DelayS(3);
		Pin_Low(Gsm_Enb);
		DelayS(1);
		while(!Pin_Get(Led_PwrMon))
		{
			DelayMs(100);		
			if(!t)return 1; else t--;
		}	
		return 0;
}	

/****************************************************************************/
uint8_t Get_FtpLogFile_SizeOf(uint32_t time) // LOG FILE DOSYA BOYUTU OKUNUYOR
{
	 uint8_t quest=0,i;
	 
		while(++quest)
		{
			if(quest>3)return 1;	
//			printf("AT#FTPFSIZE=\"%s%d-%s%s\"\r",Log_File_Addr,Baylan_No,Serial_Number_Str,Log_File_Extension);
			if(!Gsm_Rx_Wait(FTPFSIZE,time))break;				
		}	
		
		for(i=0;i<11;i++){
//		SizeOf_FileStr[i]=BuffRx[CountRx++];
//		if(SizeOf_FileStr[i]=='\r')SizeOf_FileStr[i]='\0';
		}
	   
//		Str2Int(SizeOf_FileStr,(int32_t *)&SizeOf_File);
		return 0;
}	
/****************************************************************************/
void Real_Time_Update(void)
{

}	
/*##########################################################################*/
/*#########################!!!BOOTLOADER UPDATE!!!##########################*/  
/*##########################################################################*/
void Check_Ftp_Firmware(void)
{
	
		
}	
/*##########################################################################*/
/*###########################!!!!!!!!!!!!!!!!!##############################*/
/*##########################################################################*/
/****************************************************************************/
uint32_t Get_Str2Int(uint8_t addr)
{
	uint8_t i,buffx[10];
	uint32_t result;
	
	for(i=0;i<9;i++){
			buffx[i]=BuffRx[addr++];
			if((buffx[i]<0x30)||(buffx[i]>0x39))break;
	}
			buffx[i]='\0';
	
			Str2Int(buffx,(int32_t *)&result);
	
	return result;
}	
/****************************************************************************/
void Command_Work(uint8_t common)
{

	
}	
/****************************************************************************/
uint8_t Get_CommandToFile(void)  // LOG FILE da KOMUT BAKILIYOR
{
	
		return 0;
}	
/****************************************************************************/
uint8_t Write_LogFile(void)
{
	
	  return 0;
			
}	
/****************************************************************************/
uint8_t Connect_FTPFile(void)
{
		if(!Get_FtpLogFile_SizeOf(4000))
//				if(SizeOf_File)	
						if(Get_CommandToFile())return 1;	
//////////////////////////////////////////		
		IWDG_ReloadCounter();
//////////////////////////////////////////	
		if(Write_LogFile())return 1;

		return 0;
	
}
/****************************************************************************/
uint8_t Connect_FTP(void)
{
//////////////////////////////////////////		
		IWDG_ReloadCounter();
//////////////////////////////////////////


		return 0;
	
}	
/****************************************************************************/

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
