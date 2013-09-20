/**
  ******************************************************************************
  * @file    boot_ram.c
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    20 Mart 2013
  * @brief   bootloader yaziliminin ramde kosacak kismi
  ******************************************************************************
  * @copy
  */
 
/* Includes ------------------------------------------------------------------*/

#include <stm32l1xx.h>


#define Bank2_Baslangic_Adresi   (uint32_t)0x08030000
#define Bank1_Baslangic_Adresi   (uint32_t)0x08000000 

#define Bank2_Bitis_Adresi   0x0805FF00
#define Bank1_Bitis_Adresi   0x0802FFFF

#define FLASH_PAGE_SIZE               0x100     /* 256 Bytes */
#define FLASH_ER_PRG_TIMEOUT         ((uint32_t)0x8000)


//RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
//RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
//RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR

static __RAM_FUNC GetStatus(void)
{
  FLASH_Status FLASHstatus = FLASH_COMPLETE;
  
  if((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) 
  {
    FLASHstatus = FLASH_BUSY;
  }
  else 
  {  
    if((FLASH->SR & (uint32_t)FLASH_FLAG_WRPERR)!= (uint32_t)0x00)
    { 
      FLASHstatus = FLASH_ERROR_WRP;
    }
    else 
    {
      if((FLASH->SR & (uint32_t)0x1E00) != (uint32_t)0x00)
      {
        FLASHstatus = FLASH_ERROR_PROGRAM; 
      }
      else
      {
        FLASHstatus = FLASH_COMPLETE;
      }
    }
  }
  /* Return the FLASH Status */
  return FLASHstatus;
}


//RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
//RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
//RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR

__RAM_FUNC FLASH_If_Write_Ram(__IO uint32_t* FlashAddress, uint32_t* Data ,uint16_t DataLength)
{
  FLASH_Status status = FLASH_BUSY;
  uint32_t* malPointer = (uint32_t *)Data;
  uint32_t memBuffer[32]; /* Temporary buffer holding data that will be written in a half-page space */
  uint32_t* mempBuffer = memBuffer;
  uint32_t i = 0;

  while (malPointer < (uint32_t*)(Data + DataLength))
  {
    /* Fill with the received buffer */
    while (mempBuffer < (memBuffer + 32))
    {
      /* If there are still data available in the received buffer */
      if (malPointer < ((uint32_t *)Data + DataLength))
      {
        *(uint32_t *)(mempBuffer++) = *(uint32_t *)(malPointer++);
      }
      else /* no more data available in the received buffer: fill remaining with dummy 0 */
      {
        *(uint32_t *)(mempBuffer++) = 0;
      }
    }

    /* Write the buffer to the memory */
    status = FLASH_ProgramHalfPage(*FlashAddress, (uint32_t *)(memBuffer));
  
    if (status != FLASH_COMPLETE)
    {
      /* Error occurred while writing data in Flash memory */
      return (1);
    }

    /* Check if flash content matches memBuffer */
    for (i = 0; i < 32; i++)
    {
      if ((*(uint32_t*)(*(uint32_t*)FlashAddress + 4 * i)) != memBuffer[i])
      {
        /* flash content doesn't match memBuffer */
        return(2);
      }
    }

    /* Increment the memory pointer */
    *FlashAddress += 128;

    /* Reinitialize the intermediate buffer pointer */
    mempBuffer = memBuffer;
  }

  return (0);
}

//RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
//RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
//RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR

__RAM_FUNC Bellek_Yukleyici(void)
{
	
	 uint32_t flashaddress,status,Timeout;
	 uint32_t * ptr;

///////////////////////////  BANK-1 i FORTMATLA ///////////////////////////////	
  flashaddress = Bank1_Baslangic_Adresi;
  
  while (flashaddress <= (uint32_t) Bank1_Bitis_Adresi)
  {
 
		  /* Check for the FLASH Status */
		status = GetStatus();
  
		Timeout=0x8000;
		/* Wait for a FLASH operation to complete or a TIMEOUT to occur */
		while((status == FLASH_BUSY) && (Timeout != 0x00))
		{
    status = GetStatus();
    Timeout--;
		}
		
    /* Set the ERASE bit */
    FLASH->PECR |= FLASH_PECR_ERASE;

    /* Set PROG bit */
    FLASH->PECR |= FLASH_PECR_PROG;
  
    /* Write 00000000h to the first word of the program page to erase */
    *(__IO uint32_t *)flashaddress = 0x00000000;
 
		
		  /* Check for the FLASH Status */
		status = GetStatus();
		Timeout=0x8000;
		/* Wait for a FLASH operation to complete or a TIMEOUT to occur */
		while((status == FLASH_BUSY) && (Timeout != 0x00))
		{
    status = GetStatus();
    Timeout--;
		}
		
    /* If the erase operation is completed, disable the ERASE and PROG bits */
    FLASH->PECR &= (uint32_t)(~FLASH_PECR_PROG);
    FLASH->PECR &= (uint32_t)(~FLASH_PECR_ERASE);   

    flashaddress += FLASH_PAGE_SIZE;

  }
/////////////////////// BANK-2 yi BANK-1 E yükle ////////////////////////////	
	
	flashaddress =0x08000000; // bank 1 baslangic
  ptr =(uint32_t *) 0x08030000; // bank 2 baslangic
	
	while(flashaddress<=Bank1_Bitis_Adresi){
		
	FLASH_If_Write_Ram(&flashaddress,ptr,(uint16_t)256);
		ptr+=256;
	}
	
/////////////////////////// iSLEMCiYi RESETLE ///////////////////////////////	
	 __DSB();
  SCB->AIRCR  = ((0x5FA << SCB_AIRCR_VECTKEY_Pos)      |
                 (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
                 SCB_AIRCR_SYSRESETREQ_Msk);                   /* Keep priority group unchanged */
  __DSB();                                                     /* Ensure completion of memory access */
  while(1);                                                    /* wait until reset */
	
}	

//RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
//RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
//RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
#if defined (  __TASKING__  )
#pragma section_code_init on
#endif


