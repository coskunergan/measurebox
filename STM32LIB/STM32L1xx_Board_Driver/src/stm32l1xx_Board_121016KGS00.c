/**
  ******************************************************************************
  * @file    stm32l1xx_121016KGS00.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    26-Kasim-2012
  * @brief   #KARTLI GPRS SAYAC# Temel Donanim Fonksiyonlari
	* 
	*  @verbatim
	******************************************************************************
	*   Kart üzerindeki pin port donanim haberlesmeleri ile ilgili bilgiler;
	*
	*	
	******************************************************************************
	*@endverbatim
	*****************************************************************************/
	
#include "stm32l1xx_Board_121016KGS00.h"

	
GPIO_TypeDef* GPIO_PORT[PINn] = {Led_Pwrmon_Port,Buzzer_Port,ButonA_Port,ButonB_Port,Gsm_Rst_Port,GSM_Enb_Port,
																 FM_Enb_Port,EEP_Enb_Port,Pulse_Enb_Port,DRV_M1_Port,DRV_M2_Port,DRV_Sleep_Port,
																 Pulse_1_Port,Pulse_2_Port,Pulse_3_Port	};
const uint16_t GPIO_PIN[PINn] = {Led_Pwrmon_Pin,Buzzer_Pin,ButonA_Pin,ButonB_Pin,Gsm_Rst_Pin,GSM_Enb_Pin,
																 FM_Enb_Pin,EEP_Enb_Pin,Pulse_Enb_Pin,DRV_M1_Pin,DRV_M2_Pin,DRV_Sleep_Pin,
																 Pulse_1_Pin,Pulse_2_Pin,Pulse_3_Pin	};
const uint32_t GPIO_CLK[PINn] = {Led_Pwrmon_Clk,Buzzer_Clk,ButonA_Clk,ButonB_Clk,Gsm_Rst_Clk,GSM_Enb_Clk,
																 FM_Enb_Clk,EEP_Enb_Clk,Pulse_Enb_Clk,DRV_M1_Clk,DRV_M2_Clk,DRV_Sleep_Clk,
																 Pulse_1_Clk,Pulse_2_Clk,Pulse_3_Clk	};	
	


USART_TypeDef* COM_USART[COMn] = {STM_COM1,STM_COM2,STM_COM3}; 
GPIO_TypeDef* COM_TX_PORT[COMn] = {STM_COM1_TX_GPIO_PORT,STM_COM2_TX_GPIO_PORT,STM_COM3_TX_GPIO_PORT};
GPIO_TypeDef* COM_RX_PORT[COMn] = {STM_COM1_RX_GPIO_PORT,STM_COM2_RX_GPIO_PORT,STM_COM3_RX_GPIO_PORT};
const uint32_t COM_USART_CLK[COMn] = {STM_COM1_CLK,STM_COM2_CLK,STM_COM3_CLK};
const uint32_t COM_TX_PORT_CLK[COMn] = {STM_COM1_TX_GPIO_CLK,STM_COM2_TX_GPIO_CLK,STM_COM3_TX_GPIO_CLK};
const uint32_t COM_RX_PORT_CLK[COMn] = {STM_COM1_RX_GPIO_CLK,STM_COM2_RX_GPIO_CLK,STM_COM3_RX_GPIO_CLK};
const uint16_t COM_TX_PIN[COMn] = {STM_COM1_TX_PIN,STM_COM2_TX_PIN,STM_COM3_TX_PIN};
const uint16_t COM_RX_PIN[COMn] = {STM_COM1_RX_PIN,STM_COM2_RX_PIN,STM_COM3_RX_PIN};
const uint8_t COM_TX_PIN_SOURCE[COMn] = {STM_COM1_TX_SOURCE,STM_COM2_TX_SOURCE,STM_COM3_TX_SOURCE};
const uint8_t COM_RX_PIN_SOURCE[COMn] = {STM_COM1_RX_SOURCE,STM_COM2_RX_SOURCE,STM_COM3_RX_SOURCE};
const uint8_t COM_TX_AF[COMn] = {STM_COM1_TX_AF,STM_COM2_TX_AF,STM_COM3_TX_AF};
const uint8_t COM_RX_AF[COMn] = {STM_COM1_RX_AF,STM_COM2_RX_AF,STM_COM3_RX_AF};

/****************************************************/
void COM_DeInit(COM_TypeDef COM)
{
   GPIO_InitTypeDef GPIO_InitStructure;
  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);
    
  /* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
  GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);
	
	USART_DeInit(COM_USART[COM]);
}
/****************************************************/
void COM_Init(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM], ENABLE);

	if(COM == 0)
  /* Enable USART-1	clock */
  RCC_APB2PeriphClockCmd(COM_USART_CLK[COM], ENABLE); 
  else
	/* Enable USART-2-3-4-5	clock */
	RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE); 
	
  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(COM_TX_PORT[COM], COM_TX_PIN_SOURCE[COM], COM_TX_AF[COM]);

  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(COM_RX_PORT[COM], COM_RX_PIN_SOURCE[COM], COM_RX_AF[COM]);
  
  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);
    
  /* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
  GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);

  /* USART configuration */
  USART_Init(COM_USART[COM], USART_InitStruct);
    
  /* Enable USART */
  USART_Cmd(COM_USART[COM], ENABLE);
}
/****************************************************/
void Pin_Output_OD(Pin_TypeDef Pin)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the pin Clock */
  RCC_AHBPeriphClockCmd(GPIO_CLK[Pin], ENABLE);

  /* Configure the pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Pin];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_Init(GPIO_PORT[Pin], &GPIO_InitStructure);
}
/****************************************************/
void Pin_Output(Pin_TypeDef Pin)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the pin Clock */
  RCC_AHBPeriphClockCmd(GPIO_CLK[Pin], ENABLE);

  /* Configure the pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Pin];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_Init(GPIO_PORT[Pin], &GPIO_InitStructure);
}
/****************************************************/
void Pin_Input(Pin_TypeDef Pin)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the Pin Clock */
  RCC_AHBPeriphClockCmd(GPIO_CLK[Pin], ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Pin];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIO_PORT[Pin], &GPIO_InitStructure);
}
/****************************************************/
void Pin_Input_PU(Pin_TypeDef Pin)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the Pin Clock */
  RCC_AHBPeriphClockCmd(GPIO_CLK[Pin], ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Pin];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIO_PORT[Pin], &GPIO_InitStructure);
}
/****************************************************/
void Pin_Input_PD(Pin_TypeDef Pin)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the Pin Clock */
  RCC_AHBPeriphClockCmd(GPIO_CLK[Pin], ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Pin];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIO_PORT[Pin], &GPIO_InitStructure);
}
/****************************************************/
void Pin_High(Pin_TypeDef Pin)
{
	  GPIO_PORT[Pin]->BSRRL = GPIO_PIN[Pin];
}	
/****************************************************/
void Pin_Low(Pin_TypeDef Pin)
{
	  GPIO_PORT[Pin]->BSRRH = GPIO_PIN[Pin];
}	
/****************************************************/
void Pin_Toggle(Pin_TypeDef Pin)
{
	 GPIO_PORT[Pin]->ODR ^= GPIO_PIN[Pin];
}	
/****************************************************/
uint32_t Pin_Get(Pin_TypeDef Pin)
{
  return GPIO_ReadInputDataBit(GPIO_PORT[Pin], GPIO_PIN[Pin]);
}	
/****************************************************/
/****************************************************/
/****************************************************/
/****************************************************/
/****************************************************/
/****************************************************/
/****************************************************/
/****************************************************/

