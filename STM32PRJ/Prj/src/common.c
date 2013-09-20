/**
  ******************************************************************************
  * @file    common.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    14-Aralik-2012
  * @brief   usart haberlesme fonksiyonlari  
  ******************************************************************************
  * @copy
  */
 
/* Includes ------------------------------------------------------------------*/

#include "common.h"
#include "extern_reg.c"

#define  SCANF_TIMEOUT  2000    // 10ms  ( 9600 için 1ms 115k için 8us de almasi gerekir. )
#define  PRINTF_TIMEOUT 2000	  // 10ms  ( 9600 için 1ms 115k için 8us de göndermesi gerekir. )


/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/**
  * @brief  Convert a string to an integer
  * @param  inputstr: The string to be converted
  * @param  intnum: The integer value
  * @retval 1: Correct
  *         0: Error
  */
uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum)
{
  uint32_t i = 0, res = 0;
  uint32_t val = 0;

  if (inputstr[0] == '0' && (inputstr[1] == 'x' || inputstr[1] == 'X'))
  {
    if (inputstr[2] == '\0')
    {
      return 0;
    }
    for (i = 2; i < 11; i++)
    {
      if (inputstr[i] == '\0')
      {
        *intnum = val;
        /* return 1; */
        res = 1;
        break;
      }
      if (ISVALIDHEX(inputstr[i]))
      {
        val = (val << 4) + CONVERTHEX(inputstr[i]);
      }
      else
      {
        /* Return 0, Invalid input */
        res = 0;
        break;
      }
    }
    /* Over 8 digit hex --invalid */
    if (i >= 11)
    {
      res = 0;
    }
  }
  else /* max 10-digit decimal input */
  {
    for (i = 0;i < 11;i++)
    {
      if (inputstr[i] == '\0')
      {
        *intnum = val;
        /* return 1 */
        res = 1;
        break;
      }
      else if ((inputstr[i] == 'k' || inputstr[i] == 'K') && (i > 0))
      {
        val = val << 10;
        *intnum = val;
        res = 1;
        break;
      }
      else if ((inputstr[i] == 'm' || inputstr[i] == 'M') && (i > 0))
      {
        val = val << 20;
        *intnum = val;
        res = 1;
        break;
      }
      else if (ISVALIDDEC(inputstr[i]))
      {
        val = val * 10 + CONVERTDEC(inputstr[i]);
      }
      else
      {
        /* return 0, Invalid input */
        res = 0;
        break;
      }
    }
    /* Over 10 digit decimal --invalid */
    if (i >= 11)
    {
      res = 0;
    }
  }

  return res;
}
/****************************************************************************/
void Int2Str(uint8_t* str, int32_t intnum)
{
  uint32_t i, Div = 1000000000, j = 0, Status = 0;

  for (i = 0; i < 10; i++)
  {
    str[j++] = (intnum / Div) + 48;

    intnum = intnum % Div;
    Div /= 10;
    if ((str[j-1] == '0') & (Status == 0))
    {
      j = 0;
    }
    else
    {
      Status++;
    }
  }
	 for (i = 0; i < 10; i++)
  {
		if(str[i]>0x3A)str[i]=0;
	}
	
}
/****************************************************************************/
int fputc(int ch, FILE *f)
{
//		Time_Out_Usart = PRINTF_TIMEOUT;
	
    USART_SendData(Sel_Com, (uint8_t) ch);
		/* Seçilen usart dan byte gönderilmesi bekleniyor */
	
    while (USART_GetFlagStatus(Sel_Com, USART_FLAG_TC) == RESET)
		{
//		if(!Time_Out_Usart)return EOF; 
//		Time_Out_Usart--;		
		}
		
    return ch;
}
/****************************************************************************/
int fgetc(FILE *f)
{
//		Time_Out_Usart = SCANF_TIMEOUT;
		/* Seçilen usart dan byte gelmesi bekleniyor */
		
    while (USART_GetFlagStatus(Sel_Com, USART_FLAG_RXNE) == RESET)
		{
//		if(!Time_Out_Usart)return EOF; 
//		Time_Out_Usart--;	
		}

    return (int)USART_ReceiveData(Sel_Com);
}

/****************************************************************************/
void Usart_Init(COM_TypeDef COM ,uint32_t baud)
{
		USART_InitTypeDef USART_InitStructure;
	
		USART_InitStructure.USART_BaudRate = baud;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		COM_Init(COM, &USART_InitStructure);
	
		if(COM==Gsm_Com)Sel_Com=Gsm_Com_Source;	
	
}
/****************************************************************************/
void Ram_Islem_Com_Init(void)
{
			NVIC_InitTypeDef NVIC_InitStructure;
		  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			/* Time base configuration */
			TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
			TIM_TimeBaseStructure.TIM_Period = 1;          
			TIM_TimeBaseStructure.TIM_Prescaler = 40000;       
		//	TIM_TimeBaseStructure.TIM_ClockDivision = 0xFF;    
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
			TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

			/* TIM5 enable counter */
			TIM_SetCounter(TIM5,0);
			
		  TIM_Cmd(TIM5, ENABLE);
	
			/* Enable the timer Interrupt */
			NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);	

			TIM_ITConfig(TIM5,TIM_IT_Update, ENABLE);
	
				/* Enable the USART2 Interrupt */
			NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);			
	
			Usart_Init(Optik_Com,115200);
	
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	
	
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
