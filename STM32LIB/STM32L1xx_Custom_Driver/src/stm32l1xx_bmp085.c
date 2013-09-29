/**
  ******************************************************************************
  * @file    stm32l1xx_bmp085.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    29-Eylül-2013
  * @brief   Bosch BMP-085 basinç Sensörü kütüpanesi 
  *
  *  @verbatim
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_bmp085.h" 
#include "math.h"
/** @addtogroup sensör kütüpanesi
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/***************** PORT *******************/
#define BMP_SDA_GPIO  GPIOC
#define BMP_SDA_PIN   GPIO_Pin_9
#define BMP_SCL_GPIO  GPIOC
#define BMP_SCL_PIN	  GPIO_Pin_8
/***************** Control ****************/
#define Sda 	((BMP_SDA_GPIO->IDR & BMP_SDA_PIN)!=0x0)
#define SCL_LOW    BMP_SDA_GPIO->BSRRH = BMP_SCL_PIN
#define SCL_HIGH   BMP_SDA_GPIO->BSRRL = BMP_SCL_PIN
#define SDA_LOW   BMP_SCL_GPIO->BSRRH = BMP_SDA_PIN
#define SDA_HIGH  BMP_SCL_GPIO->BSRRL = BMP_SDA_PIN
/***************** define ****************/
#define I2C_Adres 0xEE
// oversampling setting
// 0 = ultra low power
// 1 = standard
// 2 = high
// 3 = ultra high resolution
const uint8_t oversampling_setting = 3; //oversampling for measurement
const uint8_t pressure_conversiontime[4] = { 5, 8, 14, 26 };  // delays for oversampling settings 0, 1, 2 and 3  type is milisecond 
int16_t ac1;
int16_t ac2; 
int16_t ac3; 
uint16_t ac4;
uint16_t ac5;
uint16_t ac6;
int16_t b1; 
int16_t b2;
int16_t mb;
int16_t mc;
int16_t md;
uint8_t hata;
/***************** timing ****************/
#define BMP085_Delay_1  __NOP(); //1us
#define BMP085_Delay_2  __NOP();__NOP();  //2us
/******************************************************************************/
/******************************************************************************/
/***                    BMP-085 Sensör Haberlesme Programi                  ***/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
void BMP085_Start(void)
{
		 SDA_HIGH;
		 SCL_HIGH;	
		 BMP085_Delay_1;  		
		 SDA_LOW;
		 BMP085_Delay_1;        
}
/******************************************************************************/
void BMP085_NAck(void)  // master No ack
{
		 SDA_HIGH;	
		 BMP085_Delay_1;
		 SCL_HIGH;       
		 BMP085_Delay_1;
		 SCL_LOW;		
}
/******************************************************************************/
bool BMP085_Ack(void)  // slave ack
{ 
	bool ack=0;
	   SDA_HIGH;	
		 SCL_HIGH;
		 BMP085_Delay_1;	
		 if(Sda)ack=1;
		 SCL_LOW;
	return ack;
}
/******************************************************************************/
void BMP085_MAck(void) // master ack
{ 
	   SDA_LOW; 
		 BMP085_Delay_1;
		 SCL_HIGH;
		 BMP085_Delay_1;	
		 SCL_LOW;
	   SDA_HIGH; 	
}
/****************************************************************************/
void BMP085_Stop(void)
{
			SDA_LOW;                  		 
			BMP085_Delay_1
			SCL_HIGH;
			BMP085_Delay_1;
			SDA_HIGH;
}
/******************************************************************************/
uint8_t BMP085_Oku8Bit(void)
{
	uint8_t x=0,i=0x80;	
	
		 do
			{
			 SCL_LOW;	
			  BMP085_Delay_1;		
			  if (Sda) x=(x)|i;
					 BMP085_Delay_1;
			 SCL_HIGH;
			 i>>=1;	
			  BMP085_Delay_1;
			}while(i!=0);
	SCL_LOW;	
  return x;
}
/******************************************************************************/
void BMP085_Gonder8Bit(uint8_t x)
{ 
		uint8_t i=0x80;
 do{
		 SCL_LOW;	
	    if (x&i)SDA_HIGH; 
	    else SDA_LOW; 
	 	  BMP085_Delay_1;
		 SCL_HIGH;	 
		 i>>=1;	
	    BMP085_Delay_1;
  }while(i!=0);
	SCL_LOW;	
}	  
/******************************************************************************/
void BMP085_AdresYaz8(uint8_t r, uint8_t v)
{
			BMP085_Start();	
			BMP085_Gonder8Bit(I2C_Adres);  // yaz
			if(BMP085_Ack())hata=1;
			BMP085_Gonder8Bit(r);
			if(BMP085_Ack())hata=1;
			BMP085_Gonder8Bit(v);
			BMP085_NAck();
			BMP085_Stop();

}
/******************************************************************************/
uint8_t BMP085_AdresOku8(uint8_t r)
{
  uint8_t v;

			BMP085_Gonder8Bit(I2C_Adres); // write byte
			if(BMP085_Ack())hata=1;
			BMP085_Gonder8Bit(r);
			if(BMP085_Ack())hata=1;	

			BMP085_Start();	
			BMP085_Gonder8Bit(I2C_Adres|0x1); // read byte
			if(BMP085_Ack())hata=1;
			v = BMP085_Oku8Bit();
			BMP085_NAck();
			BMP085_Stop();
	
  return v;
}

/*******************************************************************************/
int BMP085_AdresOku16(uint8_t r)
{
  uint8_t msb, lsb;
	
			BMP085_Start();	
			BMP085_Gonder8Bit(I2C_Adres);// write byte
			if(BMP085_Ack())hata=1;		
			BMP085_Gonder8Bit(r);
			if(BMP085_Ack())hata=1;	

			BMP085_Start();	
			BMP085_Gonder8Bit(I2C_Adres|0x1); // read byte
			if(BMP085_Ack())hata=1;	
			msb = BMP085_Oku8Bit();
			BMP085_MAck();
			lsb = BMP085_Oku8Bit();
			BMP085_NAck();
			BMP085_Stop();	
	
  return (((int)msb<<8) | ((int)lsb));
}
/******************************************************************************/
uint16_t BMP085_Isi_Oku() 
{
	uint16_t t=900; // the datasheet suggests 4.5 ms
	
			BMP085_AdresYaz8(0xF4,0x2e);
				
			while(t--)
				BMP085_Delay_2;
		
  return BMP085_AdresOku16(0xF6);
}
/******************************************************************************/
int32_t BMP085_Basinc_Oku()
{  
	uint8_t msb, lsb, xlsb;
	uint16_t t = (pressure_conversiontime[oversampling_setting])*175;
	
			BMP085_AdresYaz8(0xF4,0x34+(oversampling_setting<<6));

			while(t--)
				BMP085_Delay_2;
	
			BMP085_Start();	
      BMP085_Gonder8Bit(I2C_Adres); // write byte
			BMP085_Gonder8Bit(0xF6);  // register to read
      BMP085_Ack();

			BMP085_Start();	
			BMP085_Gonder8Bit(I2C_Adres|0x1); // read byte
			if(BMP085_Ack())hata=1;	
			 msb = BMP085_Oku8Bit();
			BMP085_MAck();
			lsb |= BMP085_Oku8Bit();
			BMP085_MAck();
			xlsb |= BMP085_Oku8Bit();
			BMP085_NAck();
			BMP085_Stop();		
	
  return (((long)msb<<16) | ((long)lsb<<8) | ((long)xlsb)) >>(8-oversampling_setting);
}									
/******************************************************************************/
void KalibrasyonData_Al(void)
{
		ac1 = BMP085_AdresOku16(0xAA);
		ac2 = BMP085_AdresOku16(0xAC);
		ac3 = BMP085_AdresOku16(0xAE);
		ac4 = BMP085_AdresOku16(0xB0);
		ac5 = BMP085_AdresOku16(0xB2);
		ac6 = BMP085_AdresOku16(0xB4);
		b1 = BMP085_AdresOku16(0xB6);
		b2 = BMP085_AdresOku16(0xB8);
		mb = BMP085_AdresOku16(0xBA);
		mc = BMP085_AdresOku16(0xBC);
		md = BMP085_AdresOku16(0xBE);
}
/******************************************************************************/
void BMP085_Hesapla(int16_t *isi, int32_t *basinc)
{
			int16_t  ut = BMP085_Isi_Oku();
			int32_t  up = BMP085_Basinc_Oku();
			int32_t  x1, x2, x3, b3, b5, b6, p;
			uint32_t b4, b7;

			//calculate true temperature
			x1 = ((int32_t)ut - (int32_t)ac6) * (int32_t)ac5 >> 15;
			x2 = ((int32_t) mc << 11) / (x1 + md);
			b5 = x1 + x2;
			*isi = (b5 + 8) >> 4;

			//calculate true pressure
			b6 = b5 - 4000;
			x1 = (b2 * (b6 * b6 >> 12)) >> 11; 
			x2 = ac2 * b6 >> 11;
			x3 = x1 + x2;
			b3 = (((((int32_t) ac1 << 2) + x3) << oversampling_setting) + 2) >> 2; // + ya parantez ekledim kontrol et 
			x1 = ac3 * b6 >> 13;
			x2 = (b1 * (b6 * b6 >> 12)) >> 16;
			x3 = ((x1 + x2) + 2) >> 2;
			b4 = (ac4 * (uint32_t) (x3 + 32768)) >> 15;
			b7 = (uint32_t)((uint32_t) up - b3) * (50000 >> oversampling_setting);
			p = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;

			x1 = (p >> 8) * (p >> 8);
			x1 = (x1 * 3038) >> 16;
			x2 = (-7357 * p) >> 16;
			*basinc = p + ((x1 + x2 + 3791) >> 4);
}
/*****************************************************************************/
uint8_t BMP085_Oku(int16_t *isi,int32_t *basinc)
{
	int16_t isi_h=0;
	int32_t basinc_h=0;
	
  disableInterrupts() 

	hata=0;
  KalibrasyonData_Al();
	BMP085_Hesapla(&isi_h,&basinc_h);
	
	*isi=isi_h;
	*basinc=basinc_h;	

  enableInterrupts();	
	
	return hata;
	
}
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/
