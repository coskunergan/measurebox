/**
  ******************************************************************************
  * @file    /src/main.c
  * @author  Coskun ERGAN
  * @version V1.0
  * @date    21-september-2013
  * @brief   MeasureBox.. Sensor Reading System..
  ******************************************************************************
  * @copy
  */
 
/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "extern_reg.c"

  float  sht_isi;
	float  sht_nem;
	int16_t  bmp_isi;
	int32_t  bmp_basinc;
/****************************************************************************************************/
void Bip(void)
{
		Pin_Low(Buzzer);
		DelayMs(20);
		Pin_High(Buzzer);
}	
/****************************************************************************************************/
void Sensorleri_Oku(void)
{
	  Pin_High(Pulse_Enb);
		DelayMs(10);
	
	 	if(BMP085_Oku(&bmp_isi,&bmp_basinc))
		{
			bmp_isi=0;
			bmp_basinc=0;
		}
		
	  SHT11_Oku(&sht_isi,&sht_nem);
	
   	Pin_Low(Pulse_Enb);
		Pin_Low(Pulse_1);
		Pin_Low(Pulse_2);	
	  
}
/****************************************************************************************************/
void Gprs_Working(void)
{
	  Bip();

//////////////////////////////////////////		
		IWDG_ReloadCounter();
//////////////////////////////////////////		
}	

/****************************************************************************************************/
/********************************************** MAIN ************************************************/
/****************************************************************************************************/	
int main(void)
{ 
	
		if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET ) 
		{
				WDT_Reset_S;
		}
		RCC_ClearFlag();
//---------------- WDT Setup --------------	
		IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
		IWDG_SetPrescaler(IWDG_Prescaler_256);
		IWDG_SetReload(0xFFFF); // 30sn sonra yeniden yüklenmezse wdt reset atacak
		IWDG_ReloadCounter();
		IWDG_Enable();
//-------------- Basic Setup --------------	
		Pwr_Init(Swd_Off); 
//------------ Input Setup ----------------
		Pin_Output_OD(Pulse_1);
			Pin_Output(Pulse_2);
				Pin_Input(Pulse_3);
					Pin_Input(Led_PwrMon);
//------------ Output Setup ---------------
		Pin_Output(Pulse_Enb);
			Pin_Output_OD(Gsm_Rst);
				Pin_Output(Fm_Enb);
					Pin_Output_OD(Gsm_Enb);	
						Pin_Output(Buzzer); 
//------------ High Level -----------------
		Bip();
		Pin_High(Buzzer);
			Pin_High(Gsm_Enb);
				Pin_High(Fm_Enb);
					Pin_High(Gsm_Rst);
					  Pin_High(Pulse_Enb);
//-------------- RAM Cleans ---------------	
		for(ram=0x200;ram<0x67F4;ram+=4)
		{
				*(__IO uint32_t *) ptr_ram = 0x0; 
				ptr_ram+=1;
		}	
//----------- RCT & ALARM Setup ------------
		RTC_Config();
//	  Date_Set(__DATE__ __TIME__);	
	//	Rtc_Alarm_Hours();
		Stop_Mod_Init();
//-------------- COMs init -----------------
//		Ram_Islem_Com_Init();
//		Usart_Init(Gsm_Com,38400);
//-------------- Lcd init ------------------
		LCD_Pin_Init();
		fprintf(lcd,"MeasureBox SRS\n");
		fprintf(lcd,"Version:1.0");
		DelayMs(2000);
		LCD_Lp_Off();
//------------ Start Functions -------------
		Vcc_Read();
/****************************************************************************************************/
/******************************************** WHILE(1) **********************************************/
/****************************************************************************************************/
	 //fprintf(gsm,"AT\r");
	 //fprintf(dbg,"debug com tested");
while(1){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // Debug portu aktif et(ram islem)
		IWDG_ReloadCounter();
	
			Sensorleri_Oku();
	
		  LCD_GoTo(0,0);
			fprintf(lcd,"SHT-TEMP: %3.2f \n",sht_isi);
			fprintf(lcd,"HUMI: %3.2f \n",sht_nem);	
			DelayMs(1000);
	
		  LCD_GoTo(0,0);
			fprintf(lcd,"BMP-TEMP: %d.%d \n",bmp_isi/10,bmp_isi%10);
			fprintf(lcd,"PRESS:%d,%dhPa \n",bmp_basinc/10,bmp_basinc%10);	

	   	DelayMs(1000);
		  LCD_Lp_Off();
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, DISABLE);  // Debug portu kapat
//------------------- Stop Mod On --------------------
   Stop();	
//----------------------------------------------------
	}
}
/****************************************************************************************************/
/*******************************************  END MAIN **********************************************/
/****************************************************************************************************/
/****************************************************************************************************/
void DelayS(uint32_t nTime) 
{
			DelayMs(nTime*1000);
}
/*******************************************************************************/
void DelayMs(uint32_t nTime)
{

 TimingDelay = nTime / 10; 

  while(TimingDelay != 0);
  
}
/*******************************************************************************/
void TimingDelay_Decrement(void)  
{
		if (TimingDelay != 0x00)
		{ 
			TimingDelay--;
		} 
}
/*******************************************************************************/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
