/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32l1xx_i2c_ee.c
* Author             : Coskun ERGAN
* Version            : V1.0.1
* Date               : 30/Kasim/212
* Description        : 24Cxx Eeprom Haberleþme Kütüpanesi
********************************************************************************
	I2Cx kadar kurulabilir.
	
	pin tanýmlamalari board kütüpanesinde yapýlmalýdýr.
	
	örnek:
	_________________________________________________________
			
#define sEE_I2C                          I2C2
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C2
   
#define sEE_I2C_SCL_PIN                  GPIO_Pin_10                  
#define sEE_I2C_SCL_PORT                 GPIOB                     
#define sEE_I2C_SCL_CLK                  RCC_AHBPeriph_GPIOB
#define sEE_I2C_SCL_SOURCE               GPIO_PinSource10
#define sEE_I2C_SCL_AF                   GPIO_AF_I2C2

#define sEE_I2C_SDA_PIN                  GPIO_Pin_11                
#define sEE_I2C_SDA_PORT                 GPIOB                     
#define sEE_I2C_SDA_CLK                  RCC_AHBPeriph_GPIOB
#define sEE_I2C_SDA_SOURCE               GPIO_PinSource11
#define sEE_I2C_SDA_AF                   GPIO_AF_I2C2

#define E2prom_Kbit            512				// eeprom boyutu
#define I2C_Speed              50000      // haberleþme hýzý
#define TimeOut_I2c_Ee         50000      // zaman aþýmý süresi		
#define I2Cx_SLAVE_ADDRESS7    0xA0       // eeprom adresi	

*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "stm32l1xx_i2c_ee.h" 


#if E2prom_Kbit==1
	#define PAGE_SIZE 8
	#define SIZE 0x007f
#elif E2prom_Kbit==2
	#define PAGE_SIZE 8
	#define SIZE 0x00ff
#elif E2prom_Kbit==4
	#define PAGE_SIZE 16
	#define SIZE 0x01ff
#elif E2prom_Kbit==8
	#define PAGE_SIZE 16
	#define SIZE 0x03ff
#elif E2prom_Kbit==16
	#define PAGE_SIZE 16
	#define SIZE 0x07ff
#elif E2prom_Kbit==32
	#define PAGE_SIZE 32
	#define SIZE 0x0fff
#elif E2prom_Kbit==64
	#define PAGE_SIZE 32
	#define SIZE 0x1fff
#elif E2prom_Kbit==128
	#define PAGE_SIZE 64
	#define SIZE 0x3fff
#elif E2prom_Kbit==256
	#define PAGE_SIZE 64
	#define SIZE 0x7fff
#elif E2prom_Kbit==512
	#define PAGE_SIZE 128
	#define SIZE 0xffff
#endif

#define I2C_PageSize	          PAGE_SIZE


/* EEPROM Addresses defines */
#define EEPROM_Block0_ADDRESS 0xA0   /* E2 = 0 */
//#define EEPROM_Block1_ADDRESS 0xA2 /* E2 = 0 */
//#define EEPROM_Block2_ADDRESS 0xA4 /* E2 = 0 */
//#define EEPROM_Block3_ADDRESS 0xA6 /* E2 = 0 */


/* Private variables ---------------------------------------------------------*/
uint16_t EEPROM_ADDRESS;
uint32_t to;

/* Private function prototypes -----------------------------------------------*/
void GPIO_I2C_Configuration(void);
void I2C_Configuration(void);

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configure the used I/O ports pin
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_I2C_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

  
  /*!< sEE_I2C_SCL_GPIO_CLK and sEE_I2C_SDA_GPIO_CLK Periph clock enable */
  RCC_AHBPeriphClockCmd(sEE_I2C_SCL_CLK | sEE_I2C_SDA_CLK, ENABLE);
  
  /* Connect PXx to I2C_SCL*/
  GPIO_PinAFConfig(sEE_I2C_SCL_PORT, sEE_I2C_SCL_SOURCE, sEE_I2C_SCL_AF);
  
  /* Connect PXx to I2C_SDA*/
  GPIO_PinAFConfig(sEE_I2C_SDA_PORT, sEE_I2C_SDA_SOURCE, sEE_I2C_SDA_AF);
  
  /*!< GPIO configuration */  
  /*!< Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = sEE_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_Init(sEE_I2C_SCL_PORT, &GPIO_InitStructure);
  
  /*!< Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = sEE_I2C_SDA_PIN;
  GPIO_Init(sEE_I2C_SDA_PORT, &GPIO_InitStructure); 	


}

/*******************************************************************************
* Function Name  : I2C_Configuration
* Description    : I2C Configuration
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_Configuration(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 
	
	
	  /*!< sEE_I2C Periph clock enable */
	RCC_APB1PeriphClockCmd(sEE_I2C_CLK, ENABLE);
	
  /* I2C configuration */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = I2Cx_SLAVE_ADDRESS7;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  
  /* I2C Peripheral Enable */
  I2C_Cmd(sEE_I2C, ENABLE);
  /* Apply I2C configuration after enabling it */
  I2C_Init(sEE_I2C, &I2C_InitStructure);
}

/*******************************************************************************
* Function Name  : I2C_EE_Init
* Description    : Initializes peripherals used by the I2C EEPROM driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_EE_Init(void)
{
  /* GPIO configuration */
  GPIO_I2C_Configuration();

  /* I2C configuration */
  I2C_Configuration();

  /* depending on the EEPROM Address selected in the i2c_ee.h file */
#ifdef EEPROM_Block0_ADDRESS
  /* Select the EEPROM Block0 to write on */
  EEPROM_ADDRESS = EEPROM_Block0_ADDRESS;
#endif
#ifdef EEPROM_Block1_ADDRESS
  /* Select the EEPROM Block1 to write on */
  EEPROM_ADDRESS = EEPROM_Block1_ADDRESS;
#endif
#ifdef EEPROM_Block2_ADDRESS
  /* Select the EEPROM Block2 to write on */
  EEPROM_ADDRESS = EEPROM_Block2_ADDRESS;
#endif
#ifdef EEPROM_Block3_ADDRESS
  /* Select the EEPROM Block3 to write on */
  EEPROM_ADDRESS = EEPROM_Block3_ADDRESS;
#endif
}

/*******************************************************************************
* Function Name  : I2C_EE_BufferWrite
* Description    : Writes buffer of data to the I2C EEPROM.
* Input          : - pBuffer : pointer to the buffer  containing the data to be 
*                    written to the EEPROM.
*                  - WriteAddr : EEPROM's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the EEPROM.
* Output         : None
* Return         : None
*******************************************************************************/
char I2C_EE_BufferWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;

  Addr = WriteAddr % I2C_PageSize;
  count = I2C_PageSize - Addr;
  NumOfPage =  NumByteToWrite / I2C_PageSize;
  NumOfSingle = NumByteToWrite % I2C_PageSize;
 
  /* If WriteAddr is I2C_PageSize aligned  */
  if(Addr == 0) 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage == 0) 
    {
      if(I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle))return 1;
      if(I2C_EE_WaitEepromStandbyState())return 1;
    }
    /* If NumByteToWrite > I2C_PageSize */
    else  
    {
      while(NumOfPage--)
      {
        if(I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize))return 1; 
    	  if(I2C_EE_WaitEepromStandbyState())return 1;
        WriteAddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;
      }

      if(NumOfSingle!=0)
      {
        if(I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle))return 1;
        if(I2C_EE_WaitEepromStandbyState())return 1;
      }
    }
  }
  /* If WriteAddr is not I2C_PageSize aligned  */
  else 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage== 0) 
    {
      if(I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle))return 1;
      if(I2C_EE_WaitEepromStandbyState())return 1;
    }
    /* If NumByteToWrite > I2C_PageSize */
    else
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / I2C_PageSize;
      NumOfSingle = NumByteToWrite % I2C_PageSize;	
      
      if(count != 0)
      {  
        if(I2C_EE_PageWrite(pBuffer, WriteAddr, count))return 1;
        if(I2C_EE_WaitEepromStandbyState())return 1;
        WriteAddr += count;
        pBuffer += count;
      } 
      
      while(NumOfPage--)
      {
        if(I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize))return 1;
        if(I2C_EE_WaitEepromStandbyState())return 1;
        WriteAddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;  
      }
      if(NumOfSingle != 0)
      {
        if(I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle))return 1;
        if(I2C_EE_WaitEepromStandbyState())return 1;
      }
    }
  }
		return 0;
}

/*******************************************************************************
* Function Name  : I2C_EE_PageWrite
* Description    : Writes more than one byte to the EEPROM with a single WRITE
*                  cycle. The number of byte can't exceed the EEPROM page size.
* Input          : - pBuffer : pointer to the buffer containing the data to be 
*                    written to the EEPROM.
*                  - WriteAddr : EEPROM's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the EEPROM.
* Output         : None
* Return         : None
*******************************************************************************/
char I2C_EE_PageWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t NumByteToWrite)
{
	
		to=TimeOut_I2c_Ee;
    while(I2C_GetFlagStatus(sEE_I2C, I2C_FLAG_BUSY))if(!to)return 1; else to--;
    
  /* Send START condition */
  I2C_GenerateSTART(sEE_I2C, ENABLE);
  
  /* Test on EV5 and clear it */
	to=TimeOut_I2c_Ee;
  while(!I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_MODE_SELECT))if(!to)return 1; else to--;
  
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(sEE_I2C, EEPROM_ADDRESS, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
	to=TimeOut_I2c_Ee;
  while(!I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))if(!to)return 1; else to--; 

  #if E2prom_Kbit >16
		I2C_SendData(sEE_I2C,WriteAddr>>8);			//????
		  /* Test on EV8 and clear it */
			to=TimeOut_I2c_Ee;
  		while(! I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))if(!to)return 1; else to--;
  #endif

  /* Send the EEPROM's internal address to write to */    
  I2C_SendData(sEE_I2C, WriteAddr&0x00ff);  

  /* Test on EV8 and clear it */
	to=TimeOut_I2c_Ee;
  while(! I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))if(!to)return 1; else to--;

  /* While there is data to be written */
  while(NumByteToWrite--)  
  {
    /* Send the current byte */
    I2C_SendData(sEE_I2C, *pBuffer); 

    /* Point to the next byte to be written */
    pBuffer++; 
  
    /* Test on EV8 and clear it */
		to=TimeOut_I2c_Ee;
    while (!I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))if(!to)return 1; else to--;
  }

  /* Send STOP condition */
  I2C_GenerateSTOP(sEE_I2C, ENABLE);
	
		return 0;
}

/*******************************************************************************
* Function Name  : I2C_EE_BufferRead
* Description    : Reads a block of data from the EEPROM.
* Input          : - pBuffer : pointer to the buffer that receives the data read 
*                    from the EEPROM.
*                  - ReadAddr : EEPROM's internal address to read from.
*                  - NumByteToRead : number of bytes to read from the EEPROM.
* Output         : None
* Return         : None
*******************************************************************************/
char I2C_EE_BufferRead(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead)
{  
  //*((u8 *)0x4001080c) |=0x80; 
		to=TimeOut_I2c_Ee;
    while(I2C_GetFlagStatus(sEE_I2C, I2C_FLAG_BUSY))if(!to)return 1; else to--;
  
  //I2C_EE_WaitEepromStandbyState();  
  /* Send START condition */
  I2C_GenerateSTART(sEE_I2C, ENABLE);
  //*((u8 *)0x4001080c) &=~0x80;
  
  /* Test on EV5 and clear it */
	to=TimeOut_I2c_Ee;
  while(!I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_MODE_SELECT))if(!to)return 1; else to--;

  /* Send EEPROM address for read */
  I2C_Send7bitAddress(sEE_I2C, EEPROM_ADDRESS, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
	to=TimeOut_I2c_Ee;
  while(!I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))if(!to)return 1; else to--;
  
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(sEE_I2C, ENABLE);

   #if e2prom >16
		I2C_SendData(sEE_I2C,ReadAddr>>8);			 
		  /* Test on EV8 and clear it */
			to=TimeOut_I2c_Ee;
  		while(! I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))if(!to)return 1; else to--;
  #endif
  /* Send the EEPROM's internal address to write to */
  I2C_SendData(sEE_I2C, ReadAddr&0x00FF);  

  /* Test on EV8 and clear it */
	to=TimeOut_I2c_Ee;
  while(!I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED))if(!to)return 1; else to--;
  
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(sEE_I2C, ENABLE);
  
  /* Test on EV5 and clear it */
	to=TimeOut_I2c_Ee;
  while(!I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_MODE_SELECT))if(!to)return 1; else to--;
  
  /* Send EEPROM address for read */
  I2C_Send7bitAddress(sEE_I2C, EEPROM_ADDRESS, I2C_Direction_Receiver);
  
  /* Test on EV6 and clear it */
	to=TimeOut_I2c_Ee;
  while(!I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))if(!to)return 1; else to--;
  
  /* While there is data to be read */
  while(NumByteToRead)  
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(sEE_I2C, DISABLE);
      
      /* Send STOP Condition */
      I2C_GenerateSTOP(sEE_I2C, ENABLE);
    }

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(sEE_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED))  
    {      
      /* Read a byte from the EEPROM */
      *pBuffer = I2C_ReceiveData(sEE_I2C);

      /* Point to the next location where the byte read will be saved */
      pBuffer++; 
      
      /* Decrement the read bytes counter */
      NumByteToRead--;        
    }   
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(sEE_I2C, ENABLE);
	return 0;
}

/*******************************************************************************
* Function Name  : I2C_EE_WaitEepromStandbyState
* Description    : Wait for EEPROM Standby state
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
char I2C_EE_WaitEepromStandbyState(void)      
{

	to=TimeOut_I2c_Ee;
  do
  {
		if(!to)return 1; else to--;
    /* Send START condition */
    I2C_GenerateSTART(sEE_I2C, ENABLE);
    /* Read I2C1 SR1 register */
    I2C_ReadRegister(sEE_I2C, I2C_Register_SR1);
    /* Send EEPROM address for write */
    I2C_Send7bitAddress(sEE_I2C, EEPROM_ADDRESS, I2C_Direction_Transmitter);
  }while(!(I2C_ReadRegister(sEE_I2C, I2C_Register_SR1) & 0x0002));
  
  /* Clear AF flag */
    I2C_ClearFlag(sEE_I2C, I2C_FLAG_AF);
    /* STOP condition */    
    I2C_GenerateSTOP(sEE_I2C, ENABLE); // Added by Najoua 27/08/2008
	
	return 0;
}

/************************END OF FILE******************************/
