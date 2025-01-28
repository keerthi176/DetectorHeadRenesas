/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_serial.h"
#include "r_cg_adc.h"
#include "r_cg_timer.h"
#include "r_cg_wdt.h"
#include "r_cg_it.h"
#include "delay.h"
#include "main.h"
/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern unsigned char PIRE_Z;
extern unsigned char ED04_Z;
extern unsigned char PIRS_Z;
extern F1 flag;
unsigned char PIR_30S,PIR_CONT;
unsigned char PIRC;
// Device     : RL78/R5F10268  
// File Name  : PIR.C
// Date       : 2018/11/18                                                    
// Version    : 1.1
/***********************************************************************************************************************
* Description  : PIR detection
***********************************************************************************************************************/
void PIR_CY(void)
{
	if(PIRE_Z==0||ED04_Z==0)	
 	{
 	PIRS_Z=0;
	flag.PIR_30S_E=1;
	PIR_30S=0;
 	return;
  	}
	if(flag.PIR_30S_E==1)	
	{
 	PIR_30S++;		
 	if(PIR_30S>100)
	{
 	flag.PIR_30S_E=0;
 	PIR_30S=0;}	
	PIRS_Z=0;
	PIR_CONT=0;
	return;
	}
 	if(PIRC==1)
	{
	PIR_CONT++;	
	if(PIR_CONT>=3)
 	PIRS_Z=1;
	}
 	else
	PIR_CONT=0;
}
