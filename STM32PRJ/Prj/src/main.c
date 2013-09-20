/**
  ******************************************************************************
  * @file    /src/main.c
  * @author  Coskun ERGAN
  * @version V1.0
  * @date    20-september-2013
  * @brief   MeasureBox.. Sensor Reading System..
  ******************************************************************************
  * @copy
  */
 
/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "extern_reg.c"

/****************************************************************************************************/
void Buzzer_On(void)
{
	if(Buzzer_Status)
	{	
		Pin_Low(Buzzer);
		DelayMs(20);
		Pin_High(Buzzer);
	}
}	
/****************************************************************************************************/
void Gprs_Working(void)
{
	  Buzzer_On();

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
//				Gprs_Task=TRUE; // Wdt reset olusturmus
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
		Pin_Input(Pulse_1);
			Pin_Input(Pulse_2);
				Pin_Input(Pulse_3);
					Pin_Input(Led_PwrMon);
						Pin_Input(ButonA);
							Pin_Input(ButonB);	
//------------ Output Setup ---------------
		Pin_Output(Pulse_Enb);
			Pin_Output_OD(Gsm_Rst);
				Pin_Output(Fm_Enb);
					Pin_Output(M_Sleep);
						Pin_Output(M_Next);
							Pin_Output(M_Back);
								Pin_Output_OD(Gsm_Enb);	
								  Pin_Output(Buzzer); 
//------------ High Level -----------------
		Pin_High(Buzzer);
			Pin_High(Gsm_Enb);
				Pin_High(Fm_Enb);
					Pin_High(Gsm_Rst);
//------------- Low Level -----------------				
				Pin_Low(M_Sleep);			
//-------------- RAM Cleans ---------------	
		for(ram=0x200;ram<0x67F4;ram+=4)
		{
				*(__IO uint32_t *) ptr_ram = 0x0; 
				ptr_ram+=1;
		}	
//----------- RCT & ALARM Setup ------------
		RTC_Config();
	  Date_Set(__DATE__ __TIME__);	
		Rtc_Alarm_Hours();
		Rtc_Alarm_Day();	
//------------------------------------------
		Ram_Islem_Com_Init();
/****************************************************************************************************/
/******************************************** WHILE(1) **********************************************/
/****************************************************************************************************/
    Stop_Mod_Init();
		Vcc_Read();
while(1){

if(Task){

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // ram islem usart2 rx aç

		Task=FALSE;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, DISABLE); // ram islem usart2 rx kapat	
		}	

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
