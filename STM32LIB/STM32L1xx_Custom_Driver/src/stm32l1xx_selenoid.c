/**
  ******************************************************************************
  * @file    stm32l1xx_selenoid.c
  * @author  Coskun ERGAN
  * @version V1.0.4
  * @date    03-Ekim-2012
  * @brief   Selenoid Valf Kontrol(SVK) kütüpanesi 
  *
	*  @verbatim
******************************************************************************
	*   BiLGi;
	*
	*						
	*
	******************************************************************************
	*   Notlar;
	*		
	*		- Zamanlama degisikliklerini stm32l1xx_selenoid.h" dosyasi icerisindeki define satirlayla yapabilirsiniz. 
	*		- ADC_IN0 ile ADC_IN25 dahil arasinda kalan tüm pinler VrefPin olarak Tanimlanabilir.
	*				örnek; PB12 => ADC_IN18 => RI_IOSwitch_CH18
	*		- Tüm IO pinler GND ref. enable Pin olarak tan1mlanabilir bu pinin görevi LP uygulamalarda kacak akimlari önlemektir.
	*		- Tüm IO pinler Valf_Ac/Kapat pinleri olarak kullan1labilir.
	*
	******************************************************************************	
  *
	*  Valf_Hata(uint8_t) 
	*
	* 0 => Basarili;         	 Valf Basarili bir sekilde Acildi/Kapatildi
	* 1 => ZamanAsimi Hatasi;	 Voltaj yükseltme islemi zaman sinirini asti.
	*												 		Sebepleri:
	*												  	- Pil voltaji düsük, pil arizali.
	*														- Sarj devresi arizali
	*														- Selenoid devresi kompanentleri arizali.
  *
	******************************************************************************
	*
	*
	******************************************************************************
	*@endverbatim
	*****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_selenoid.h"

/** @addtogroup Selenoid valf Ac Kapat kütüpanesi
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


uint32_t	Svk_Error_Time;
uint16_t  Voltage_UpSet;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @defgroup COMP_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions.
 *
@verbatim
 ===============================================================================
              ##### Initialization and Configuration functions #####
 ===============================================================================
*/
 

void Svk_Pin_Init(GPIO_TypeDef* GPIOx, uint16_t Port_Pin, uint16_t Port_Clk, uint8_t Port_Mod,uint8_t Port_Typ )
{
 		GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_AHBPeriphClockCmd(Port_Clk , ENABLE);
		GPIO_InitStructure.GPIO_Pin = Port_Pin;
	if(Port_Mod==GPIO_Mode_OUT)
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	else 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	if(Port_Typ==GPIO_OType_PP)
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP ;
	else
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOx, &GPIO_InitStructure); 

}
/**
  * @brief  
  * @note   
  * @note   
  * @param   
  * @retval None
  */	
void SVK_Init(void)
{

		Svk_Pin_Init(SVK_Puls_Port,SVK_Puls_Pin,SVK_Puls_Clk,GPIO_Mode_OUT,GPIO_OType_PP);	
		GPIO_ResetBits(SVK_Puls_Port,SVK_Puls_Pin); 	
		Svk_Pin_Init(SVK_Vref_Port,SVK_Vref_Pin,SVK_Vref_Clk,GPIO_Mode_AIN,GPIO_OType_PP);	
		Svk_Pin_Init(SVK_RefEnb_Port,SVK_RefEnb_Pin,SVK_RefEnb_Clk,GPIO_Mode_OUT,GPIO_OType_OD);
		GPIO_SetBits(SVK_RefEnb_Port,SVK_RefEnb_Pin); 	
		Svk_Pin_Init(SVK_Open_Port,SVK_Open_Pin,SVK_Open_Clk,GPIO_Mode_OUT,GPIO_OType_PP);
		Svk_Pin_Init(SVK_Close_Port,SVK_Close_Pin,SVK_Close_Clk,GPIO_Mode_OUT,GPIO_OType_PP);
		GPIO_ResetBits(SVK_Open_Port,SVK_Open_Pin); 
	  GPIO_ResetBits(SVK_Close_Port,SVK_Close_Pin); 
}
/**
  * @}
  */

uint8_t SVK_Open(void)
{
	uint32_t t;
	
	COMP_InitTypeDef COMP_InitStructure;
 	/* Comparator resetleniyor */
	COMP_DeInit();
 	/* Comparator clock aktif */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_COMP, DISABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_COMP, ENABLE);
	
  COMP_InitStructure.COMP_InvertingInput = COMP_InvertingInput_1_2VREFINT;
  COMP_InitStructure.COMP_OutputSelect = COMP_OutputSelect_None;
  COMP_InitStructure.COMP_Speed = COMP_Speed_Fast;
  COMP_Init(&COMP_InitStructure);
	
  /* Enable the Comparator 1 */
  COMP_Cmd(ENABLE);

 /* Switch kontrol etmek aktif */
  SYSCFG_RISwitchControlModeCmd(ENABLE);
  /* COMP1 ADC analog pinlere ulasmak icin VCOMP switch aktif  */
  SYSCFG_RIIOSwitchConfig(RI_IOSwitch_VCOMP, ENABLE);
  /* COMP1 ADC analog PinX switch aktif  */
  SYSCFG_RIIOSwitchConfig(SVK_RI_IOSwitch_CHx, ENABLE);
	
	/* GndVreferans pini kullan1lacak */
	GPIO_ResetBits(SVK_RefEnb_Port,SVK_RefEnb_Pin); 	
	
	GPIO_ResetBits(SVK_Open_Port,SVK_Open_Pin); 
	
	GPIO_SetBits(SVK_Close_Port,SVK_Close_Pin);
	DelayMs(Valve_Time);
	GPIO_ResetBits(SVK_Close_Port,SVK_Close_Pin);	
//////////////////////////////////////////		
		IWDG_ReloadCounter();
//////////////////////////////////////////			
	Svk_Error_Time=SVK_TimeOut;	
	/* Voltaj seviyenin üzerindeyse bekle..
	   Not: düzgün calisan bir sistemde burda bekleme yapmaz */
	while(COMP_GetOutputLevel(COMP_Selection_COMP1))if(Svk_Error_Time==0)break; else Svk_Error_Time--;
	
	while(1){

//	if(Svk_Error_Time==0){Valve_Error2_S;break;} else Svk_Error_Time--;		
		
	GPIO_ToggleBits(SVK_Puls_Port,SVK_Puls_Pin); 
	t=Pwm_Freq;
	while(t--);			
		
	if(COMP_GetOutputLevel(COMP_Selection_COMP1))break;	
		
	}	
		
	GPIO_ResetBits(SVK_Puls_Port,SVK_Puls_Pin);
	
	/*Valfe Voltaj Gönderiliyor */
	GPIO_SetBits(SVK_Open_Port,SVK_Open_Pin); 
	/*Valf üzerinden voltaj bosalmaya devam ediyor */
	DelayMs(Valve_Time);	
	/* Valf Voltaj1 kesiliyor */
	GPIO_ResetBits(SVK_Open_Port,SVK_Open_Pin);

	Voltage_UpSet=10000;
	
	while(1){	
		
	GPIO_ToggleBits(SVK_Puls_Port,SVK_Puls_Pin); 
	t=Pwm_Freq;
	while(t--);			
	Voltage_UpSet--;
	if(!Voltage_UpSet)break;	
		
	}	

//	if(COMP_GetOutputLevel(COMP_Selection_COMP1)){Valve_Error1_S;Svk_Error_Time=0;}
	/* Referans pin pasif yap1l1yor */
	GPIO_SetBits(SVK_RefEnb_Port,SVK_RefEnb_Pin); 
	
	if(Svk_Error_Time==0)return 1;
	
	return 0;
	
}
/**
  * @}
  */
uint8_t SVK_Close(void)
{
	uint32_t t;
	
	COMP_InitTypeDef COMP_InitStructure;
 	/* Comparator resetleniyor */
	COMP_DeInit();
 	/* Comparator clock aktif */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_COMP, DISABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_COMP, ENABLE);
	
  COMP_InitStructure.COMP_InvertingInput = COMP_InvertingInput_1_2VREFINT;
  COMP_InitStructure.COMP_OutputSelect = COMP_OutputSelect_None;
  COMP_InitStructure.COMP_Speed = COMP_Speed_Fast;
  COMP_Init(&COMP_InitStructure);
	
  /* Enable the Comparator 1 */
  COMP_Cmd(ENABLE);

 /* Switch kontrol etmek aktif */
  SYSCFG_RISwitchControlModeCmd(ENABLE);
  /* COMP1 ADC analog pinlere ulasmak icin VCOMP switch aktif  */
  SYSCFG_RIIOSwitchConfig(RI_IOSwitch_VCOMP, ENABLE);
  /* COMP1 ADC analog PinX switch aktif  */
  SYSCFG_RIIOSwitchConfig(SVK_RI_IOSwitch_CHx, ENABLE);
	
	/* GndVreferans pini kullan1lacak */
	GPIO_ResetBits(SVK_RefEnb_Port,SVK_RefEnb_Pin); 	
	
	GPIO_ResetBits(SVK_Close_Port,SVK_Close_Pin); 
	
	GPIO_SetBits(SVK_Open_Port,SVK_Open_Pin);
	DelayMs(Valve_Time);
	GPIO_ResetBits(SVK_Open_Port,SVK_Open_Pin);	
//////////////////////////////////////////		
		IWDG_ReloadCounter();
//////////////////////////////////////////		
	Svk_Error_Time=SVK_TimeOut;	
	/* Voltaj seviyenin üzerindeyse bekle..
	   Not: düzgün calisan bir sistemde burda bekleme yapmaz */	
	while(COMP_GetOutputLevel(COMP_Selection_COMP1))if(Svk_Error_Time==0)break; else Svk_Error_Time--;
	
	while(1){

	//if(Svk_Error_Time==0){Valve_Error2_S;break;} else Svk_Error_Time--;		
		
	GPIO_ToggleBits(SVK_Puls_Port,SVK_Puls_Pin); 
	t=Pwm_Freq;
	while(t--);			
		
	if(COMP_GetOutputLevel(COMP_Selection_COMP1))break;	

		
	}	
		
	GPIO_ResetBits(SVK_Puls_Port,SVK_Puls_Pin);
	
	/*Valfe Voltaj Gönderiliyor */
	GPIO_SetBits(SVK_Close_Port,SVK_Close_Pin); 
		/*Valf üzerinden voltaj bosalmaya devam ediyor */
	DelayMs(Valve_Time);	
	/* Valf Voltaj1 kesiliyor */
	GPIO_ResetBits(SVK_Close_Port,SVK_Close_Pin);
	
	Voltage_UpSet=10000;
	
	while(1){	
		
	GPIO_ToggleBits(SVK_Puls_Port,SVK_Puls_Pin); 
	t=Pwm_Freq;
	while(t--);			
	Voltage_UpSet--;
	if(!Voltage_UpSet)break;	
		
	}	

	//if(COMP_GetOutputLevel(COMP_Selection_COMP1)){Valve_Error1_S;Svk_Error_Time=0;}
	/* Referans pin pasif yap1l1yor */
	GPIO_SetBits(SVK_RefEnb_Port,SVK_RefEnb_Pin); 
	
	if(Svk_Error_Time==0)return 1;
	
	return 0;
	
}

/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/
