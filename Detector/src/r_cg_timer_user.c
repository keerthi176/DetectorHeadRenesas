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
* File Name    : r_cg_timer_user.c
* Version      : CodeGenerator for RL78/G12 V2.04.08.02 [03 Jun 2024]
* Device(s)    : R5F10268
* Tool-Chain   : CCRL
* Description  : This file implements device driver for TAU module.
* Creation Date: 28-01-2025
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_port.h"
#include "main.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_tau0_channel0_interrupt(vect=INTTM00)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
extern F1 flag;
extern unsigned char rx_bz;
extern unsigned char TX_TIME;
extern rxxx rx;
extern unsigned char TX;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_tau0_channel0_interrupt
* Description  : This function is INTTM00 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_tau0_channel0_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
	unsigned char t0_d1;
if(flag.TXWC==0)
{
rx_bz++;
if(rx_bz>=5)
RX_EEROR();
}
else
{
if(TX_TIME!=0)
	TX_TIME--;
if(TX_TIME==0)
   {
TX=1;
t0_d1=0X5;
while(--t0_d1);
flag.TXWC=0;
rx_bz=3;
TS0 |=0X001;
 PMK2 = 1U;
SS0 |= _0002_SAU_CH1_START_TRG_ON;
SRIF0 = 0U;
	SRMK0 = 0U;
}
 }
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Description  : UART receive error handlin
***********************************************************************************************************************/
void RX_EEROR(void)
{
	rx_bz=0;
	rx.data[15]=0;
	SRMK0 = 1U;
	ST0 |= _0002_SAU_CH1_STOP_TRG_ON ;
 	SRIF0 = 0U;
	TT0 |= 0X001;
    	TMMK00 = 1U;
    	TMIF00 = 0U;

	EGP0=0X00;
	PIF2 = 0U;
    	PMK2 = 0U;
}

/* End user code. Do not edit comment generated here */
