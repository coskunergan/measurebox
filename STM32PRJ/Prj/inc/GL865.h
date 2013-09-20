/**
  ******************************************************************************
  * @file    Header File 
  * @author  Coskun ERGAN
  * @version V1.0.0
  * @date    14-AraLik-2012
  * @brief   Bu Bir Hedeader dosyadir fonksiyonlari main'e baglar.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GL865_H
#define __GL865_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

////////////////////////////////////////////////////
//																								//
//    				   	  	GL865 Telit									//
//	 					  			Komutlar   					  			//
//																							 	//
////////////////////////////////////////////////////


#define AT  					"AT\r"
#define ATE0  				"ATE0\r"
#define ATK0  				"AT&K0\r"
#define ATCPIN				"AT+CPIN?\r" 
#define IP_GET        "AT#GPRS=1\r"
#define FTPTO         "AT#FTPTO=1000\r"  //timeout 1sn
#define ATFTPTYPE0    "AT#FTPTYPE=0\r"
#define ATFTPCLOSE    "AT#FTPCLOSE\r"
#define CLOSE_DATA_CONNECT    "+++"
#define ATCCLK        "AT+CCLK?\r"
#define ATMONI        "AT#MONI\r"
#define ATCBC					"AT+CBC\r"

////////////////////////////////////////////////////
//																								//
//    				   	  	GL865 Telit									//
//	 					  			Cevaplar   					  			//
//																							 	//
////////////////////////////////////////////////////


#define OK       "OK"
#define SIM_RDY  "+CPIN: READY"
#define CONNECT  "CONNECT"
#define COMMAND  "COMMAND("
#define NO_CARRIER  "NO CARRIER"
#define CCLK       "+CCLK: \""
#define MONI      "#MONI:"
#define FTPFSIZE   "#FTPFSIZE: "


/* Private variables ---------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint8_t Gsm_Rx_Wait(char * Quest_Buff, uint32_t time);
uint8_t CommandGsm(char * data,char * Quest_Buff, uint32_t time);
uint8_t Apn_AddressPut(uint32_t time);
uint8_t FTP_Login(uint32_t time);
uint8_t FTP_Close(uint32_t time);
uint8_t IP_Get(uint32_t time);
void Gsm_Reset(void);
uint8_t Gsm_Pwr_On(void);
void Gsm_Pwr_Off(void);
uint8_t Gsm_Pwr_Reset(void);
uint8_t Get_FtpLogFile_SizeOf(uint32_t time);
uint8_t Get_CommandToFile(void);
void Command_Work(uint8_t common);
void Check_Ftp_Firmware(void);
uint8_t Write_LogFile(void);
uint8_t Connect_FTP_File(void);
uint8_t Connect_FTP(void);
void Message_Show_Gprs(void);


#endif  /* __H */

/*******************(C)COPYRIGHT 2012 STMicroelectronics *****END OF FILE******/
