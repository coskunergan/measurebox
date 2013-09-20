/**
  ******************************************************************************
  * @file    rtc.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    27 Aralik-2012
  * @brief   rtc modlarinin kontrol edildigi dosya
  ******************************************************************************
  * @copy
  */
 
/* Includes ------------------------------------------------------------------*/

#include "rtc.h"
#include "int_eeprom.h"
#include "extern_reg.c"


RTC_InitTypeDef RTC_InitStructure;
RTC_TimeTypeDef RTC_TimeStructure;	

// Haftanýn gününü hesaplarken kullanýlan liste
const uint8_t  Week_Day_List[12]  = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4}; 

/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
// giris bilgisi : yil/ay/gun/saat:dakika/saniye olarak girilir
// örnek : 13/08/15 09:33:59
void Date_Set(const uint8_t * Buffer)
{
				uint8_t st;

        RTC_WaitForSynchro();

				Buffer+=2;	
				
				st =*Buffer;
	
				if(st=='n') 
				{
					Buffer--;
					st=*Buffer;
					if(st=='a')st=1;  // Jan
					else if(st=='u')st=6;  // Jun
					Buffer++;
				}
				else if(st=='b') st=2;  // Feb
				else if(st=='r') 
				{
					Buffer--;
					st=*Buffer;
					if(st=='a')st=3;  // Mar
					else if(st=='p')st=4;  // Apr	
					Buffer++;					
				}
				else if(st=='y') st=5;  // May
				else if(st=='l') st=7;  // Jul
				else if(st=='g') st=8;  // Aug
				else if(st=='p') st=9;  // Sep
				else if(st=='t') st=10; // Oct
				else if(st=='v') st=11; // Nov
				else if(st=='c') st=12; // Dec

				RTC_DateStruct.RTC_Month   = st;
				Buffer+=2;
				st =(*Buffer-48)*10;
				Buffer+=1;
				st+=*Buffer-48;
				RTC_DateStruct.RTC_Date   = st; 
	
				Buffer+=4;	
				st =(*Buffer-48)*10;
				Buffer+=1;
				st+=*Buffer-48; 
				RTC_DateStruct.RTC_Year  = st;
	

				RTC_DateStruct.RTC_WeekDay  = Week_Day_Search(RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date);
				RTC_SetDate(RTC_Format_BIN, &RTC_DateStruct);	

				Buffer+=1;
				st =(*Buffer-48)*10;
				Buffer+=1;
				st+=*Buffer-48;
				RTC_TimeStruct.RTC_Hours   = st; 
	
				Buffer+=2;	
				st =(*Buffer-48)*10;
				Buffer+=1;
				st+=*Buffer-48; 
				RTC_TimeStruct.RTC_Minutes  = st;
	
				Buffer+=2;		
				st =(*Buffer-48)*10;
				Buffer+=1;
				st+=*Buffer-48;
				RTC_TimeStruct.RTC_Seconds   = st;
	
				RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);
			
				
}
/****************************************************************************************************/
void Date_Load(uint32_t *  reg)
{
	
				RTC_TimeTypeDef RTC_TimeStructure;	
				RTC_DateTypeDef RTC_DateStructure;	
	
				RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
				RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);  
	
				*reg= RTC_TimeStructure.RTC_Minutes;
				*reg|= RTC_TimeStructure.RTC_Hours<<8;
				*reg|=(((RTC_DateStructure.RTC_Year&0x07)<<5)+RTC_DateStructure.RTC_Date)<<16;
				*reg|=(((RTC_DateStructure.RTC_Year&0xF8)<<1)+RTC_DateStructure.RTC_Month)<<24;		
	
}	
/****************************************************************************************************/
void Tarihi_Lcd_Yaz(void)
{
}
/****************************************************************************************************/
uint8_t Week_Day_Search(uint8_t Year, uint8_t Month, uint8_t Day)
{
      if(Month<3)
            Year-=1;
      return (Year + Year/4 - Year/100 + Year/400 + Week_Day_List[Month-1] + Day) % 7;
}
/****************************************************************************************************/
void RTC_Config(void)
{

  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_RTCAccessCmd(ENABLE);

  /* Reset RTC Domain */
  RCC_RTCResetCmd(ENABLE);
  RCC_RTCResetCmd(DISABLE);

  /* Enable the LSE OSC */
  RCC_LSEConfig(RCC_LSE_ON);

//	Lcd_Str (Alt1,"Waiting  !!! "); 
//	Lcd_Str (Alt2,"RTC NOT READY"); 
	
  /* Wait till LSE is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {
  }

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Configure the RTC data register and RTC prescaler */
  RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
  RTC_InitStructure.RTC_SynchPrediv  = 0xFF;
  RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);
	

    /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);
  
  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();

}
/****************************************************************************************************/
void Rtc_Alarm_Hours(void)
{
	uint8_t kont;

	RTC_AlarmTypeDef  RTC_AlarmStructure;
	
  RTC_AlarmCmd(RTC_Alarm_A, DISABLE);  
	(void)RTC->DR;	
 	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
	
	kont=RTC_TimeStructure.RTC_Hours;

	kont+=1;
	
	if(kont==24)kont=0;
	
  //RTC_AlarmStructure.RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = kont;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0;
  
	
	 /* Set the Alarm A */
  RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31;
  RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
  RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay; //| 	RTC_AlarmMask_Seconds;

	 /* Configure the RTC Alarm A register */
  RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure);
	
  /* Enable the alarm  A */
  RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
	
	RTC_ClearFlag(RTC_FLAG_ALRAF);

		
}	
/****************************************************************************************************/
// bugun uyand1ysa alarm1 en erken yarin için kurar
void Rtc_Alarm_Day(void)
{
	RTC_AlarmTypeDef  RTC_AlarmStructure;
	RTC_DateTypeDef RTC_DateStructure;	
	
	uint8_t Kont_H,Kont_M,Buff[5],WeekDay;

  RTC_AlarmCmd(RTC_Alarm_B, DISABLE);  
	
	Int_Eeprom_ReadStr(EE_CTIME_ADDR,Buff, EE_CTIME_LEN);
//	WeekDayConn=Int_Eeprom_ReadByte(EE_WDTIME_ADDR);
	
	Kont_H= (Buff[0]-48)*10;
	Kont_H+= Buff[1]-48;
	Kont_M= (Buff[2]-48)*10;
	Kont_M+= Buff[3]-48;	

	(void)RTC->DR;	
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
	WeekDay=RTC_DateStructure.RTC_WeekDay;	// simdiki gün

	 /* kay1tl1 günler */
//  if((WeekDayConn & 0x7F)== 0x0)WeekDayConn=1;// eger 0 ise haftada 1 ve haftan1n ilk günü baglanir.
 
 
 //------------------------------
 
	if(Kont_H >=RTC_TimeStructure.RTC_Hours) // saat _imdiki saatte n büyükse
	  if(Kont_M>RTC_TimeStructure.RTC_Minutes) // dk simdiki dk dan büyükse	
//				if(WeekDayConn & (1 << WeekDay-1))goto jump;  // alarm bugün için kurulabilirse gün asirtmayi atla ve direk kur
		
		/* Gün Asirtma */	
	while(1){
	
		if(WeekDay>6)WeekDay=0; 
		
//		if(WeekDayConn & (1 << WeekDay))break;

		WeekDay++;
	}		

	WeekDay++;
	


//  RTC_AlarmStructure.RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = Kont_H;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = Kont_M;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0;

	 /* Set the Alarm B */
  RTC_AlarmStructure.RTC_AlarmDateWeekDay = WeekDay;
  RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_WeekDay;
  RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_None; //| 	RTC_AlarmMask_Seconds;

	 /* Configure the RTC Alarm B register */
  RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_B, &RTC_AlarmStructure);
	
   /* Enable the alarm  B */
  RTC_AlarmCmd(RTC_Alarm_B, ENABLE);
	
	RTC_ClearFlag(RTC_FLAG_ALRBF);
	
}	
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
