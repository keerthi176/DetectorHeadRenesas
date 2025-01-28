/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G12 V2.04.08.02 [03 Jun 2024]
* Device(s)    : R5F10268
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 28-01-2025
***********************************************************************************************************************/

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
/* Start user code for include. Do not edit comment generated here */
#include "2705-001.h"
#include "smoke.h"
#include "heat.h"
#include "PIR.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
unsigned char TX;
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
   	R_Systeminit();
	R_IT_Start();
	SOTPYAS(10);
	R_FLASH();
	SD_SAMPLE_PJ();
	SD_DATACS();
	R_INTC2_Start();
    while (1)
    {
    	STOP_TIME();
    		    if(OPEC_Z==1)
    		    {
    		    if((sz_mos.L&0X01)&&(ED01_Z==1))
    		    {
    		    if(flag.TIME_W==1||flag.Y_YWB==1)
    		    {
    		    SMOKE_CY();
    		    if(SGZJSQ==0)
    		    {
    		    SMOKE_V_GX();
    		    S_PGZ=DATA_PROCESS();
    		    }
    		    SVAL_Z=SMOKE_MN();
    		    CHECK_ALARM();
    		    }
    		    }
    		    if((sz_mos.L&0X02)&&(ED02_Z==1))
    		    {
    		    HEAT_CY();
    		    if(HGZJSQ==0)
    		    {
    		    HEAT_V_GX();
    		    H_PGZ=HEAT_PROCESS();
    		    if(sz_mos.L&0X04)
    		    HEAT_WS();
    		    else
    		    HVAL_Z=HEAT_MN(H_PGZ);
    		    }
    		    H_ALARM_PD();
    		    }
    		    STAS_DATA();
    		   YBF_TX20MS();
    		    }
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Description  : 200ms delay.
***********************************************************************************************************************/
void SOTPYAS(unsigned char ss_d1)
{
	while(ss_d1--)
	{
	    __stop();
	    R_WDT_Restart();
	}
}

/***********************************************************************************************************************
* Description  : Read setting data judgment
***********************************************************************************************************************/
void	SD_DATACS(void)
{
	unsigned int sd1;
	DRSO_Z=1;
	if(RESF&0X10)
	DRSO_Z=2;
	if(RESF&0X01)
	DRSO_Z=3;
if(sz_mos.L&0X01)
	SD_SMOKE_INT();
	STH1_Z=45;
	STH0_Z=0;
	HTH1_Z=65;
	HTH0_Z=0;
	SVAL_Z=23;
	HVAL_Z=23;
	OPEC_Z=1;
	PIRE_Z=0;
	ED01_Z=1;
	ED02_Z=1;
	ED04_Z=1;
	sd1=sz_mos.L;
	sd1&=~0x04;
	DETY_Z=sd1;
	DECL_Z=1;
	if(sz_mos.L&0x02)
	{
	if(sz_mos.L&0X04)
	{
	HTH1_Z=45;
	DECL_Z=1;
	}
	else
	DECL_Z=2;
	}
}
/***********************************************************************************************************************
* Description  : AD sampling
***********************************************************************************************************************/
void SD_SAMPLE_PJ(void)
{
	unsigned char d1;
	for(d1=6;d1!=0;d1--)
	{
		SOTPYAS(8);
	    	if(sz_mos.L&0X01)
	    	{
	    	SMOKE_CY();
		if(SGZJSQ==0)
		{
	    	SMOKE_V_GX();
	    	S_PGZ=DATA_PROCESS();
		}
	    	}
	    	if(sz_mos.L&0X02)
	    	{
	    	HEAT_CY();
		if(HGZJSQ==0)
		{
	    	HEAT_V_GX();
	   	H_PGZ=HEAT_PROCESS();
		}
	    	}
	}
	SD_HEAT_IN();
}
/***********************************************************************************************************************
* Description  : udgment of smoke interruption signal value
***********************************************************************************************************************/
void CHECK_ALARM(void)
{
 	if(SVAL_Z>=STH1_Z)
 	flag.Y_YWB=1;
 	else
 	flag.Y_YWB=0;
 	if(SVAL_Z<=STH0_Z)
 	flag.S_STH0=1;
	else
	flag.S_STH0=0;
}
/***********************************************************************************************************************
* Description  : Judgment of heat interruption signal value
***********************************************************************************************************************/
void H_ALARM_PD(void)
{
 	if(flag.HEAT_GZ==1)
	HVAL_Z=1;
 	if(HVAL_Z>=HTH1_Z)
 	flag.Y_HWB=1;
 	else
 	flag.Y_HWB=0;
 	if(HVAL_Z<=HTH0_Z)
 	flag.H_HTH0=1;
 	else
 	flag.H_HTH0=0;
 }
/***********************************************************************************************************************
* Description  : Read the setting data
***********************************************************************************************************************/
void R_FLASH(void)
{
	IM d1;
	R_pdl(&RW_DataFla_buff[0]);
	d1.H=RW_DataFla_buff[0];
	d1.L=RW_DataFla_buff[1];
	SMOKE_NEWZERO_VALUE=d1.I;
	d1.H=RW_DataFla_buff[2];
	d1.L=RW_DataFla_buff[3];
	SMOKE_ALARM_VALUE=d1.I;
	d1.H=RW_DataFla_buff[4];
	d1.L=RW_DataFla_buff[5];
	sz_mos.I=d1.I;
	SENU_S.L=RW_DataFla_buff[6];
	SENU_S.H=RW_DataFla_buff[7];
	SENU_B=RW_DataFla_buff[8];
	d1.L=RW_DataFla_buff[9];
	d1.H=d1.L&0X0F;
	d1.L=d1.L&0XF0;
	d1.L>>=4;
	SENU_Y.H=d1.L+17;
	SENU_Y.L=d1.H;
	DBID_LSZ=RW_DataFla_buff[10];
	DBID_Z=DBID_LSZ;
	if(sz_mos.L>32)
	{gz.c.EEW_SDGZ=1;
	sz_mos.I=0x000b;
	}
}
/***********************************************************************************************************************
* Description  : Emergency signal interrupt processing
***********************************************************************************************************************/
void YBF_TX20MS(void)
{
if(STAT_Z==1&&flag.YBTXQL==0)
{
	txint_count=5;
	do{
	R_WDT_Restart();
	if((flag.TXWC==0)&&(rx_bz==0))
	{
	R_INTC2_Stop();
	if(txint_count!=0)
	txint_count--;
	R_TAU0_Channel0_Start();
	TX_TIME=2;
	flag.TXWC=1;
	TX=0;
	}
	if(flag.YBTXQL==1)
	txint_count=0;
	}while(txint_count);
}
}
/***********************************************************************************************************************
* Description  : Product data status processing
***********************************************************************************************************************/
void STAS_DATA(void)
{
	ev1 d1;
	if(flag.Y_YWB==1||flag.Y_HWB==1||wsb_time!=0)
	flag.JKJC=1;
	else
	flag.JKJC=0;
	ev_ls.event=0;
	if(flag.Y_YWB==1)
	ev_ls.c.S1=1;
	else
	ev_int.c.S1=0;
	if(flag.S_STH0==1)
	ev_ls.c.S0=1;
	else
	ev_int.c.S0=0;
	if(flag.Y_HWB==1)
	ev_ls.c.H1=1;
	else
	ev_int.c.H1=0;
	if(flag.H_HTH0==1)
	ev_ls.c.H0=1;
	else
	ev_int.c.H0=0;
	if(PIRS_Z==1)
	ev_ls.c.PIR=1;
	else
	ev_int.c.PIR=0;
	ev_bj.event=ev_ls.event;
	if(ev_bj.c.S1==1&&ev_int.c.S1==1)
	ev_ls.c.S1=0;
	if(ev_bj.c.S0==1&&ev_int.c.S0==1)
	ev_ls.c.S0=0;
	if(ev_bj.c.H1==1&&ev_int.c.H1==1)
	ev_ls.c.H1=0;
	if(ev_bj.c.H0==1&&ev_int.c.H0==1)
	ev_ls.c.H0=0;
	if(ev_bj.c.PIR==1&&ev_int.c.PIR==1)
	ev_ls.c.PIR=0;
	if(ev_ls.event!=0)
	flag.YBTXQL=0;
	d1.event=0;
	if(ev_bj.c.S1==1||ev_bj.c.S0==1)
	d1.c.S=1;
	if(ev_bj.c.H1==1||ev_bj.c.H0==1)
	d1.c.H=1;
	if(ev_bj.c.PIR==1)
	d1.c.PIR=1;
	STAT_Z1=d1.event;
	if(ev_bj.event!=0)
	STAT_Z=1;
	else
	STAT_Z=0;
	if(gz.c.SMOKE_GZ==1)
	{OCS1_Z=3;}
	else
	{
	if(gz.c.SDIRB==1)
	OCS1_Z=2;
	else
	OCS1_Z=0;
	}
}

/***********************************************************************************************************************
* Description  : peripheral data link
***********************************************************************************************************************/
void R_pdl(unsigned char* buffer) {
    // Fill the buffer with predefined values
    buffer[0] = 0x00;
    buffer[1] = 0x01;
    buffer[2] = 0x02;
    buffer[3] = 0x03;
    buffer[4] = 0x04;
    buffer[5] = 0x05;
    buffer[6] = 0x06;
    buffer[7] = 0x07;
    buffer[8] = 0x08;
    buffer[9] = 0x09;
    buffer[10] = 0x0A;
    buffer[11] = 0x0B;
    buffer[12] = 0x0C;
    buffer[13] = 0x0D;
    buffer[14] = 0x0E;
    buffer[15] = 0x0F;
    buffer[16] = 0x10;
    buffer[17] = 0x11;
    buffer[18] = 0x12;
    buffer[19] = 0x13;
    buffer[20] = 0x14;
    buffer[21] = 0x15;
}
/* End user code. Do not edit comment generated here */
