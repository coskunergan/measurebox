
#include <stm32l1xx.h>

#ifndef __LCD_DEFINE_H
#define __LCD_DEFINE_H

#ifdef __cplusplus
 extern "C" {
#endif 
	 
	 
#define intro1  "KGS Meters     "	 
#define intro2    Version	  	 
	 
#define SPACE   "                "
	 
#define LangN  2
////////////////////////////////////////////////////
//																								//
//    				   	    English							 				//
//	 					       Messasges			        			//
//																							 	//
////////////////////////////////////////////////////
//------------  Menu Messages ---------------
#define _REST_BALANCE " REST BALANCE " 
#define _TOTAL_INDEX  "  TOTAL INDEX "
#define _VALVE_OPEN   "  VALVE OPEN  "	 
#define _VALVE_CLOSE  "  VALVE CLOSE " 
#define _PULSE_FINE   "  PULSE FINE  "	 
#define _NO_BALANCE   "  NO BALANCE  "	
#define _SERIAL_NO    "   METER NO:  "	 
#define _NO_CARD			"   NO CARD    " 
#define _VALVE_ERROR  "  VALVE ERROR!"	  
#define _NO_OPEN			"   NO OPEN    "	
#define _NO_CLOSE     "   NO CLOSE   "	 
#define _VALVE				"    VALVE     "	
#define _CLOSING   	 	"   CLOSING    "	 
#define _OPENING      "   OPENING    "	 
//------------ CARD MESSAGES ---------------
#define _OPEN_VALVE   " OPEN VALVE   "
#define _CLOSE_VALVE  " CLOSE VALVE  "
#define _COMMAND_CARD "COMMAND->CARD "
#define _CARD_READ    "  CARD READ   "
//------------ GPRS MESSAGES ---------------
#define _GPRS					"    GPRS      "
#define _CONNECTION   " CONNECTION   "
#define _FTP_READY    "    READY     "
#define _COMPLETE     "  COMPLETE    "
#define _COMMAND_GPRS "COMMAND->GPRS "
#define _CREDIT_LOAD  " CREDIT LOAD  "
////////////////////////////////////////////////////
//																								//
//    				   	  	Türkçe							 				//
//	 					       Mesajlar				        			//
//																							 	//
////////////////////////////////////////////////////	
//------------  Menu ekran ----------------
#define _KALAN_BAKIYE "  KALAN KREDi "
#define _TOPLAM_ENDEX "  ANA TüKETiM "
#define _VALF_ACIK    "  VALF AÇIK   "	 
#define _VALF_KAPALI  "  VALF KAPALI "		 
#define _PALS_CEZALI  "  PALS CEZALI "	 
#define _BAKIYE_YOK   "  BAKiYE YOK  "	
#define _SERI_NO      "  SAYAÇ NO:   "	 
#define _KART_YOK     "   KART YOK   "	 
#define _VALF_HATA    "  HATA! VALF  "	 
#define _ACILAMADI    "  AÇILAMADI   "	
#define _KAPATILAMADI " KAPATILAMADI "	
#define _VALF				  "     VALF     "	
#define _ACILIYOR			"   AÇILIYOR   "
#define _KAPATILIYOR  "  KAPATILIYOR "
//------------ CARD MESSAGES ---------------
#define _VALF_AC      "   VALF AÇ    "
#define _VALF_KAPAT   "  VALF KAPAT  "
#define _KOMUT_KART   "  KOMUT->KART "
#define _KART_OKUMA   "  KART OKUMA  "
//------------ GPRS MESSAGES ---------------
#define _BAGLANIYOR   " BAGLANILIYOR "
#define _BAGLANDI     "   BAGLANDI   "
#define _FTP_HAZIR    "    HAZIR     "
#define _BAGLANTI     "   BAGLANTI   "
#define _TAMAMLANDI   "  TAMAMLANDI  "
#define _KOMUT_GPRS   "  KOMUT->GPRS "
#define _KREDI_YUK    "  KREDi YüKL. "
////////////////////////////////////////////////////
//																								//
//    				   	  Mesaj Status		  	 	 				//
//	 					      GPRS & CARD			        			//
//																							 	//
////////////////////////////////////////////////////

extern uint32_t Message_Status_Gprs;	
	 
#define  Mgprs_Info			   				 Message_Status_Gprs|=0x00000001		 
#define  Mgprs_Valf_Off   				 Message_Status_Gprs|=0x00000002	 
#define  Mgprs_Valf_On   		   	 	 Message_Status_Gprs|=0x00000004	 
#define  Mgprs_Endex_Change    	 	 Message_Status_Gprs|=0x00000008	 
#define  Mgprs_Buzzer_On   				 Message_Status_Gprs|=0x00000010	 
#define  Mgprs_Buzzer_Off   			 Message_Status_Gprs|=0x00000020	 
#define  Mgprs_Connect_Time_Change Message_Status_Gprs|=0x00000040	
#define  Mgprs_Connect_Error	  	 Message_Status_Gprs|=0x00000080	
#define  Mgprs_Error_Clear	    	 Message_Status_Gprs|=0x00000100
#define  Mgprs_Connect_Day_Change  Message_Status_Gprs|=0x00000200
#define  Mgprs_Balance_Change    	 Message_Status_Gprs|=0x00000400	 
#define  Mgprs_Debt_Change    	 	 Message_Status_Gprs|=0x00000800	 
#define  Mgprs_Credit_Load    	 	 Message_Status_Gprs|=0x00001000	 
#define  Mgprs_Connect_Change  	 	 Message_Status_Gprs|=0x00002000	 
#define  Mgprs_Serial_Change  		 Message_Status_Gprs|=0x00004000	
#define  Mgprs_Divider_Change  		 Message_Status_Gprs|=0x00008000	
#define  Mgprs_Close_Change  		   Message_Status_Gprs|=0x00010000
#define  Mgprs_Sim_Error    		   Message_Status_Gprs|=0x00020000
#define  Mgprs_Institu_Change			 Message_Status_Gprs|=0x00040000
#define  Mgprs_Apn_Change			     Message_Status_Gprs|=0x00080000
#define  Mgprs_Dom_Change			     Message_Status_Gprs|=0x00100000
#define  Mgprs_User_Change			   Message_Status_Gprs|=0x00200000
#define  Mgprs_Pass_Change			   Message_Status_Gprs|=0x00400000
#define  Mgprs_Language_Change		 Message_Status_Gprs|=0x00800000
#define  Mgprs_SetTime						 Message_Status_Gprs|=0x01000000
#define  Mgprs_BaylanNo_Change		 Message_Status_Gprs|=0x02000000

extern uint32_t Message_Status_Card;		 

#define  Mcard_Info			   				 Message_Status_Gprs|=0x00000001	
#define  Mcard_Valf_Off   		   	 Message_Status_Card|=0x00000002 	 
#define  Mcard_Valf_On    				 Message_Status_Card|=0x00000004	  
#define  Mcard_Endex_Change    	 	 Message_Status_Card|=0x00000008	 
#define  Mcard_Buzzer_On   				 Message_Status_Card|=0x00000010	 
#define  Mcard_Buzzer_Off   			 Message_Status_Card|=0x00000020	 
#define  Mcard_Connect_Time_Change Message_Status_Card|=0x00000040	
#define  Mcard_Connect_Error	  	 Message_Status_Card|=0x00000080	
#define  Mcard_Error_Clear	    	 Message_Status_Card|=0x00000100
#define  Mcard_Connect_Day_Change  Message_Status_Card|=0x00000200
#define  Mcard_Balance_Change    	 Message_Status_Card|=0x00000400	 
#define  Mcard_Debt_Change    	 	 Message_Status_Card|=0x00000800	 
#define  Mcard_Credit_Load    	 	 Message_Status_Card|=0x00001000	 
#define  Mcard_Connect_Change  	 	 Message_Status_Card|=0x00002000	 
#define  Mcard_Serial_Change  		 Message_Status_Card|=0x00004000	
#define  Mcard_Divider_Change  		 Message_Status_Card|=0x00008000	
#define  Mcard_Close_Change  		   Message_Status_Card|=0x00010000

#define  Mcard_No_Card   			  	 Message_Status_Card|=0x00020000	
#define  Mcard_Undefined_SN_Card   Message_Status_Card|=0x00040000

#define  Mcard_Institu_Change			 Message_Status_Card|=0x00080000
#define  Mcard_Apn_Change			     Message_Status_Card|=0x00100000
#define  Mcard_Dom_Change			     Message_Status_Card|=0x00200000
#define  Mcard_User_Change			   Message_Status_Card|=0x00400000
#define  Mcard_Pass_Change			   Message_Status_Card|=0x00800000
#define  Mcard_Language_Change	   Message_Status_Card|=0x01000000
#define  Mcard_Read_Succes    	   Message_Status_Card|=0x02000000
#define  Mcard_Read_Error          Message_Status_Card|=0x04000000

#define  Mcard_Factory_Card        Message_Status_Card|=0x08000000
#define  Mcard_Authorization_Card  Message_Status_Card|=0x10000000
#define  Mcard_SetTime						 Message_Status_Card|=0x20000000 
#define  Mcard_BaylanNo_Change	   Message_Status_Card|=0x40000000 

#define  Mcard_Undefined_AN_Card   Message_Status_Card|=0x80000000

#ifdef __cplusplus
}
#endif
  
#endif /* __LCD_DEFINE_H*/

