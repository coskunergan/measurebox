
#include <stm32l1xx.h>

#ifndef __STM32L1xx_DEFINE_H
#define __STM32L1xx_DEFINE_H

#ifdef __cplusplus
 extern "C" {
#endif 

extern uint32_t  Error_Status;	 
	 
#define    Valve_Error1_S    Error_Status|=0x00000001	 // Valf uçlari takili degil veya valf arizali iken valf durumu degistirilemiyor ise bit set olur.	 
#define    Valve_Error2_S    Error_Status|=0x00000002	 // Vpump gerilimi Düsük bu yüzden valf durumu degistirilemiyor ise bit set olur. 
#define    Gprs_Error_S      Error_Status|=0x00000004	 // GPRS baglantisi 3 kez denenip saglanamadigi durumlarda bit set olur.
#define    Pulse_Error_S     Error_Status|=0x00000008	 // Pals okuma kablosu üzerinde ceza olustugunda bit set olur.
#define    WDT_Reset_S       Error_Status|=0x00000010	 // Cihaz Bir durumdan etkilenip yazilimsal olarak reset aldiginda bit set olur.
	
	 
#define 	 Led_PwrMon   LED1
#define		 Buzzer  			BUZZER
#define 	 ButonA  			BUTONA
#define 	 ButonB 			BUTONB
#define		 Gsm_Rst  		GSM_RST
#define		 Gsm_Enb  		GSM_ENB
#define	   Fm_Enb     	FM_ENB
#define  	 Eep_Enb    	EEP_ENB 
#define		 Pulse_Enb  	PULSE_ENB
#define		 M_Back  			  M1
#define		 M_Next   		  M2
#define		 M_Sleep  		  M_SLEEP
#define		 Pulse_1  		  PULSE_1
#define		 Pulse_2  		  PULSE_2
#define		 Pulse_3  		  PULSE_3
	 

#define  	 Gsm_Com	    COM1
#define 	 Optik_Com	  COM2
#define  	 Debug_Com	  COM3

#define  	 Gsm_Com_Source	    STM_COM1
#define 	 Optik_Com_Source	  STM_COM2
#define  	 Debug_Com_Source	  STM_COM3	 
	 
	 
	 
#ifdef __cplusplus
}
#endif
  
#endif /* __STM32L1xx_DEFINE_H*/

