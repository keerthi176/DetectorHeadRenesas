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
* File Name    : r_cg_it.c
* Version      : CodeGenerator for RL78/G12 V2.04.08.02 [03 Jun 2024]
* Device(s)    : R5F10268
* Tool-Chain   : CCRL
* Description  : This file implements device driver for IT module.
* Creation Date: 28-01-2025
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_it.h"
/* Start user code for include. Do not edit comment generated here */
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
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_IT_Create
* Description  : This function initializes the IT module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IT_Create(void)
{
    TMKAEN = 1U;    /* supply IT clock */
    ITMC = _0000_IT_OPERATION_DISABLE;    /* disable IT operation */
    TMKAMK = 1U;    /* disable INTIT interrupt */
    TMKAIF = 0U;    /* clear INTIT interrupt flag */
    /* Set INTIT low priority */
    TMKAPR1 = 1U;
    TMKAPR0 = 1U;
    ITMC = _0BB7_ITMCMP_VALUE;
}

/***********************************************************************************************************************
* Function Name: R_IT_Start
* Description  : This function starts IT module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IT_Start(void)
{
    TMKAIF = 0U;    /* clear INTIT interrupt flag */
    TMKAMK = 0U;    /* enable INTIT interrupt */
    ITMC |= _8000_IT_OPERATION_ENABLE;    /* enable IT operation */
}

/***********************************************************************************************************************
* Function Name: R_IT_Stop
* Description  : This function stops IT module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IT_Stop(void)
{
    TMKAMK = 1U;    /* disable INTIT interrupt */
    TMKAIF = 0U;    /* clear INTIT interrupt flag */
    ITMC &= (uint16_t)~_8000_IT_OPERATION_ENABLE;    /* disable IT operation */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
