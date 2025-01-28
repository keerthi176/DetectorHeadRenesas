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
* File Name    : r_cg_serial_user.c
* Version      : CodeGenerator for RL78/G12 V2.04.08.02 [03 Jun 2024]
* Device(s)    : R5F10268
* Tool-Chain   : CCRL
* Description  : This file implements device driver for Serial module.
* Creation Date: 28-01-2025
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"
/* Start user code for include. Do not edit comment generated here */
#include "main.h"
#include "r_cg_port.h"
#include "r_cg_timer.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_uart0_interrupt_send(vect=INTST0)
#pragma interrupt r_uart0_interrupt_receive(vect=INTSR0)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t * gp_uart0_tx_address;         /* uart0 send buffer address */
extern volatile uint16_t  g_uart0_tx_count;            /* uart0 send data number */
extern volatile uint8_t * gp_uart0_rx_address;         /* uart0 receive buffer address */
extern volatile uint16_t  g_uart0_rx_count;            /* uart0 receive data number */
extern volatile uint16_t  g_uart0_rx_length;           /* uart0 receive data length */
/* Start user code for global. Do not edit comment generated here */
const unsigned char I9SI[]= {"03.00.00,28/12/22"};
const unsigned char ERROR[]={"ERROR"};
const unsigned char OK[]={"OK"};

unsigned char rx_data;
unsigned char err_type;
rxxx rx;
txxx tx;
IM rxd_jcend;
LM js_datal;
volatile unsigned char * gp_uart0_tx_address1;
volatile const unsigned char * gp_uart0_tx_address_r;
unsigned char js_data;
unsigned char CXTO_Z;

extern IM sz_mos;
extern ev ev_int;
extern ev ev_bj;

extern IM    SENU_Y;
extern unsigned char SENU_B;
extern IM    SENU_S;
extern unsigned char stop_t;
extern F1 flag;
extern unsigned char rx_bz;
extern unsigned char TX_TIME;
extern unsigned char DETY_Z;
extern unsigned char DECL_Z;
extern unsigned char ED01_Z;
extern unsigned char ED02_Z;
extern unsigned char ED04_Z;
extern unsigned char STH1_Z;
extern unsigned char STH0_Z;
extern unsigned char HTH1_Z;
extern unsigned char HTH0_Z;
extern unsigned char SVAL_Z;
extern unsigned char STH1_Z;

extern unsigned char HVAL_Z;
extern unsigned char DECL_Z;
extern unsigned char PIRS_Z;
extern unsigned char PIRE_Z;
extern unsigned char ILED_Z;
extern unsigned char DETY_Z;
extern unsigned char STAT_Z;
extern unsigned char STAT_Z1;
extern unsigned char OCS1_Z;
extern unsigned char OPEC_Z;
extern LM    IDNU_Z;
extern unsigned char DRSO_Z;
extern unsigned char DBID_Z;
extern unsigned char DBID_LSZ;
extern unsigned char PIR_CONT;
extern unsigned char TX;
unsigned char PIRDY;
unsigned char LED;

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_uart0_interrupt_receive
* Description  : This function is INTSR0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_uart0_interrupt_receive(void)
{
    volatile uint8_t rx_data;
    volatile uint8_t err_type;
    
    err_type = (uint8_t)(SSR01 & 0x0007U);
    SIR01 = (uint16_t)err_type;

    if (err_type != 0U)
    {
        r_uart0_callback_error(err_type);
    }
    
    rx_data = RXD0;

    if (g_uart0_rx_length > g_uart0_rx_count)
    {
        *gp_uart0_rx_address = rx_data;
        gp_uart0_rx_address++;
        g_uart0_rx_count++;

        if (g_uart0_rx_length == g_uart0_rx_count)
        {
            r_uart0_callback_receiveend();
        }
    }
    else
    {
        r_uart0_callback_softwareoverrun(rx_data);
    }
}

/***********************************************************************************************************************
* Function Name: r_uart0_interrupt_send
* Description  : This function is INTST0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_uart0_interrupt_send(void)
{
    if (g_uart0_tx_count > 0U)
    {
        TXD0 = *gp_uart0_tx_address;
        gp_uart0_tx_address++;
        g_uart0_tx_count--;
    }
    else
    {
        r_uart0_callback_sendend();
    }
}

/***********************************************************************************************************************
* Function Name: r_uart0_callback_receiveend
* Description  : This function is a callback function when UART0 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_uart0_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_uart0_callback_softwareoverrun
* Description  : This function is a callback function when UART0 receives an overflow data.
* Arguments    : rx_data -
*                    receive data
* Return Value : None
***********************************************************************************************************************/
static void r_uart0_callback_softwareoverrun(uint16_t rx_data)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_uart0_callback_sendend
* Description  : This function is a callback function when UART0 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_uart0_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_uart0_callback_error
* Description  : This function is a callback function when UART0 reception error occurs.
* Arguments    : err_type -
*                    error type value
* Return Value : None
***********************************************************************************************************************/
static void r_uart0_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Description  : Data decoding received by UART
***********************************************************************************************************************/
void RX_DATACX(void)
{
	unsigned char rx_d1;
	unsigned int rx_d2;
	tx.c.g_uart0_tx_count=0;
	flag.ROMTX=0;
	rx.data[19]=rx.data[1];
	rx.data[18]=rx.data[2];
	rx.data[17]=rx.data[3];
	rx.data[16]=rx.data[4];
	CXTO_Z=0;
	if(rx.data[5]=='?')
	{
switch(rx.c.ml){
	case	0x53454E55 :
	{
	tx.c.TX_DATA[0]=SENU_Y.H/10+0X30;
	tx.c.TX_DATA[1]=SENU_Y.H%10+0X30;
	tx.c.TX_DATA[2]=SENU_Y.L/10+0X30;
	tx.c.TX_DATA[3]=SENU_Y.L%10+0X30;
	tx.c.TX_DATA[4]='-';
	tx.c.TX_DATA[5]=SENU_B/10+0X30;
	tx.c.TX_DATA[6]=SENU_B%10+0X30;
	tx.c.TX_DATA[7]='-';
	rx_d2=SENU_S.I;
	tx.c.TX_DATA[8]=rx_d2/10000+0X30;
	rx_d2=rx_d2%10000;
	tx.c.TX_DATA[9]=rx_d2/1000+0X30;
	rx_d2=rx_d2%1000;
	tx.c.TX_DATA[10]=rx_d2/100+0x30;
	rx_d2=rx_d2%100;
	tx.c.TX_DATA[11]=rx_d2/10+0x30;
	rx_d2=rx_d2%10;
	tx.c.TX_DATA[12]=rx_d2+0x30;
	tx.c.g_uart0_tx_count=15;
	return;}
	case	0x49395349 :
	{
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=19;
	gp_uart0_tx_address_r=I9SI;
	return;}
	case	0x44455459 :
	{
	tx.c.TX_DATA[0]=DETY_Z/10+0X30;
	tx.c.TX_DATA[1]=DETY_Z%10+0X30;
	tx.c.g_uart0_tx_count=4;
	return;}
	case	0x4445434C :
	{
	tx.c.TX_DATA[0]=DECL_Z+0X30;
	tx.c.g_uart0_tx_count=3;
	return;}
	case	0x44544143 :
	{
	tx.c.TX_DATA[0]=DETY_Z/10+0X30;
	tx.c.TX_DATA[1]=DETY_Z%10+0X30;
	tx.c.TX_DATA[2]=',';
	tx.c.TX_DATA[3]=DECL_Z+0X30;
	tx.c.g_uart0_tx_count=6;
	return;}
	case	0X45443031:
	{
	if(sz_mos.L&0X01)
		{
	tx.c.TX_DATA[0]=ED01_Z+0X30;
	tx.c.g_uart0_tx_count=3;
		}
	return;}
	case	0X45443032:
	{
	if(sz_mos.L&0X02)
	{
	tx.c.TX_DATA[0]=ED02_Z+0X30;
	tx.c.g_uart0_tx_count=3;
	}
	return;}
		case	0X45443034:
	{
	if(sz_mos.L&0X08)
	{
	tx.c.TX_DATA[0]=ED04_Z+0X30;
	tx.c.g_uart0_tx_count=3;
	}
	return;}
	case	0x53544831  :
	{
	tx.c.TX_DATA[0]=STH1_Z/10+0X30;
	tx.c.TX_DATA[1]=STH1_Z%10+0X30;
	tx.c.g_uart0_tx_count=4;
	return;}
	case  0X53544830:
	{
	tx.c.TX_DATA[0]=STH0_Z/10+0X30;
	tx.c.TX_DATA[1]=STH0_Z%10+0X30;
	tx.c.g_uart0_tx_count=4;
	return;
	}
	case	0x48544831 :
	{
	tx.c.TX_DATA[0]=HTH1_Z/10+0X30;
	tx.c.TX_DATA[1]=HTH1_Z%10+0X30;
	tx.c.g_uart0_tx_count=4;
	return;}
	case   0x48544830:
	{
	tx.c.TX_DATA[0]=HTH0_Z/10+0X30;
	tx.c.TX_DATA[1]=HTH0_Z%10+0X30;
	tx.c.g_uart0_tx_count=4;
	return;
	}
	case	0x5356414C  :
	{
	tx.c.TX_DATA[0]=SVAL_Z/10+0X30;
	tx.c.TX_DATA[1]=SVAL_Z%10+0X30;
	tx.c.g_uart0_tx_count=4;
	return;}
	case	0x4856414C  :
	{
	tx.c.TX_DATA[0]=HVAL_Z/10+0X30;
	tx.c.TX_DATA[1]=HVAL_Z%10+0X30;
	tx.c.g_uart0_tx_count=4;
	return;}
	case	0x50495253  :
	{
	tx.c.TX_DATA[0]=PIRS_Z+0x30;
	tx.c.g_uart0_tx_count=3;
	return;}
	case	0x50495245  :
	{
	tx.c.TX_DATA[0]=PIRE_Z+0x30;
	tx.c.g_uart0_tx_count=3;
	return;}
	case	0x494C4544  :
	{
	tx.c.TX_DATA[0]=ILED_Z+0x30;
	tx.c.g_uart0_tx_count=3;
	return;}
	case	0x53544154  :
	{
	tx.c.TX_DATA[0]=STAT_Z+0x30;
	tx.c.TX_DATA[1]=',';
	tx.c.TX_DATA[2]=STAT_Z1/10+0X30;
	tx.c.TX_DATA[3]=STAT_Z1%10+0X30;
		if(STAT_Z==1)
	flag.YBTXQL=1;
	tx.c.g_uart0_tx_count=6;
	if(ev_int.c.S1==0&&ev_bj.c.S1==1)
	{ev_int.c.S1=1;return;}
	if(ev_int.c.S0==0&&ev_bj.c.S0==1)
	{ev_int.c.S0=1;return;}
	if(ev_int.c.H1==0&&ev_bj.c.H1==1)
	{ev_int.c.H1=1;return;}
	if(ev_int.c.H0==0&&ev_bj.c.H0==1)
	{ev_int.c.H0=1;return;}
	if(ev_int.c.PIR==0&&ev_bj.c.PIR==1)
	{ev_int.c.PIR=1;return;}
	return;}
	case	0x4F435331  :
	{
	tx.c.TX_DATA[0]=OCS1_Z+0x30;
	tx.c.g_uart0_tx_count=3;
	return;}
	case	0x4F504543  :
	{
	tx.c.TX_DATA[0]=OPEC_Z+0x30;
	tx.c.g_uart0_tx_count=3;
	return;}
	case	0x49444E55  :
	{
		rx_d1=IDNU_Z.m4;
		if(rx_d1>=0x0a) rx_d1+=0x37;
		else rx_d1+=0x30;
	tx.c.TX_DATA[0]=rx_d1;

		rx_d1=IDNU_Z.m3;
		if(rx_d1>=0x0a) rx_d1+=0x37;
		else rx_d1+=0x30;
	tx.c.TX_DATA[1]=rx_d1;

		rx_d1=IDNU_Z.m2;
		if(rx_d1>=0x0a) rx_d1+=0x37;
		else rx_d1+=0x30;
	tx.c.TX_DATA[2]=rx_d1;

		rx_d1=IDNU_Z.m1;
		if(rx_d1>=0x0a) rx_d1+=0x37;
		else rx_d1+=0x30;
	tx.c.TX_DATA[3]=rx_d1;

	tx.c.g_uart0_tx_count=6;
	return;}
	case	0x4452534F  :
	{
	tx.c.TX_DATA[0]=DRSO_Z+0x30;
	tx.c.g_uart0_tx_count=3;
	return;
	}
	case	0x44424944  :
	{
	rx_d1=DBID_Z;
	tx.c.TX_DATA[0]=rx_d1/100+0X30;
	rx_d2=rx_d1%100;
	tx.c.TX_DATA[1]=rx_d2/10+0X30;
	tx.c.TX_DATA[2]=rx_d2%10+0X30;
	tx.c.g_uart0_tx_count=5;
	return;}
	}
	return;}
	if(rx.data[5]=='=')
	{
	switch(rx.c.ml){
	case	  0X45443031:
	{
	if(sz_mos.L&0X01){
	rx_d1=RXDATAJS1();
	if((rx_d1==0)&&(js_data<=1))
	{
	ED01_Z=js_data;
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	}}
	return;}
	case	  0X45443032:
	{
	if(sz_mos.L&0X02){
	rx_d1=RXDATAJS1();
	if((rx_d1==0)&&(js_data<=1))
	{
	ED02_Z=js_data;
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	}}
	return;}
	case	  0X45443034:
	{
	if(sz_mos.L&0X08)	{
	rx_d1=RXDATAJS1();
	if((rx_d1==0)&&(js_data<=1))
	{
	ED04_Z=js_data;
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	}}
	return;}
	case	0x53544831  :
	{
	if(RXDATAJS2()==0)
	{STH1_Z=js_data;
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	ev_int.c.S1=0;
	}
	return;}
	case	0x53544830  :
	{
	if(RXDATAJS2()==0)
	{STH0_Z=js_data;
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	ev_int.c.S0=0;
	}
	return;}
	case	0x48544831 :
	{
	if(RXDATAJS2()==0)
	{
	HTH1_Z=js_data;
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	ev_int.c.H1=0;
	}
	return;}
	case	0x48544830 :
	{
	if(RXDATAJS2()==0)
	{
	HTH0_Z=js_data;
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	ev_int.c.H0=0;
	}
	return;}
	case	0x50495245  :
	{
	rx_d1=RXDATAJS1();
	if((rx_d1==0)&&(js_data<=1))
	{
	PIRE_Z=js_data;
	if(sz_mos.L&0X08)
	{
	if(PIRE_Z==1)
	PIRDY=1;
	else
	PIRDY=0;
	}
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	}
	return;}
	case	0x494C4544  :
	{
	rx_d1=RXDATAJS1();
	if((rx_d1==0)&&(js_data<=1))
	{
	ILED_Z=js_data;
	if(ILED_Z==1)
		LED=1;
	else
		LED=0;
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	}
	return;}
	case	0x4F504543  :
	{
	rx_d1=RXDATAJS1();
	if((rx_d1==0)&&(js_data<=1))
	{
	OPEC_Z=js_data;
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	}
	return;}
	case	0x49444E55  :
	{
	if(RXDATAJS4()==0)
	{
	IDNU_Z.L=js_datal.L;
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	}
	return;}
	case	0x4452534F  :
	{
	if(RXDATAJS1()==0)
	{
	DRSO_Z=js_data;
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	}
	return;}
	case	0x44424944  :
	{
	if(RXDATAJS3()==0)
	{
	DBID_LSZ=js_data;
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	}
	return;}
	}
	return;}
	if(rx.data[5]=='+')
	{
	switch(rx.c.ml){
	case	0x50495243  :
	{
	if(PIRS_Z==1)
	{
	ev_int.c.PIR=0;
	ev_bj.c.PIR=0;
	PIRS_Z=0;
	}
	PIR_CONT=0;
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	return;}
	case	0x4358544F  :
	{
	flag.ROMTX=1;
	tx.c.g_uart0_tx_count=4;
	gp_uart0_tx_address_r=OK;
	CXTO_Z=0XFF;
	return;}
	}
	return;}
}
/***********************************************************************************************************************
* Description  : UART reception ON
***********************************************************************************************************************/
void R_UART0tx_Start(void)
{
   SO0 |= _0001_SAU_CH0_DATA_OUTPUT_1;
   SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;
   SS0 |= _0001_SAU_CH0_START_TRG_ON;
   STIF0 = 0U;
   STMK0 = 0U;
}
/***********************************************************************************************************************
* Description  : UART sends data
***********************************************************************************************************************/
void R_UART0_Send1(void)
{
        SMR00 |= _0001_SAU_BUFFER_EMPTY;
        STMK0 = 1U;
		    if(flag.ROMTX==1)
	    {
	    TXD0 = *gp_uart0_tx_address_r;
	    gp_uart0_tx_address_r++;}
	    else
	    {
            TXD0 = *gp_uart0_tx_address1;
	    gp_uart0_tx_address1++;}
        tx.c.g_uart0_tx_count--;
        STMK0 = 0U;
}
/***********************************************************************************************************************
* Description  : UART data validity judgment
***********************************************************************************************************************/
unsigned char RXDATAJS1(void)
{
	unsigned char js_d1;
	unsigned char js_gz=0;
	if(rx.data[15]!=8)
	return	js_gz=0x80;
	js_d1=rx.data[6];
	if(js_d1<=0x2f)
	js_gz|=1;
	if(js_d1>=0x3a)
	js_gz|=2;
	if(js_gz!=0)
	return	js_gz;
	js_data=js_d1-0x30;
	return 0;
}
/***********************************************************************************************************************
* Description  : UART data validity and data conversion
***********************************************************************************************************************/
unsigned char RXDATAJS2(void)
{
	unsigned char js_d1;
	unsigned char js_gz=0;
	if(rx.data[15]!=9)
	return	js_gz=0x80;
	js_d1=rx.data[6];
	if(js_d1<=0x2f)
	js_gz|=1;
	if(js_d1>=0x3a)
	js_gz|=2;
	if(js_gz!=0)
	return	js_gz;
	js_data=(js_d1-0x30)*10;
	js_d1=rx.data[7];
	if(js_d1<=0x2f)
	js_gz|=4;
	if(js_d1>=0x3a)
	js_gz|=8;
	if(js_gz!=0)
	return	js_gz;
	js_d1=js_d1-0x30;
	js_data+=js_d1;
	return 0;
}
/***********************************************************************************************************************
* Description  : UART data validity and data conversion
***********************************************************************************************************************/
unsigned char RXDATAJS3(void)
{
	unsigned char js_d1;
	unsigned char js_gz=0;
	if(rx.data[15]!=10)
	return	js_gz=0x80;
	js_d1=rx.data[6];
	if(js_d1<=0x2f)
	js_gz|=1;
	if(js_d1>=0x3a)
	js_gz|=2;
	if(js_gz!=0)
	return	js_gz;
	js_data=(js_d1-0x30)*100;
	js_d1=rx.data[7];
	if(js_d1<=0x2f)
	js_gz|=4;
	if(js_d1>=0x3a)
	js_gz|=8;;
	if(js_gz!=0)
	return	js_gz;
	js_d1=(js_d1-0x30)*10;
	js_data+=js_d1;
	js_d1=rx.data[8];
	if(js_d1<=0x2f)
	js_gz|=4;
	if(js_d1>=0x3a)
	js_gz|=8;
	if(js_gz!=0)
	return	js_gz;
	js_d1=js_d1-0x30;
	js_data+=js_d1;

	return 0;
}
/***********************************************************************************************************************
* Description  : UART data validity and data conversion
***********************************************************************************************************************/
unsigned char RXDATAJS4(void)
{
	unsigned char js_d1;
	unsigned char js_gz=0;
	if(rx.data[15]!=11)
	return	js_gz=0x80;

	js_d1=rx.data[6];
	if(js_d1<=0x2f)
	js_gz|=1;
	if(js_d1>=0x47)
	js_gz|=2;;
	if(js_gz!=0)
	return	js_gz;
	if(js_d1>=0x41)
	js_d1-=0x37;
	else
	js_d1-=0x30;
	js_datal.m4=js_d1;

	js_d1=rx.data[7];
	if(js_d1<=0x2f)
	js_gz|=1;
	if(js_d1>=0x47)
	js_gz|=2;
	if(js_gz!=0)
	return	js_gz;
	if(js_d1>=0x41)
	js_d1-=0x37;
	else
	js_d1-=0x30;
	js_datal.m3=js_d1;

	js_d1=rx.data[8];
	if(js_d1<=0x2f)
	js_gz|=1;
	if(js_d1>=0x47)
	js_gz|=2;
	if(js_gz!=0)
	return	js_gz;
	if(js_d1>=0x41)
	js_d1-=0x37;
	else
	js_d1-=0x30;
	js_datal.m2=js_d1;

	js_d1=rx.data[9];
	if(js_d1<=0x2f)
	js_gz|=1;
	if(js_d1>=0x47)
	js_gz|=2;
	if(js_gz!=0)
	return	js_gz;
	if(js_d1>=0x41)
	js_d1-=0x37;
	else
	js_d1-=0x30;
	js_datal.m1=js_d1;
	return 0;
}

/* End user code. Do not edit comment generated here */
