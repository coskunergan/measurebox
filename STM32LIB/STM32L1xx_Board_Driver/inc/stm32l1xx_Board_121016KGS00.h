/**
*
  ******************************************************************************
  * @file    stm32l1xx_121016KGS00.h
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    23-Kasim-2012
  * @brief   #KARTLI GPRS SAYAC# Define Tanimlamalari
	* 
	*  @verbatim
	******************************************************************************
	*   Kart üzerindeki pin port donanim haberlesmeleri ile ilgili bilgiler;
	*
	*	
	******************************************************************************
	*@endverbatim
	*****************************************************************************/
#include <stm32l1xx.h>
#include "main.h"


#ifndef __STM32L1xx_BOARD_121016KGS00_H
#define __STM32L1xx_BOARD_121016KGS00_H

#ifdef __cplusplus
 extern "C" {
#endif 

	 
#define GPIO_HIGH(a,b) 		a->BSRRL = b
#define GPIO_LOW(a,b)		a->BSRRH = b
#define GPIO_TOGGLE(a,b) 	a->ODR ^= b 

////////////////////////////////////////////////////
//																								//
//   Led, Buzzer, Buton-A,B										 		//
//	 GSM_Enb, Pals, Pals_Vcc,											//
//	 Optik_Rx, Optik_Tx, COMx,										//
//												v.b. Basit Donanimlar		//
////////////////////////////////////////////////////

/*************** PIN TYPEDEF TANIMLAMALARI ***************/

	 
typedef enum 
{
  LED1       = 0,
	BUZZER     = 1,
	BUTONA     = 2,
  BUTONB     = 3,
	GSM_RST    = 4,
	GSM_ENB    = 5,
	FM_ENB     = 6,
	EEP_ENB    = 7,
	PULSE_ENB  = 8,
	M1         = 9,
	M2         = 10,
	M_SLEEP    = 11,
	PULSE_1    = 12,
	PULSE_2    = 13,	
	PULSE_3    = 14		
} Pin_TypeDef;


//////////////////////////
#define  	PINn	  15    //
//////////////////////////

/********  BASIT DONAIM PIN TANIMLAMALARI  *********/

/* PwrMon Led tanimlamasi */
#define  Led_Pwrmon_Pin      GPIO_Pin_6
#define  Led_Pwrmon_Port		 GPIOC
#define  Led_Pwrmon_Clk			 RCC_AHBPeriph_GPIOC
/* Buzzer Pin Tanimlamasi */
#define  Buzzer_Pin   			GPIO_Pin_11
#define  Buzzer_Port				GPIOA
#define  Buzzer_Clk					RCC_AHBPeriph_GPIOA
/*  Buton-A tanimlamasi (Exti-2) */
#define  ButonA_Pin   			GPIO_Pin_13
#define  ButonA_Port				GPIOC
#define  ButonA_Clk					RCC_AHBPeriph_GPIOC
/*  Buton-B tanimlamasi (Exti-1) */
#define  ButonB_Pin   			GPIO_Pin_0
#define  ButonB_Port				GPIOA
#define  ButonB_Clk					RCC_AHBPeriph_GPIOA
/*  Gsm Reset pin */
#define  Gsm_Rst_Pin   			GPIO_Pin_12
#define  Gsm_Rst_Port				GPIOC
#define  Gsm_Rst_Clk				RCC_AHBPeriph_GPIOC

/***********  ENABLE PIN TANIMLAMALARI   **********/

/*  GSM Enb Pin tanimlamasi */
#define  GSM_Enb_Pin   			GPIO_Pin_15
#define  GSM_Enb_Port				GPIOB
#define  GSM_Enb_Clk				RCC_AHBPeriph_GPIOB
/*  FM Enb Pin tanimlamasi */
#define  FM_Enb_Pin					GPIO_Pin_12
#define  FM_Enb_Port				GPIOA
#define  FM_Enb_Clk					RCC_AHBPeriph_GPIOA
/*  EEprom Enb Pin tanimlamasi */
#define  EEP_Enb_Pin				GPIO_Pin_12
#define  EEP_Enb_Port				GPIOB
#define  EEP_Enb_Clk				RCC_AHBPeriph_GPIOB
/*  Enb Puls PullUp Pin tanimlamasi */  
#define  Pulse_Enb_Pin				GPIO_Pin_8  
#define  Pulse_Enb_Port			GPIOA
#define  Pulse_Enb_Clk				RCC_AHBPeriph_GPIOA

/***********  Motor KONTROL TANIMLAMALARI ************/

/*  Motor Sürücü M1 Pin */
#define  DRV_M1_Pin   			GPIO_Pin_8  // geri
#define  DRV_M1_Port				GPIOB
#define  DRV_M1_Clk					RCC_AHBPeriph_GPIOB
/*  Motor Sürücü M2 Pin */
#define  DRV_M2_Pin   			GPIO_Pin_0   // ileri
#define  DRV_M2_Port				GPIOC
#define  DRV_M2_Clk					RCC_AHBPeriph_GPIOC
/*  Motor Sürücü Sleep Pin */
#define  DRV_Sleep_Pin   		GPIO_Pin_9
#define  DRV_Sleep_Port			GPIOB
#define  DRV_Sleep_Clk			RCC_AHBPeriph_GPIOB

/*  Pals Okula Pin - 1 */
#define  Pulse_1_Pin   			GPIO_Pin_9
#define  Pulse_1_Port				GPIOC
#define  Pulse_1_Clk		 		RCC_AHBPeriph_GPIOC

/*  Pals Okula Pin - 2 */
#define  Pulse_2_Pin   			GPIO_Pin_8
#define  Pulse_2_Port				GPIOC
#define  Pulse_2_Clk		 		RCC_AHBPeriph_GPIOC

/*  Pals Okula Pin - 3 */
#define  Pulse_3_Pin   			GPIO_Pin_7
#define  Pulse_3_Port				GPIOC
#define  Pulse_3_Clk		 		RCC_AHBPeriph_GPIOC

/*************** COM TANIMLAMALARI ***************/

typedef enum 
{
  COM1   = 0,   // GSM Com  					
  COM2   = 1,   // Optik Com					
	COM3   = 2    // Extra Com (debug)
} COM_TypeDef;  

#define  	COMn	  3	 
/*  GSM usart Com Pin tanimlamasi */
#define STM_COM1                        USART1
#define STM_COM1_CLK                    RCC_APB2Periph_USART1

#define STM_COM1_TX_PIN                 GPIO_Pin_9
#define STM_COM1_TX_GPIO_PORT           GPIOA
#define STM_COM1_TX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define STM_COM1_TX_SOURCE              GPIO_PinSource9
#define STM_COM1_TX_AF                  GPIO_AF_USART1

#define STM_COM1_RX_PIN                 GPIO_Pin_10
#define STM_COM1_RX_GPIO_PORT           GPIOA
#define STM_COM1_RX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define STM_COM1_RX_SOURCE              GPIO_PinSource10
#define STM_COM1_RX_AF                  GPIO_AF_USART1

#define STM_COM1_IRQn                   USART1_IRQn

/*  Optik Com Pin tanimlamasi */
#define STM_COM2                        USART2
#define STM_COM2_CLK                    RCC_APB1Periph_USART2

#define STM_COM2_TX_PIN                 GPIO_Pin_2
#define STM_COM2_TX_GPIO_PORT           GPIOA
#define STM_COM2_TX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define STM_COM2_TX_SOURCE              GPIO_PinSource2
#define STM_COM2_TX_AF                  GPIO_AF_USART2

#define STM_COM2_RX_PIN                 GPIO_Pin_3
#define STM_COM2_RX_GPIO_PORT           GPIOA
#define STM_COM2_RX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define STM_COM2_RX_SOURCE              GPIO_PinSource3
#define STM_COM2_RX_AF                  GPIO_AF_USART2

#define STM_COM2_IRQn                   USART2_IRQn

/*   Debug COM Pin tanimlamasi */
#define STM_COM3                        USART3
#define STM_COM3_CLK                    RCC_APB1Periph_USART3

#define STM_COM3_TX_PIN                 GPIO_Pin_10
#define STM_COM3_TX_GPIO_PORT           GPIOC
#define STM_COM3_TX_GPIO_CLK            RCC_AHBPeriph_GPIOC
#define STM_COM3_TX_SOURCE              GPIO_PinSource10
#define STM_COM3_TX_AF                  GPIO_AF_USART3

#define STM_COM3_RX_PIN                 GPIO_Pin_11
#define STM_COM3_RX_GPIO_PORT           GPIOC
#define STM_COM3_RX_GPIO_CLK            RCC_AHBPeriph_GPIOC
#define STM_COM3_RX_SOURCE              GPIO_PinSource11
#define STM_COM3_RX_AF                  GPIO_AF_USART3

#define STM_COM3_IRQn                   USART3_IRQn

////////////////////////////////////////////////////
//																								//
//			Selenoid Valf Kontrol Tanimlamalari				//
//																								//
////////////////////////////////////////////////////

/* Valf üzerinden Akim Akma Zamani */
#define  Valve_Time     100 // ~100mS
/* Sarj Pump Voltajinin belirlenen seviyeye yükselme zaman asimi */
#define  SVK_TimeOut  100000	// 10 sn 
/* 72,727KHz = ( 110 / (SystemCoreClock)4000000 )  
pwm puls frekansi duty cycle %50 _|-|_|-|_|-  */
#define  Pwm_Freq   200	 // 72 Khz 	4Mhz => 55 8Mhz =>110 

/* Dijital Puls Pin   */
#define 	SVK_Puls_Pin				GPIO_Pin_6
#define 	SVK_Puls_Src				GPIO_PinSource6	
#define 	SVK_Puls_Port				GPIOA	
#define 	SVK_Puls_Clk				RCC_AHBPeriph_GPIOA	
#define 	SVK_Puls_AF_TIMx		GPIO_AF_TIM3
/* Analog Vref Pin   */
#define 	SVK_Vref_Pin				GPIO_Pin_7
#define 	SVK_Vref_Port				GPIOA
#define 	SVK_Vref_Clk				RCC_AHBPeriph_GPIOA
#define 	SVK_RI_IOSwitch_CHx	RI_IOSwitch_CH7
/* Vref GND polarma pin  */
#define 	SVK_RefEnb_Pin			GPIO_Pin_4
#define 	SVK_RefEnb_Port			GPIOC
#define 	SVK_RefEnb_Clk			RCC_AHBPeriph_GPIOC
/* Ac Pin  */	
#define 	SVK_Open_Pin				GPIO_Pin_1
#define 	SVK_Open_Port				GPIOA
#define 	SVK_Open_Clk				RCC_AHBPeriph_GPIOA
/* Kapat Pin   */	
#define 	SVK_Close_Pin				GPIO_Pin_5
#define 	SVK_Close_Port			GPIOA
#define 	SVK_Close_Clk				RCC_AHBPeriph_GPIOA

////////////////////////////////////////////////////
//																								//
//					 LCD ST7522 Tanimlamalari							//
//																								//
////////////////////////////////////////////////////

#define  Lcd_Si_Pin						GPIO_Pin_14
#define  Lcd_Si_Port					GPIOB
#define  Lcd_Si_Clk						RCC_AHBPeriph_GPIOB  
  
#define  Lcd_Scl_Pin					GPIO_Pin_2
#define  Lcd_Scl_Port					GPIOB
#define  Lcd_Scl_Clk					RCC_AHBPeriph_GPIOB

#define  Lcd_A0_Pin						GPIO_Pin_1
#define  Lcd_A0_Port					GPIOB
#define  Lcd_A0_Clk						RCC_AHBPeriph_GPIOB  

#define  Lcd_Enb_Pin					GPIO_Pin_13
#define  Lcd_Enb_Port					GPIOB
#define  Lcd_Enb_Clk					RCC_AHBPeriph_GPIOB

#define  Lcd_Rst_Pin					GPIO_Pin_5
#define  Lcd_Rst_Port					GPIOC
#define  Lcd_Rst_Clk					RCC_AHBPeriph_GPIOC

#define  Lcd_BL_Pin						GPIO_Pin_0
#define  Lcd_BL_Port					GPIOB
#define  Lcd_BL_Clk						RCC_AHBPeriph_GPIOB

#define  Lcd_CS_Pin						GPIO_Pin_1
#define  Lcd_CS_Port					GPIOB
#define  Lcd_CS_Clk						RCC_AHBPeriph_GPIOB 

////////////////////////////////////////////////////
//																								//
//			SPI	FM1702sl KART OKUMA PIN TABLOSU				//
//																								//
////////////////////////////////////////////////////

#define FM_SPIx                SPI1
#define FM_SPIx_CLK            RCC_APB2Periph_SPI1

#define FM_SCK_PIN             GPIO_Pin_3                
#define FM_SCK_PORT            GPIOB                       
#define FM_SCK_CLK             RCC_AHBPeriph_GPIOB
#define FM_SCK_SOURCE          GPIO_PinSource3
#define FM_SCK_AF              GPIO_AF_SPI1

#define FM_MISO_PIN            GPIO_Pin_4                
#define FM_MISO_PORT           GPIOB                    
#define FM_MISO_CLK            RCC_AHBPeriph_GPIOB
#define FM_MISO_SOURCE         GPIO_PinSource4
#define FM_MISO_AF             GPIO_AF_SPI1

#define FM_MOSI_PIN            GPIO_Pin_5            
#define FM_MOSI_PORT           GPIOB                    
#define FM_MOSI_CLK            RCC_AHBPeriph_GPIOB
#define FM_MOSI_SOURCE         GPIO_PinSource5
#define FM_MOSI_AF             GPIO_AF_SPI1

#define FM_NSS_PIN          	 GPIO_Pin_15            
#define FM_NSS_PORT            GPIOA                    
#define FM_NSS_CLK             RCC_AHBPeriph_GPIOA

#define FM_RST_PIN             GPIO_Pin_6           
#define FM_RST_PORT            GPIOB                    
#define FM_RST_CLK             RCC_AHBPeriph_GPIOB

#define FM_ENB_PIN             GPIO_Pin_12            
#define FM_ENB_PORT            GPIOA                    
#define FM_ENB_CLK             RCC_AHBPeriph_GPIOA

////////////////////////////////////////////////////
//																								//
//			I2C EEPROM HABERLESME PIN TABLOSU		  		//
//																								//
////////////////////////////////////////////////////

/**
  * @brief  I2C EEPROM Interface pins
  */  
#define sEE_I2C                          I2C2
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C2
   
#define sEE_I2C_SCL_PIN                  GPIO_Pin_10                  
#define sEE_I2C_SCL_PORT            		 GPIOB                     
#define sEE_I2C_SCL_CLK             		 RCC_AHBPeriph_GPIOB
#define sEE_I2C_SCL_SOURCE               GPIO_PinSource10
#define sEE_I2C_SCL_AF                   GPIO_AF_I2C2

#define sEE_I2C_SDA_PIN                  GPIO_Pin_11                
#define sEE_I2C_SDA_PORT            		 GPIOB                     
#define sEE_I2C_SDA_CLK            			 RCC_AHBPeriph_GPIOB
#define sEE_I2C_SDA_SOURCE               GPIO_PinSource11
#define sEE_I2C_SDA_AF                   GPIO_AF_I2C2

#define E2prom_Kbit            512				// eeprom boyutu
#define I2C_Speed              300000      // haberleþme hýzý
#define TimeOut_I2c_Ee         50000      // zaman aþýmý süresi		
#define I2Cx_SLAVE_ADDRESS7    0xA0       // eeprom adresi

/******************************************************************/

void COM_DeInit(COM_TypeDef COM);
void COM_Init(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);
void Pin_Output_OD(Pin_TypeDef Pin);
void Pin_Output(Pin_TypeDef Pin);
void Pin_Input(Pin_TypeDef Pin);
void Pin_Input_PU(Pin_TypeDef Pin);
void Pin_Input_PD(Pin_TypeDef Pin);
void Pin_High(Pin_TypeDef Pin);
void Pin_Low(Pin_TypeDef Pin);
void Pin_Toggle(Pin_TypeDef Pin);
uint32_t Pin_Get(Pin_TypeDef Pin);

/******************************************************************/

#ifdef __cplusplus
}
#endif
  
#endif /* __STM32L1xx_BOARD_121016KGS00_H*/




