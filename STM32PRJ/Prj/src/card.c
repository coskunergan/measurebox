/**
  ******************************************************************************
  * @file    card.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    27 Aralik-2012
  * @brief   kart modlarinin kontrol edildigi dosya
  ******************************************************************************
  * @copy
  */
 
/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "extern_reg.c"


#define Factory_Card 			32
#define Authorization_Card 8
#define	New_User_Card  		 2
#define Card_Type_Len  		 3
#define Format_Card    	1000
#define Restart_Card   	1001

/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
void Card_Buffer_Parse(void)
{
	
	Date_Load(&Card_Read_Time);
	 

	Error_Status_Card=Error_Status;
	
	if(Card_Type_Read==Factory_Card)Cmd_OK_Card=0;
	
}	
/****************************************************************************************************/
uint8_t Sector_5_Write(void)
{

			Card_Buffer_Parse();
	
			Reset_Fm(); 
			Config_Auth_Fm(Sector_5,0x80);		
			CheckCalc_Sum (47,(unsigned char *)&Version_Byte,0);	
			WriteRead_Sektor(Sector_5,&Version_Byte,0x80,0);	  //write
	
	    return 0;
	
}	
/****************************************************************************************************/
uint8_t Command_Sector_Read(void)
{
			uint8_t i,Buff[48];
	
			CountRx=0;
			Cmd_OK_Card=0;

	
			Reset_Fm(); 
			Config_Auth_Fm(Sector_1,0x80);		
			if(WriteRead_Sektor(Sector_1,BuffRx,0x80,1))return 2; // checksum kontrolü yanl1ssa çik
	
			for(i=0;i<48;i++)
					if(BuffRx[i]=='[')break;
			
			if(i==47)return 1;  // ac isareti yok ise olumsuz çik
	
	//----------- komut var -------------------
			Cmd_OK_Card=1;
	// komut daha önce islenmismi bakilir
			Reset_Fm(); 
			Config_Auth_Fm(Sector_5,0x80);		
			if(WriteRead_Sektor(Sector_5,Buff,0x80,1))return 2;	 // checksum kontrolü yanl1ssa çik
			if(Buff[3]!=0x0)return 1; // komut daha önce islenmis olumsuz cik
	//------------------------------------------------	
			for(i=0;i<48;i++)
					if(BuffRx[i]==']')return 0;// kapal1 isaretini bulduysa olumlu ç1k
			
			
			Reset_Fm(); 
			Config_Auth_Fm(Sector_2,0x80);		
			if(WriteRead_Sektor(Sector_2,BuffRx+47,0x80,1))return 2;	// checksum kontrolü yanl1ssa çik
	
			for(i=0;i<=48;i++)
					if(BuffRx[i+47]==']')return 0;	// kapal1 isaretini bulduysa olumlu ç1k

	
			Reset_Fm(); 
			Config_Auth_Fm(Sector_3,0x80);		
			if(WriteRead_Sektor(Sector_3,BuffRx+94,0x80,1))return 2;	 // checksum kontrolü yanl1ssa çik
 
			
			for(i=0;i<=48;i++)
					if(BuffRx[i+94]==']')return 0;	// kapal1 isaretini bulduysa olumlu ç1k
			
			Reset_Fm(); 
			Config_Auth_Fm(Sector_4,0x80);		
			if(WriteRead_Sektor(Sector_4,BuffRx+141,0x80,1))return 2;	// checksum kontrolü yanl1ssa çik
	
			for(i=0;i<=48;i++)
				if(BuffRx[i+141]==']')return 0;	// kapal1 isaretini bulduysa olumlu ç1k
	
			return 1;
	
}	
/****************************************************************************************************/
uint8_t Sector_0_Read(void)
{

	
					if(!WriteRead_Sektor(Sector_0,(uint8_t *)&Serial_Number_Read,0x80,1)){
										
						
											if(Card_Type_Read==Format_Card){
													
													Int_Eeprom_WriteStr( EE_CHECK_ADDR,"  ", EE_CHECK_LEN);	
													NVIC_SystemReset(); // reset device
												
											}

											if(Card_Type_Read==Restart_Card){
													
													NVIC_SystemReset(); // reset device
												
											}											
											
											if(Card_Type_Read==Factory_Card){
												
												 // fabrika kart1ysa kontrol yapmadan komuta git
												Mcard_Factory_Card;
																	return TRUE;
												
											}	
								
								
											//if(Institute_Number_Read!=Institute_Number){Mcard_Undefined_Card; return FALSE; }		
											
											if(Card_Type_Read==Authorization_Card){
												
												 // yetki kart1ysa komuta git
												Mcard_Authorization_Card;
																	return TRUE;
												
											}	

											if(Meter_Number_Read!=Serial_Number){Mcard_Undefined_SN_Card; return FALSE; }							
												
											if(Serial_Number_Read!=Serial_Number_Card){

												 
																	/* yeni abone kart1m1 */
																	if(Card_Type_Read==New_User_Card){
																	
																	Serial_Number_Card=Serial_Number_Read;
																	Int_Eeprom_WriteWord( EE_SERIAL_ADDR	,Serial_Number_Card); 
												
																		
																	}else{
																		Mcard_Undefined_AN_Card;
																		return FALSE; 
																	}
											}		
					
				}else{Mcard_Read_Error; return FALSE;}
			
			
			return TRUE;

}	
/****************************************************************************************************/
void Message_Show_Card(void)
{
	  char buff[16];

		if(Message_Status_Card & 0x0001 ){
		Lcd_Str(Alt1,info1);	
		Lcd_Str(Alt2,info2);	
		DelayS(2);		
		}	
		
	
		if(Message_Status_Card & 0x04000000 ){   
		Lcd_Str (Alt1,"   HATALI     ");		
		Lcd_Str (Alt2,"   OKUMA!     ");			
		DelayS(2);	
		}				
		if(Message_Status_Card & 0x00040000 ){
		Lcd_Str(Alt1,"   TANIMSIZ   ");
		Lcd_Str(Alt2,"   SERI NO    ");
		DelayS(2);	
		}
		if(Message_Status_Card & 0x08000000 ){   
		Lcd_Str (Alt1,"FABRiKA KARTI");		
		Lcd_Str (Alt2,"   OKUNDU    ");			
		DelayS(2);	
		}	
		if(Message_Status_Card & 0x10000000 ){   
		Lcd_Str (Alt1," YETKi KARTI ");		
		Lcd_Str (Alt2,"   OKUNDU    ");			
		DelayS(2);	
		}			
		
		Lcd_Str(Alt2,&Command_Card[Language][0]);			
		if(Message_Status_Card & 0x0002 ){
		Lcd_Str(Alt1,&Close_Valve[Language][0]);		
		Valve_Command='C';
		DelayS(2);	
		}	
		if(Message_Status_Card & 0x0004 ){
		Lcd_Str(Alt1,&Open_Valve[Language][0]);	
		Valve_Command='C';			
		DelayS(2);		
		}	
		if(Message_Status_Card & 0x0008 ){
		Lcd_Str(Alt1,"INDEX ENTERED ");				
		DelayS(2);		
		}	
		if(Message_Status_Card & 0x0010 ){
		Lcd_Str(Alt1,"BUZZER ENABLE ");	
		DelayS(2);
		}	
		if(Message_Status_Card & 0x0020 ){   
		Lcd_Str(Alt1,"BUZZER DISABLE");				
		DelayS(2);	
		}	
		if(Message_Status_Card & 0x0040 ){   
		Lcd_Str(Alt1,"CONNTIME CHANG");				
		DelayS(2);	
		}			
		if(Message_Status_Card & 0x0080 ){   
	//	Lcd_Str(Alt1," CARD CONNECT  ");	
	//	Lcd_Str(Alt2,"    ERROR!     ");				
		DelayS(2);	
		}		
//////////////////////////////////////////		
		IWDG_ReloadCounter();
//////////////////////////////////////////	
		if(Message_Status_Card & 0x0100 ){   
		Lcd_Str(Alt1," CLEAR ERROR  ");				
		DelayS(2);	
		}				
		if(Message_Status_Card & 0x0200 ){   
		Lcd_Str(Alt1,"CONDAY CHANGE ");			
		DelayS(2);	
		}			
		if(Message_Status_Card & 0x0400 ){   
		Lcd_Str(Alt1,"BALANCE CHANG.");				
		DelayS(2);	
		}					
		if(Message_Status_Card & 0x0800 ){   
		Lcd_Str(Alt1," DEBT CHANGE  ");			
		DelayS(2);	
		}				
		if(Message_Status_Card & 0x2000 ){   
		Lcd_Str(Alt1,"CONNECT CHANG.");			
		DelayS(2);	
		}			
		if(Message_Status_Card & 0x4000 ){   
		Lcd_Str(Alt1,"SERIAL CHANGE ");		
		DelayS(2);	
		}	
		if(Message_Status_Card & 0x8000 ){   
		Lcd_Str(Alt1,"DIVIDER CHANG.");			
		DelayS(2);	
		}					
//////////////////////////////////////////		
		IWDG_ReloadCounter();
//////////////////////////////////////////			
		if(Message_Status_Card & 0x00010000 ){   
		Lcd_Str(Alt1," CLOSE CHANGE ");			
		DelayS(2);	
		}			
		if(Message_Status_Card & 0x00020000	 ){
		Lcd_Str(Alt1,"    NO CARD   ");
		Lcd_Str(Alt2,"              ");
		DelayS(2);	
		}					

		if(Message_Status_Card & 0x00080000 ){   
		Lcd_Str(Alt1,"INSTITU CHANG.");			
		DelayS(2);	
		}					
		if(Message_Status_Card & 0x00100000 ){   
		Lcd_Str(Alt1,"  APN CHANGE  ");			
		DelayS(2);	
		}			
		if(Message_Status_Card & 0x00200000 ){   
		Lcd_Str(Alt1,"  DOM CHANGE  ");			
		DelayS(2);	
		}						
		if(Message_Status_Card & 0x00400000 ){   
		Lcd_Str(Alt1," USER CHANGE  ");			
		DelayS(2);	
		}
		if(Message_Status_Card & 0x00800000 ){   
		Lcd_Str(Alt1," PASS CHANGE  ");			
		DelayS(2);	
		}				
		if(Message_Status_Card & 0x01000000 ){    
		Lcd_Str(Alt1," LANG. CHANGE ");			
		DelayS(2);	
		}
		if(Message_Status_Card & 0x20000000 ){    
		Lcd_Str(Alt1,"  TiME CHANGE ");			
		DelayS(2);	
		}
		if(Message_Status_Card & 0x40000000 ){    
		Lcd_Str(Alt1,"BAYLNNO CHANGE");		
		DelayS(2);	
		}		
		if(Message_Status_Card & 0x80000000 ){    
		Lcd_Str(Alt1,"   TANIMSIZ   ");
		Lcd_Str(Alt2,"    ABONE     ");
		DelayS(2);	
		}				
		if(Message_Status_Card & 0x02000000 ){   
		Lcd_Str (Alt1,&Card_Read[Language][0]);		
		Lcd_Str (Alt2,&Complete[Language][0]);			
		DelayS(2);	
		}					
		if(Message_Status_Card & 0x1000 ){    
		sprintf(buff,"%d",(uint32_t)Credit);
		Lcd_Center_Str(Alt1,buff);
		Lcd_Str(Alt2,&Credit_Load[Language][0]);
		DelayS(2);	
		}					
			
		Message_Status_Card=0;
}	
/****************************************************************************************************/
/****************************************************************************************************/
