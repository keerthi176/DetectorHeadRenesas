// Device     : RL78/R5F10268  
// File Name  : smoke.c
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

unsigned int gzd05,gzd1,gzd2,gzd3,gzd4,gzd5,gzd6;
extern F2 gz;
extern dttt dd;
unsigned char OPK,FLED;
/***********************************************************************************************************************
* Description  : smoke initialization
***********************************************************************************************************************/
void SD_SMOKE_INT(void)
{
	if((500<SMOKE_NEWZERO_VALUE)||(SMOKE_NEWZERO_VALUE<20))
	{
	gz.c.EER_SDGZ=1;
	SMOKE_NEWZERO_VALUE=60;
	}
	if((600<SMOKE_ALARM_VALUE)||(SMOKE_ALARM_VALUE<20))
	{
	gz.c.EER_SDGZ=1;
	SMOKE_ALARM_VALUE=30;
	}	
	SMOKE_NO_ALARM_VALUE=SMOKE_ALARM_VALUE>>2;	
	SMOKE_NEWZERO_XDD=800;	
	gzd05=SMOKE_NEWZERO_VALUE;
	gzd1=gzd05;
	gzd2=gzd05;
	gzd3=gzd05;
	gzd4=gzd05;
	gzd5=gzd05;
	gzd6=gzd05;
}
/***********************************************************************************************************************
* Description  : Sampling smoke concentration
***********************************************************************************************************************/
void SMOKE_CY(void)
{
	unsigned char D1,gbz=0;
	OPK=1;		
	DELAY2MS();
	ADS = 0X00;	
	ADCE=1;
	ADIF=0;
	for(D1=10;D1!=0;D1--);
	ADCS = 1U;  
	while(ADIF==0);
	S_ADCYZL=ADCR>>6;
	ADIF=0;
	if(S_ADCYZL>300)
	gbz=1;
	__DI();		
	FLED=1; 		
	for(D1=9;D1!=0;D1--);		
	ADCS = 1U;  
	for(D1=4;D1!=0;D1--);		
	FLED=0;
	__EI();		
	while(ADIF==0);
	S_ADCYZ=ADCR>>6;
	ADCE=0;
	OPK=0;		
	if(S_ADCYZ>=S_ADCYZL)
	{SMOKE_VALUE=S_ADCYZ-S_ADCYZL;
	if(SMOKE_VALUE<5)
	gbz=2;	
	}
	else
	gbz=3;
	if(gbz!=0)
	{SMOKE_VALUE=gbz;
	SGZJSQ++;
	if(SGZJSQ>9)
	gz.c.SMOKE_GZ=1;
	}else
	{
	gz.c.SMOKE_GZ=0;
	SGZJSQ=0;
	}
}
/***********************************************************************************************************************
* Description  : Storage of smoke sampling data
***********************************************************************************************************************/
void SMOKE_V_GX(void)
{
RESULT4 =RESULT3;
RESULT3 =RESULT2;
RESULT2 =RESULT1;
RESULT1 =SMOKE_VALUE;
}
/***********************************************************************************************************************
* Description  : Update background values
***********************************************************************************************************************/
void SMOKE_ZERO(void)
{
	static unsigned int ze_d1,ze_d2,ze_d3,ze_dd;
	MCNT1++;
	if(MCNT1<450)	
	return;
	MCNT1=0;
	MCNT2++;
	ze_d1=SMOKE_ALARM_VALUE>>1;	
	ze_d2=ze_d1>>1;			
	ze_d3=ze_d2>>1;			   

	if(S_PGZ>gzd05)
	ze_dd=S_PGZ-gzd05;
	else
	ze_dd=gzd05-S_PGZ;		
	if(ze_d3>ze_dd)
	goto	SMOKE_ZERO_3;
	if(S_PGZ>gzd1)
	ze_dd=S_PGZ-gzd1;
	else
	ze_dd=gzd1-S_PGZ;
	if(ze_d2<ze_dd)
	goto	SMOKE_ZERO_5;	
SMOKE_ZERO_3:	
	if(S_PGZ>gzd6)
	ze_dd=S_PGZ-gzd6;
	else
	ze_dd=gzd6-S_PGZ;	
	if(ze_d1<ze_dd)
	goto	SMOKE_ZERO_5;		
	SMOKE_NEWZERO_VALUE=S_PGZ;
	if(SMOKE_NEWZERO_VALUE>SMOKE_NEWZERO_XDD)
	gz.c.SDIRB=1;
	else
	gz.c.SDIRB=0;
SMOKE_ZERO_5:
	if(!(MCNT2&0x01))
	{
	gzd6=gzd5;
	gzd5=gzd4;
	gzd4=gzd3;
	gzd3=gzd2;
	gzd2=gzd1;
	}
	gzd1=gzd05;
	gzd05=S_PGZ;
}
unsigned int SMOKE_MN(void)
{
	unsigned int sm_d1,sm_d2;
	sm_d1=S_PGZ<<5;		
	sm_d2=SMOKE_ALARM_VALUE*23;	
	sm_d1+=sm_d2;
	sm_d2=SMOKE_NEWZERO_VALUE<<5;	
	if(sm_d1>sm_d2)
	{
	sm_d1-=sm_d2;
	sm_d1/=SMOKE_ALARM_VALUE;
	if(sm_d1<=9)
	sm_d1=9;
	if(sm_d1>=99)
	sm_d1=99;
	}
	else
	sm_d1=9;
	if(gz.IG!=0&&sm_d1<54)
	{
	sm_d2=0;
	if(gz.c.SMOKE_GZ==1)  
	sm_d2|=1;
	if(gz.c.SDIRB==1)	
	sm_d2|=2;
	if(gz.c.EER_SDGZ==1)	
	sm_d2=4;
	if(gz.c.EEW_SDGZ==1)	
	sm_d2=8;
	return	sm_d2;
	}
	return	sm_d1;
}
/***********************************************************************************************************************
* Description  : Calculation of average value of sampling data
***********************************************************************************************************************/
unsigned int DATA_PROCESS(void)
{
unsigned int pgzd;
pgzd=RESULT1;
pgzd+=RESULT2;
pgzd+=RESULT3;
pgzd+=RESULT4;
return pgzd/=4;
}

