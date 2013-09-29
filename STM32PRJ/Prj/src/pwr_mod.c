/**
  ******************************************************************************
  * @file    pwr_mod.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    14 Aralik-2012
  * @brief   pwr modlarinin fonksiyonlarinin bulundugu dosya
  ******************************************************************************
  * @copy
  */
 
/* Includes ------------------------------------------------------------------*/

#include "main.h"


#define VREF 		1.224L
#define ADC_CONV 	4096

extern uint16_t Battery;

__IO uint32_t CaptureNumber = 0, PeriodValue = 0;

/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
void Pwr_Init(uint8_t swd)
{
	
  RCC_ClocksTypeDef RCC_Clocks;
	GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_GetClocksFreq(&RCC_Clocks);
		
		if (SysTick_Config(RCC_Clocks.HCLK_Frequency / 100))
		{
			for (;;) /* Capture error */
			{
			}
		}

		/* Portlar LP moda uygun konuma aliniyor */
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                        RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOE | RCC_AHBPeriph_GPIOH |
                        RCC_AHBPeriph_GPIOF | RCC_AHBPeriph_GPIOG, ENABLE);

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
		
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		GPIO_Init(GPIOE, &GPIO_InitStructure);
		GPIO_Init(GPIOH, &GPIO_InitStructure);
		GPIO_Init(GPIOF, &GPIO_InitStructure);
		GPIO_Init(GPIOG, &GPIO_InitStructure);  
if(!swd)GPIO_Init(GPIOA, &GPIO_InitStructure); 
 		GPIO_Init(GPIOB, &GPIO_InitStructure);   

		/* Disable GPIOs clock */
		RCC_AHBPeriphClockCmd(  RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOE | RCC_AHBPeriph_GPIOH |
                            RCC_AHBPeriph_GPIOF | RCC_AHBPeriph_GPIOG, DISABLE);
		/* Enable & SYSCFG */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG , ENABLE);	

		/* Enable Ultra low power mode */
		PWR_UltraLowPowerCmd(ENABLE);
		
}
/**************************************************************************************/
void Stop_Mod_Init(void)
{
  NVIC_InitTypeDef  NVIC_InitStructure;
  EXTI_InitTypeDef  EXTI_InitStructure;
		
	/* Kesme kurulumu yapiliyor */
	EXTI_DeInit();	
		
	/* Button A ve B kesme pini olarak gösteriliyor WKUP-1,2 */
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);
		
  /* EXTI configuration *******************************************************/
//  EXTI_ClearITPendingBit(EXTI_Line0);
//	EXTI_ClearITPendingBit(EXTI_Line13);
  EXTI_ClearITPendingBit(EXTI_Line20);
/*	
	EXTI_InitStructure.EXTI_Line =  EXTI_Line0 | EXTI_Line13;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line20;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
   /*  RTC kesmesine 1. öncelik tan1n1yor */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   
 
   /* Buton kesmelerine 2. öncelik tan1n1yor */
/*  NVIC_InitStructure.NVIC_IRQChannel =  EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
	
  NVIC_InitStructure.NVIC_IRQChannel =  EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 	
*/	
  /* RTC Wakeup Interrupt Generation: Clock Source: RTCDiv_16  */
  RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);
// 0x66 =50ms	
// 0xcc =100ms	
// 0x07FF =1sn	
// 0x1FFF =4sn
// 0xF000 =30sn 
// 0xFFFF =32sn
  RTC_SetWakeUpCounter(0x2FFF); // 4sn

  /* Enable the Wakeup Interrupt */
  RTC_ITConfig(RTC_IT_WUT, ENABLE); 
	
	/* Enable Wakeup Counter */
  RTC_WakeUpCmd(ENABLE);
	
}	
/**********************************************************************************/
void Stop(void)
{
		/* WU flag temizle   */
	  PWR_ClearFlag(PWR_FLAG_WU);  
	  /* STOP-Mod sadece Reset, WKUP-1 veya WKUP-2 Uyandiracak (RTC aktif) (~1.6uA) */
		PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);	   
}
/**************************************************************************************/
void Vcc_Read(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  uint8_t j;
  uint16_t res;
	
	disableInterrupts();

  /* Enable the HSI oscillator */
  RCC_HSICmd(ENABLE);
	
	/* Check that HSI oscillator is ready */
  while( RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
	
	/* Enable ADC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	/* de-initialize ADC */
  ADC_DeInit(ADC1);

  /* ADC Configuration */
  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel4 configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_192Cycles);
  ADC_DelaySelectionConfig(ADC1, ADC_DelayLength_Freeze);

  ADC_PowerDownCmd(ADC1, ADC_PowerDown_Idle_Delay, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
  
  /* Wait until ADC1 ON status */
  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
  {
  }
 
  ADC_TempSensorVrefintCmd(ENABLE);

  /* ADC1 regular channel 17 for VREF configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_17, 1, ADC_SampleTime_192Cycles);
  
  /* initialize result */
  res = 0;
  for(j=4; j>0; j--)
  {
  /* start ADC convertion by software */
    ADC_SoftwareStartConv(ADC1);

    /* wait until end-of-covertion */
    while( ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0 );
  /* read ADC convertion result */
    res += ADC_GetConversionValue(ADC1);
  }
	
  /* de-initialize ADC */
  ADC_TempSensorVrefintCmd(DISABLE);
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, DISABLE);
  /* Enable the HSI oscillator */
  RCC_HSICmd(DISABLE);
	
  res=res>>2;

	Battery = (VREF/res) * ADC_CONV * 100;   // (1.2V / Adc)x 4096 = Vdd
	
	enableInterrupts();
}
/*******************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
