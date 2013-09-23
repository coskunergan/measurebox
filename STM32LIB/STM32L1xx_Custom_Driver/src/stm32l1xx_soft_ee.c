/**
  ******************************************************************************
  * @file    stm32l1xx_soft_ee.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    13-Aralik-2012
  * @brief   Yazilimsal E2prom haberlesme kütüpanesi 
  *
	*  @verbatim
  ******************************************************************************
	*   Notlar;
	*
	*		
	*					
	******************************************************************************
	*
	*    Kullanmadan önce sirasiyla;
	*
	* 
  *
	******************************************************************************
	*@endverbatim
	*****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_soft_ee.h"


/******************************************************************************/
/***                      24C02A Read/write programý                        ***/
/******************************************************************************/
void Soft_Ee_Init_Pin(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
	
  RCC_AHBPeriphClockCmd(SOFT_I2C_SDA_CLK | SOFT_I2C_SCL_CLK, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin =  SOFT_I2C_SCL_PIN ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
  GPIO_Init(SOFT_I2C_SCL_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  SOFT_I2C_SDA_PIN ;
  GPIO_Init(SOFT_I2C_SDA_PORT, &GPIO_InitStructure);	
	
}
/******************************************************************************/
void ee_delay(void)
{  			
	uint32_t t;
	for(t=0;t<Soft_Ee_Delay;t++); 
}
/******************************************************************************/
void NoAck(void)
{
 SCL(0);                 
 ee_delay();
 SDA(1);
 TRIS_SDA(out);		
 ee_delay();
 SCL(1);
 ee_delay();			
 SCL(0);
 ee_delay();		

}
/******************************************************************************/
void Ack(void)
{
 SCL(0);                 
 ee_delay();
 SDA(0);
 TRIS_SDA(out);	
 ee_delay();
 SCL(1);
 ee_delay();			
 SCL(0);
 ee_delay();		

}
/******************************************************************************/
uint8_t WaitAck(void)
{ 
	SCL(0);                 
	ee_delay();
	TRIS_SDA(in);		
	ee_delay();
	SCL(1);
	ee_delay();
	
	if(Sda)
	{
    SCL(0);  
    return 1;
	}
	 SCL(0);  
	 return 0;
}
/******************************************************************************/
void start(void)
{
 SDA(1);
 SCL(1);	
	ee_delay();    
 TRIS_SDA(out);		
 SDA(0);
 ee_delay();           
}
/******************************************************************************/
void Gonder8Bit(unsigned char x)
{ 
 unsigned char i=0x80;

 do{
   SCL(0);
   TRIS_SDA(out);			
   ee_delay();
   if (x&i){ SDA(1);}
    else {SDA(0);}
   ee_delay();
   SCL(1);
   ee_delay();
   i>>=1;
  }while(i!=0);
}
/****************************************************************************/
void Oku8Bit(unsigned char *x)
{
	unsigned char i=0x80;

  TRIS_SDA(in);		
	*x=0;
 do
  {
   SCL(0);
   ee_delay();
   SCL(1);
   ee_delay();
   if (Sda) *x=(*x)|i;
   i>>=1;
  }while(i!=0);
  
  
}
/******************************************************************************/
uint8_t I2c_Read_512(uint8_t addres_h, uint8_t addres_l,uint8_t length,uint8_t * pBuffer)
{

	 Pin_High(Eep_Enb);
	   SCL(1);
		ee_delay();
		ee_delay();
		ee_delay();
    start();		 	

   Gonder8Bit(WRITE_CONTROL_BYTE);        

   if (WaitAck())  {Pin_Low(Eep_Enb); return(EE_FALSE);}
 
   Gonder8Bit(addres_h);       
 
   if (WaitAck())  {Pin_Low(Eep_Enb); return(EE_FALSE);}
 
	Gonder8Bit(addres_l);   

	 if (WaitAck())  {Pin_Low(Eep_Enb); return(EE_FALSE);}
	
		SCL(0);
		ee_delay();
		SCL(1);
		ee_delay();
		SDA(0);                  
		TRIS_SDA(out);		 			 
		ee_delay();             

		Gonder8Bit(READ_CONTROL_BYTE);         

		if (WaitAck())  {Pin_Low(Eep_Enb); return(EE_FALSE);}
   // length++; // saçmal1k what's wrong man
    while(length--)
    {
			Oku8Bit((uint8_t *)pBuffer);
			pBuffer++;
      if(length == 0)NoAck();
			else Ack();
    }

	SCL(0);                
	ee_delay();
	SDA(0);
	TRIS_SDA(out);		 	
	ee_delay();
	SCL(1);
	ee_delay();
	SDA(1);
	ee_delay();		
	SDA(0);
	SCL(0);	
	Pin_Low(Eep_Enb);
	return (EE_TRUE);

}
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
uint8_t I2c_Write_512( uint8_t addresH , uint8_t addresL,   uint16_t length , uint8_t* pBuffer)
{
		Pin_High(Eep_Enb);
		ee_delay();
		ee_delay();
		ee_delay();
  	start();		 	

   Gonder8Bit(WRITE_CONTROL_BYTE);          
 
   if (WaitAck())  {Pin_Low(Eep_Enb); return(EE_FALSE);} 	
 
   Gonder8Bit(addresH);     

   if (WaitAck())  {Pin_Low(Eep_Enb); return(EE_FALSE);} 
	
   Gonder8Bit(addresL);    

	 if (WaitAck())  {Pin_Low(Eep_Enb); return(EE_FALSE);} 

	 
    while(length--)
    {
			Gonder8Bit(*pBuffer); 
			pBuffer++;
			if (WaitAck())  {Pin_Low(Eep_Enb); return(EE_FALSE);} 
    }	

  
 		ee_delay();
		ee_delay();
		ee_delay();
		
  SCL(0);
  ee_delay(); 
  SDA(0);                  
  TRIS_SDA(out);		 		 
  ee_delay();
  SCL(1);
  ee_delay();
  SDA(1);
  ee_delay();
	DelayMs(10);
	SDA(0);
	SCL(0);
	Pin_Low(Eep_Enb);
  return(EE_TRUE);
}
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
