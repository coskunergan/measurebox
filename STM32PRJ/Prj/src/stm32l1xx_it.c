/**
  ******************************************************************************
  * @file    STM32L1xx_IAP/binary_template/src/stm32l1xx_it.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    24-January-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * FOR MORE INFORMATION PLEASE READ CAREFULLY THE LICENSE AGREEMENT FILE
  * LOCATED IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_it.h"
#include "main.h"
#include "extern_reg.c"

/** @addtogroup binary_template
  * @{
  */

/** @addtogroup SysTick
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/
/**
  * @brief  This function handles RTC Auto wake-up interrupt request.
  * @param  None
  * @retval None
  */
void RTC_WKUP_IRQHandler(void)
{
   disableInterrupts();
   RTC_ClearITPendingBit(RTC_IT_WUT);
   EXTI_ClearITPendingBit(EXTI_Line20);

   enableInterrupts();
}


void EXTI0_IRQHandler(void)
{
  disableInterrupts();
  EXTI_ClearITPendingBit(EXTI_Line0);
//	Task=TRUE;
//	Menu_Task=TRUE;
  enableInterrupts();
}

void EXTI15_10_IRQHandler(void)
{
  disableInterrupts();
  EXTI_ClearITPendingBit(EXTI_Line13);	
//	Task=TRUE;
//	Menu_Task=TRUE;
  enableInterrupts();
}

/**
  * @brief  This function handles RTC Alarms interrupt request.
  * @param  None
  * @retval None
  */
void RTC_Alarm_IRQHandler(void)
{
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET)
  {
 
    RTC_ClearITPendingBit(RTC_IT_ALRA);
    EXTI_ClearITPendingBit(EXTI_Line17);
  } 
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

    TimingDelay_Decrement();

}

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}



void USART2_IRQHandler(void)
{
	uint8_t i,chk;
	uint32_t adres, * ptr;

		if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
		{
			/* Read one byte from the receive data register */

			 TIM_SetCounter(TIM5, 0);  // byte akisi var counter temizle
			
			 RamRxTxbuffer[RamRxCount++]=(uint8_t)USART_ReceiveData(USART2);

			 if(RamRxCount>=9)
			 {
				 chk=1;
				 for(i=0;i<8;i++)
						chk+=RamRxTxbuffer[i];
				
					if(chk == RamRxTxbuffer[8])
					{
						if(	RamRxTxbuffer[0]== 0x22 && 
								RamRxTxbuffer[1]== 0x22 &&  
								RamRxTxbuffer[2]== 0x22 && 
								RamRxTxbuffer[3]== 0x22	)
						{
								adres=0x20000000;
								adres|=RamRxTxbuffer[6];
								adres|=RamRxTxbuffer[5]<<8;

								if(RamRxTxbuffer[4]=='W')
								{
									// Yaz
									ptr=(uint32_t *)adres;
									*(__IO uint8_t *) ptr= RamRxTxbuffer[7];
									RamRxTxbuffer[8]=1;
									for(i=0;i<8;i++)
									RamRxTxbuffer[8]+=RamRxTxbuffer[i];									
									USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
								}
								else if(RamRxTxbuffer[4]=='R')
								{
									// oku
									ptr=(uint32_t *)adres;
									RamRxTxbuffer[7]=(uint8_t )*ptr;
									RamRxTxbuffer[8]=1;
									for(i=0;i<8;i++)				
									RamRxTxbuffer[8]+=RamRxTxbuffer[i];		
									USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
								}					
						}
					}
				RamRxCount=0;  
			 }
		}

		if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
		{
			/* Send the received data to the PC Host*/
				USART_SendData(USART2,RamRxTxbuffer[RamTxCount++]);
			
				if(RamTxCount>=9)
					{
						RamTxCount=0;
						USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
					}
			
		}
	
}

/**
  * @brief  This function handles selenoid vref comparator.
  * @param  None
  * @retval None
  */

void TIM5_IRQHandler (void) // MBus Paket Timeout timer i
{
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	RamRxCount=0;

}	
/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */  


/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/
