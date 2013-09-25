/**
  ******************************************************************************
  * @file    stm32l1xx_sht11.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    25-Eylül-2013
  * @brief   SHT11 Isi Nem Sensöru kütüpanesi 
  *
  *  @verbatim
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_sht11.h"
#include "math.h"   

/** @addtogroup lcd kütüpanesi
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/***************** PORT *******************/

#define SHT_GPIO  GPIOC
#define SDA_PIN   GPIO_Pin_9
#define SCL_PIN	  GPIO_Pin_8

/***************************************/

#define Sda 	((GPIO_ReadInputDataBit(SHT_GPIO,SDA_PIN))&0x01)

#define SDA(x) ((x) ? (GPIO_SetBits(SHT_GPIO,SDA_PIN))  : (GPIO_ResetBits(SHT_GPIO,SDA_PIN)) );
#define SCL(x) ((x) ? (GPIO_SetBits(SHT_GPIO,SCL_PIN))  : (GPIO_ResetBits(SHT_GPIO,SCL_PIN)) ); 

#define in   1
#define out  0

#define Tamam	1
#define	Hata	0

#define ISI 0x03
#define NEM 0x05

GPIO_InitTypeDef GPIO_InitStructure;

/******************************************************************************/
/******************************************************************************/
/***                      SHT11 Sensör Haberlesme Programi                  ***/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
void SHT11_TRIS_SDA(char x)
{
			GPIO_InitStructure.GPIO_Pin = SDA_PIN;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;	
	if(!x)
			{GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;}
	else 
			{GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;}
			GPIO_Init(SHT_GPIO, &GPIO_InitStructure);
}
/******************************************************************************/
void SHT11_NAck(void)
{
		 SDA(0);
		 SHT11_TRIS_SDA(out);
		 SCL(1);                
		 SCL(0);
		 SHT11_TRIS_SDA(in);
	
}
/******************************************************************************/
char SHT11_Ack(void)
{ 
		 SCL(0);                 
		 SHT11_TRIS_SDA(in);			
		 SCL(1);
		 return(Sda);
}
/******************************************************************************/
void SHT11_Start(void)
{
		 SDA(1);
		 SCL(0);	
		 SHT11_TRIS_SDA(out);		
		 SCL(1);
		 SDA(0);
		 SCL(0);
		 SCL(1);
		 SDA(1);
		 SCL(0);
		 SDA(0);
}
/******************************************************************************/
void SHT11_Gonder8Bit(unsigned char x)
{ 
 unsigned char i=0x80;
   SHT11_TRIS_SDA(out);
 do{
   if (x&i){ SDA(1);}
   else {SDA(0);}
   SCL(1);
   SCL(0);
   i>>=1;
  }while(i!=0);
}
/****************************************************************************/
uint8_t SHT11_Oku8Bit(void)
{
	uint8_t x=0,i=0x80;	

		 do
			{
			 SCL(1);
			 if (Sda) x=(x)|i;
			 i>>=1;
			 SCL(0);
			
			}while(i!=0);
			SCL(0);
 
  return x;
}
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
void SHT11_Reset(void)
{
   unsigned long kont;
   SDA(1);
   SCL(1);
   SHT11_TRIS_SDA(out);
   SHT11_Gonder8Bit(0xFF); 
   SHT11_Gonder8Bit(0xFF); 
   SCL(0);
}
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
uint8_t SHT11_Paket_Al(uint8_t secim, float *ham)
{  
	uint16_t kont=0;
	uint32_t Timeout=100000;

   SHT11_Start();	 	
   SHT11_Gonder8Bit(secim);        
   if (SHT11_Ack()) return 1;  
   SCL(0);

   while(Sda)
	 {
		Timeout--;
		if(!Timeout)return 1;
	 }	 

   kont=SHT11_Oku8Bit();
   kont<<=8;           
   SHT11_NAck(); 
   kont|=SHT11_Oku8Bit();
   *ham=kont;
   SHT11_NAck();
   SHT11_Oku8Bit(); 
   SHT11_Ack();
   return 0;
}																			
/******************************************************************************/
void SHT11_Hesapla(float *isi_ham, float *nem_ham)
{
  const float C1=-2.0468;          
  const float C2=+0.0367;           
  const float C3=-0.0000015955;    
  const float T1=+0.01;             
  const float T2=+0.00008;          
 
  float nem=*nem_ham;             
  float isi=*isi_ham;         
  float nem_lin;                     
  float nem_gercek;                  
  float isi_gercek; 
                   

  isi_gercek=isi*0.01 - 39.7;           
  nem_lin=C3*nem*nem + C2*nem + C1;      
  nem_gercek=(isi_gercek-25)*(T1+T2*nem)+nem_lin;   

  if(nem_gercek>99)nem_gercek=99;        
  if(nem_gercek<0.1)nem_gercek=0.1;  
               
  *nem_ham=nem_gercek;

  *isi_ham=isi_gercek;
 
}
/*****************************************************************************/
uint8_t SHT11_Oku(float *isi,float *nem)
{
	float nem_ham,isi_ham;
	uint8_t err=0;
               	 
	err|=SHT11_Paket_Al(ISI,&isi_ham);	 
	err|=SHT11_Paket_Al(NEM,&nem_ham); 
	
	SHT11_Hesapla(&isi_ham,&nem_ham);    
   
	*isi=isi_ham;
	*nem=nem_ham;

 	if(err)return (Hata);  
 	return (Tamam);
}
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/
