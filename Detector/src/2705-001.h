// Device     : RL78/R5F10268  
// File Name  : 2705-001.h
// Date       : 2018/11/18                                                    
// Version    : 1.1  
/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#include "main.h"	
/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
F1 flag;		//flag
F2 gz;			//fault
 unsigned char stop_t;	//sotp time
	
unsigned char rx_bz;	//Receiving steps
unsigned char txint_count; //Number of interruptions	

IM    SENU_Y;		//Year of manufacture, beginning from current year 17 to 99,Month of manufacture, range from 01 to 12
unsigned char SENU_B;	//Batch number of the detector with range of 01 to 31
IM    SENU_S;		//Serial number of the detector with range of 00001 to 65535
unsigned char STH1_Z;	//Smoke Upper Threshold
unsigned char STH0_Z;	//Smoke Lower Threshold
unsigned char HTH1_Z;	//Heat Upper Threshold
unsigned char HTH0_Z;	//Heat Lower Threshold
unsigned char SVAL_Z;	//Smoke Analogue Value 
unsigned char HVAL_Z;	//Heat Analogue Value
unsigned char DECL_Z;	//Class of Device
unsigned char PIRS_Z;	//PIR Status
unsigned char PIRE_Z;	//PIR Enable Operation
unsigned char ILED_Z;	//Indicator Control
unsigned char DETY_Z;	//Type of Device
unsigned char STAT_Z;	//Read only command to identify the status of the detector and the type of sensor that raised the event/interrupt in one single message	
unsigned char STAT_Z1;	//Read only command to identify the status of the detector and the type of sensor that raised the event/interrupt in one single message
unsigned char OCS1_Z;	//Optical Chamber Status
unsigned char OPEC_Z;	//Switch Control
LM    IDNU_Z;		//Identification Number
unsigned char DRSO_Z;	//Reset Source
unsigned char ED01_Z;	//Smoke sensor status
unsigned char ED02_Z;	//Heat sensor status
unsigned char ED04_Z;	//Heat sensor status
unsigned char DBID_Z;	//Detector Branding Id
unsigned char DBID_LSZ;	//Detector Branding Id

unsigned char RW_DataFla_buff[22];	//DATA FLASH 
unsigned char TX_TIME;		//Interrupt signal timing
IM sz_mos;	//Product function selection
ev ev_int;	//Interrupt signal
ev ev_bj;	//Interrupt signal
ev ev_ls;	//Interrupt signal comparison
dttt dd;	//data

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
extern void R_Systeminit(void);
void R_FLASH(void);
void  STOP_TIME(void);
void H_ALARM_PD(void);	
void CHECK_ALARM(void);	
void SD_DATACS(void);
void SD_SAMPLE_PJ(void); 
void STAS_DATA(void);
void YBF_TX20MS(void);
void SOTPYAS(unsigned char ss_d1);
void DBID_ER(void);
void R_pdl(unsigned char* buffer);
