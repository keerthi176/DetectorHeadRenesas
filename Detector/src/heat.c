// Device     : RL78/R5F10268  
// File Name  : heat.c
// Date       : 2018/11/18                                                    
// Version    : 1.1 
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
unsigned char h_4s,h_20s,h_40s,h_60s,ws_time,ws_ext;
extern F1 flag;
extern dttt dd;
extern unsigned char HVAL_Z;
unsigned char WDY;
/***********************************************************************************************************************
* Description  : heat initialization
***********************************************************************************************************************/
void SD_HEAT_IN(void)
{
	h_4s=H_PGZ>>2;
	h_20s=h_4s;
	h_40s=h_4s;
	h_60s=h_4s;
}
/***********************************************************************************************************************
* Description  : Temperature sampling
***********************************************************************************************************************/
void HEAT_CY(void)
{
	unsigned char D1,gdz=0;
	WDY=1;		
	ADS = 0X01;	
	ADCE=1;
	ADIF=0;
	for(D1=30;D1!=0;D1--);
	ADCS = 1U;  
	while(ADIF==0);
	H_ADCYZL=ADCR>>6;
	ADIF=0;
	ADCE=0;
	WDY=0;		
	if(H_ADCYZL<5)
	gdz=1;	
	if(H_ADCYZL>1000)
	gdz=2;
	if(gdz!=0)
	{
	HGZJSQ++;
	if(HGZJSQ>9)
	flag.HEAT_GZ=1;
	}else
	{
	flag.HEAT_GZ=0;
	HGZJSQ=0;
	}
}
/***********************************************************************************************************************
* Description  : Calculation of average value of sampling data
***********************************************************************************************************************/
unsigned int HEAT_PROCESS(void)
{
unsigned int pgzd;
pgzd=H_BDAT1;
pgzd+=H_BDAT2;
pgzd+=H_BDAT3;
pgzd+=H_BDAT4;
return pgzd/=4;
}
/***********************************************************************************************************************
* Description  : Storage of temperature sampling data
***********************************************************************************************************************/
void HEAT_V_GX(void)
{
H_BDAT4 =H_BDAT3;
H_BDAT3 =H_BDAT2;
H_BDAT2 =H_BDAT1;
H_BDAT1 =H_ADCYZL;
}
/***********************************************************************************************************************
* Description  : Temperature rise mode calculation
***********************************************************************************************************************/
void HEAT_WS(void)
{
	unsigned char wd1, wd2;
	if(flag.TIME_W==0)	
	return;
	ws_time++;
	wd2=23;		
	if(ws_time>=5)
	{
	ws_time=0;
	h_60s=h_40s;
	h_40s=h_20s;
	h_20s=h_4s;
	}
	h_4s=H_ADCYZL>>2;
	if(h_60s>h_4s)
	{
	wd1=h_60s-h_4s;
	if(wd1>=2)
	{
	ws_ext=0;
	wsb_time+=wd1;
	if(wd1>=8)
	wsb_time+=wd1;
	if(wd1>=16)
	wsb_time+=wd1;
	}
	else
	ws_ext++;
	}
	else
	ws_ext++;
	if(ws_ext>=3)
	{
	wsb_time=0;
	ws_ext=10;
	}
	if(wsb_time>375)
	wd2=45;
	if(wsb_time>450)
	wd2=55;
 	if(H_PGZ<=382)		
	wd2=56;
	if(flag.HEAT_GZ==1)
	wd2=1;
	HVAL_Z=wd2;
}
/***********************************************************************************************************************
* Description  : Temperature analog value calculation
***********************************************************************************************************************/
unsigned char HEAT_MN(unsigned int wdz)
{
	unsigned int hm_d1,hm_d2;
	hm_d1=0;
	if(flag.HEAT_GZ==1)
	return hm_d1=1;
	hm_d2=wdz>>2;
	if(hm_d2>=208)	
	return 9;
	
	if(hm_d2>=206)
	{
	return 10;}	
	
	if(hm_d2>=187)  
	{
	hm_d1=hm_d2-187;
	hm_d1<<=3;
	hm_d1=hm_d1/18;
	hm_d1=19-hm_d1;	
	return hm_d1;}
	
	if(hm_d2>=165)  
	{
	hm_d1=hm_d2-165;
	hm_d1<<=3;
	hm_d1=hm_d1/21;
	hm_d1=28-hm_d1;	
	return hm_d1;}	
	
	if(hm_d2>=142)  
	{
	hm_d1=hm_d2-142;
	hm_d1<<=3;
	hm_d1=hm_d1/22;
	hm_d1=37-hm_d1;	
	return hm_d1;}	
	
	if(hm_d2>=119)  
	{
	hm_d1=hm_d2-119;
	hm_d1<<=3;
	hm_d1=hm_d1/22;
	hm_d1=46-hm_d1;	
	return hm_d1;}	
	
	if(hm_d2>=98)  
	{
	hm_d1=hm_d2-98;
	hm_d1<<=3;
	hm_d1=hm_d1/20;
	hm_d1=55-hm_d1;	
	return hm_d1;}	
	
	if(hm_d2>=79)  
	{
	hm_d1=hm_d2-79;
	hm_d1<<=3;
	hm_d1=hm_d1/18;
	hm_d1=64-hm_d1;	
	return hm_d1;}
	
	if(hm_d2>=62)  
	{
	hm_d1=hm_d2-62;
	hm_d1<<=3;
	hm_d1=hm_d1/16;
	hm_d1=73-hm_d1;	
	return hm_d1;}
	
	if(hm_d2>=51) 
	{
	hm_d1=hm_d2-51;
	hm_d1<<=3;
	hm_d1=hm_d1/10;
	hm_d1=81-hm_d1;	
	return hm_d1;}
	
	if(hm_d2>=41)	
	{
	hm_d1=hm_d2-41;
	hm_d1<<=3;
	hm_d1=hm_d1/9;
	hm_d1=90-hm_d1;	
	return hm_d1;
	}	

	if(hm_d2>=32)	
	{
	hm_d1=hm_d2-32;
	hm_d1<<=3;
	hm_d1=hm_d1/9;
	hm_d1=99-hm_d1;	
	return hm_d1;
	}
	
	if(hm_d2<=31)
	hm_d1=99;
	if(wdz<=10)
	hm_d1=1;	
	return hm_d1;
}
