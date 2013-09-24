/**
  ******************************************************************************
  * @file    stm32l1xx_hd44780.c
  * @author  Coskun ERGAN
  * @version V1.0.4
  * @date    23-Eylül-2013
  * @brief   4x20 lcd kütüpanesi 
  *
	*  @verbatim
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hd44780.h"

/** @addtogroup lcd kütüpanesi
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//===============================================================================
//              ##### Initialization and Configuration functions #####
//===============================================================================

const char UserFont[8][8] = {  /* 8 user defined characters to be loaded into CGRAM (used for bargraph)*/
    { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
    { 0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10 },
    { 0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18 },
    { 0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C },
    { 0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E },
    { 0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F },
    { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
    { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }
};

//==========================================================================================
//
//==========================================================================================
void delay_us(int us)
{
		 long i, tus;
		 tus = 9*us;
		 for(i=0;i<tus;i++);
}
//==========================================================================================
//
//==========================================================================================
void LCD_SendByte(uint8_t cmd)
{
		 uint8_t tcmd = 0;

		 GPIO_SetBits(Lcd_E_Port, Lcd_E_Pin);

		 tcmd = cmd >> 4;
		 if( tcmd & 0x01 )GPIO_SetBits(Lcd_D4_Port, Lcd_D4_Pin);
		 else 					  GPIO_ResetBits(Lcd_D4_Port, Lcd_D4_Pin);
		 if( tcmd & 0x02 )GPIO_SetBits(Lcd_D5_Port, Lcd_D5_Pin);
		 else 					  GPIO_ResetBits(Lcd_D5_Port, Lcd_D5_Pin);
		 if( tcmd & 0x04 )GPIO_SetBits(Lcd_D6_Port, Lcd_D6_Pin);
		 else 					 GPIO_ResetBits(Lcd_D6_Port, Lcd_D6_Pin);
		 if( tcmd & 0x08 )GPIO_SetBits(Lcd_D7_Port, Lcd_D7_Pin);
		 else 					  GPIO_ResetBits(Lcd_D7_Port, Lcd_D7_Pin);	

		 GPIO_ResetBits(Lcd_E_Port, Lcd_E_Pin);
		 delay_us(50);
		 GPIO_SetBits(Lcd_E_Port, Lcd_E_Pin);

		 cmd &= 0x0F;
		 if( cmd & 0x01 )GPIO_SetBits(Lcd_D4_Port, Lcd_D4_Pin);
		 else 					 GPIO_ResetBits(Lcd_D4_Port, Lcd_D4_Pin);
		 if( cmd & 0x02 )GPIO_SetBits(Lcd_D5_Port, Lcd_D5_Pin);
		 else 					 GPIO_ResetBits(Lcd_D5_Port, Lcd_D5_Pin);
		 if( cmd & 0x04 )GPIO_SetBits(Lcd_D6_Port, Lcd_D6_Pin);
		 else 					 GPIO_ResetBits(Lcd_D6_Port, Lcd_D6_Pin);
		 if( cmd & 0x08 )GPIO_SetBits(Lcd_D7_Port, Lcd_D7_Pin);
		 else 					 GPIO_ResetBits(Lcd_D7_Port, Lcd_D7_Pin);	

		 GPIO_ResetBits(Lcd_E_Port, Lcd_E_Pin);
		/* GPIO_ResetBits(LCD_PORT_D4, LCD_D4);
		 GPIO_ResetBits(LCD_PORT_D5, LCD_D5);
		 GPIO_ResetBits(LCD_PORT_D6, LCD_D6);
		 GPIO_ResetBits(LCD_PORT_D7, LCD_D7); */
		 GPIO_ResetBits(Lcd_Rs_Port, Lcd_Rs_Pin);
		 delay_us(50);// <<<<<<<<< kalibre edilecek
}

//==========================================================================================
//
//==========================================================================================
void LCD_SendCmd(uint8_t cmd)
{
		 GPIO_ResetBits(Lcd_Rs_Port, Lcd_Rs_Pin);
		 delay_us(50);
		 LCD_SendByte(cmd);
}
//==========================================================================================
//
//==========================================================================================
void LCD_SendData(uint8_t data)
{
		 GPIO_SetBits(Lcd_Rs_Port, Lcd_Rs_Pin);
		 delay_us(50);
		 LCD_SendByte(data);
}

//==========================================================================================
//   print a string on LCD.
//==========================================================================================
void LCD_SendText(char *text)
{
		 while(*text)
		 {
			LCD_SendData(*text);
			text++;
		 }
}

//==========================================================================================
//   Clear the LCD display.
//==========================================================================================
void LCD_Clear(void)
{
		LCD_SendCmd(0x01);
}

//==========================================================================================
//   Set cursor position on LCD display.
//==========================================================================================
void LCD_GoTo (unsigned char line, unsigned char column)
{
		 uint8_t position = 0;

		 position = (line * 0x40) + column;
		 position = 0x80 + (position & 0x7F);

		 LCD_SendCmd(position);
}
//==========================================================================================
//  LCD low power mode active 
//==========================================================================================
void LCD_Lp_Off(void)
{
		 GPIO_SetBits(Lcd_Enb_Port, Lcd_Enb_Pin); // lcd off
		 GPIO_SetBits(Lcd_BL_Port, Lcd_BL_Pin);   // BL off
	
		 GPIO_ResetBits(Lcd_D4_Port, Lcd_D4_Pin);
		 GPIO_ResetBits(Lcd_D5_Port, Lcd_D5_Pin);
		 GPIO_ResetBits(Lcd_D6_Port, Lcd_D6_Pin);
		 GPIO_ResetBits(Lcd_D7_Port, Lcd_D7_Pin); 
		 GPIO_ResetBits( Lcd_E_Port, Lcd_E_Pin);	
		 GPIO_ResetBits(Lcd_Rs_Port, Lcd_Rs_Pin);	
}
//==========================================================================================
//   Initialize LCD pin.
//==========================================================================================
void LCD_Pin_Init(void)
{
			GPIO_InitTypeDef  GPIO_InitStructure;

			/* Enable the pins Clock */
			RCC_AHBPeriphClockCmd(Lcd_D7_Clk, ENABLE);
			RCC_AHBPeriphClockCmd(Lcd_D6_Clk, ENABLE);	
			RCC_AHBPeriphClockCmd(Lcd_D5_Clk, ENABLE);
			RCC_AHBPeriphClockCmd(Lcd_D4_Clk, ENABLE);
			RCC_AHBPeriphClockCmd(Lcd_Rs_Clk, ENABLE);
			RCC_AHBPeriphClockCmd(Lcd_E_Clk,  ENABLE);
			RCC_AHBPeriphClockCmd(Lcd_Enb_Clk,ENABLE);	
			RCC_AHBPeriphClockCmd(Lcd_BL_Clk, ENABLE);	

			/* Configure the pin */
			GPIO_InitStructure.GPIO_Pin = Lcd_D7_Pin;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
			GPIO_Init(Lcd_D7_Port, &GPIO_InitStructure);

			GPIO_InitStructure.GPIO_Pin = Lcd_D6_Pin;
			GPIO_Init(Lcd_D6_Port, &GPIO_InitStructure);

			GPIO_InitStructure.GPIO_Pin = Lcd_D5_Pin;
			GPIO_Init(Lcd_D5_Port, &GPIO_InitStructure);

			GPIO_InitStructure.GPIO_Pin = Lcd_D4_Pin;
			GPIO_Init(Lcd_D4_Port, &GPIO_InitStructure);
			
			GPIO_InitStructure.GPIO_Pin = Lcd_Rs_Pin;
			GPIO_Init(Lcd_Rs_Port, &GPIO_InitStructure);

			GPIO_InitStructure.GPIO_Pin = Lcd_E_Pin;
			GPIO_Init(Lcd_E_Port, &GPIO_InitStructure);

			GPIO_InitStructure.GPIO_Pin = Lcd_Enb_Pin;
			GPIO_Init(Lcd_Enb_Port, &GPIO_InitStructure);

			GPIO_InitStructure.GPIO_Pin = Lcd_BL_Pin;
			GPIO_Init(Lcd_BL_Port, &GPIO_InitStructure);
			
			GPIO_SetBits(Lcd_Enb_Port, Lcd_Enb_Pin); // lcd off
			GPIO_SetBits(Lcd_BL_Port, Lcd_BL_Pin);   // BL off
	
}
//==========================================================================================
//   Initialize the LCD.
//==========================================================================================
void LCD_Init(void)
{
		 uint8_t i;
		 char const *p;
		 GPIO_ResetBits(Lcd_Enb_Port, Lcd_Enb_Pin); // lcd on
		 GPIO_ResetBits(Lcd_BL_Port, Lcd_BL_Pin);   // BL on	
		 DelayMs(30);
		 GPIO_ResetBits(Lcd_Rs_Port, Lcd_Rs_Pin);
		 GPIO_ResetBits(Lcd_E_Port, Lcd_E_Pin);
		 for(i = 0; i<3; i++)
		 {
			 GPIO_SetBits(Lcd_E_Port, Lcd_E_Pin);
			 GPIO_SetBits(Lcd_D4_Port, Lcd_D4_Pin);
			 GPIO_SetBits(Lcd_D5_Port, Lcd_D5_Pin);	 
			 GPIO_ResetBits(Lcd_D6_Port, Lcd_D6_Pin);
			 GPIO_ResetBits(Lcd_D7_Port, Lcd_D7_Pin);	 
			 GPIO_ResetBits(Lcd_E_Port, Lcd_E_Pin);
		 }
		 GPIO_SetBits(Lcd_E_Port, Lcd_E_Pin);
		 DelayMs(50);
		 GPIO_ResetBits(Lcd_D4_Port, Lcd_D4_Pin);
		 GPIO_SetBits(Lcd_D5_Port, Lcd_D5_Pin);
		 GPIO_ResetBits(Lcd_D6_Port, Lcd_D6_Pin);
		 GPIO_ResetBits(Lcd_D7_Port, Lcd_D7_Pin);	
		 DelayMs(50);
		 GPIO_ResetBits(Lcd_E_Port, Lcd_E_Pin);
		 LCD_SendCmd(0x28);
		 LCD_SendCmd(0x08);
		 LCD_SendCmd(0x01);
		 LCD_SendCmd(0x06);
		 LCD_SendCmd(0x0C); //
		 DelayMs(10);

		 /* Load user-specific characters into CGRAM                               */
		 LCD_SendCmd(0x40);                  /* Set CGRAM address counter to 0     */
		 p = &UserFont[0][0];
		 for (i = 0; i < sizeof(UserFont); i++, p++)
			LCD_SendData (*p);
			LCD_SendCmd(0x80);                 /* Set DDRAM address counter to 0     */
}

/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/
