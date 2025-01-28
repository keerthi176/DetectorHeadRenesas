// Device     : RL78/R5F10268
// File Name  : main.h
// Date       : 2022/12/28
// Version    : 1.2
/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#include "iodefine.h"
#include "r_cg_serial.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
typedef volatile union {
    struct {
      	unsigned char L;
	unsigned char H;
    };
	unsigned int	I;
}IM;

 typedef volatile union {
    struct {
      	unsigned char m1;
	unsigned char m2;
	unsigned char m3;
	unsigned char m4;
    };
	unsigned long	L;
}LM;

typedef union
{
struct  {
	unsigned	S1:1;
	unsigned	S0:1;
	unsigned	H1:1;
	unsigned	H0:1;
	unsigned	PIR:1;
}c;
	unsigned char 	event;
}ev;

typedef union
{
struct  {
	unsigned	S:1;
	unsigned	H:1;
	unsigned 	CO:1;
	unsigned	PIR:1;
}c;
	unsigned char 	event;
}ev1;

typedef union  {
struct {
	unsigned char   st1;
	unsigned char   st[15];
	unsigned long   ml;
	}c;
	unsigned char	data[20];
}rxxx;

typedef union
{
struct {
	unsigned int  g_uart0_tx_count;
	unsigned char	TX_DATA[20];
}c;
	unsigned char data[22];
}txxx;

typedef struct  {
	unsigned	JKJC:1;
	unsigned	Y_YWB:1;
	unsigned	Y_HWB:1;
	unsigned	S_STH0:1;
	unsigned	H_HTH0:1;
	unsigned	TXWC:1;
	unsigned 	ROMTX:1;
	unsigned   	PIR_30S_E:1;
	unsigned	TIME_W:1;
	unsigned	HEAT_GZ : 1;
	unsigned	YBTXQL:1;
	unsigned	int_200ms:1;
}F1;
typedef union  {
	struct {
	unsigned	SDIRB:1;
	unsigned 	SMOKE_GZ : 1;
	unsigned	EER_SDGZ:1;
	unsigned	EEW_SDGZ:1;
	}c;
	unsigned char IG;
}F2;
typedef union
{
struct {
unsigned int  H_ADCYZL,S_ADCYZL,S_ADCYZ;
unsigned int H_BDAT1,H_BDAT2,H_BDAT3,H_BDAT4,H_PGZ;
unsigned int wsb_time;
unsigned int RESULT1,RESULT2,RESULT3,RESULT4,S_PGZ;
unsigned int SMOKE_VALUE,SMOKE_NO_ALARM_VALUE,SMOKE_NEWZERO_XDD;
unsigned int SMOKE_NEWZERO_VALUE,SMOKE_ALARM_VALUE;
unsigned int  MCNT1,MCNT2;
unsigned char SGZJSQ;
unsigned char HGZJSQ;
}c;
	unsigned char data[45];
}dttt;
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define H_ADCYZL dd.c.H_ADCYZL	//Sampling heat  value
#define S_ADCYZL dd.c.S_ADCYZL	//Sampling smoke value
#define S_ADCYZ dd.c.S_ADCYZ	//Sampling smoke value
#define H_BDAT1 dd.c.H_BDAT1	//Sampling heat  preservation value
#define H_BDAT2 dd.c.H_BDAT2	//Sampling heat  preservation value
#define H_BDAT3 dd.c.H_BDAT3	//Sampling heat  preservation value
#define H_BDAT4 dd.c.H_BDAT4	//Sampling heat  preservation value
#define H_PGZ dd.c.H_PGZ	//Sampling heat  average value
#define wsb_time dd.c.wsb_time	//Temperature rise timer
#define RESULT1 dd.c.RESULT1	//Sampling smoke  preservation value
#define RESULT2 dd.c.RESULT2	//Sampling smoke  preservation value
#define RESULT3 dd.c.RESULT3	//Sampling smoke  preservation value
#define RESULT4 dd.c.RESULT4	//Sampling smoke  preservation value
#define S_PGZ dd.c.S_PGZ	//Sampling smoke  average value
#define SMOKE_VALUE dd.c.SMOKE_VALUE	//Sampling smoke Difference
#define SMOKE_NO_ALARM_VALUE dd.c.SMOKE_NO_ALARM_VALUE	//At smoke concentration exits
#define SMOKE_NEWZERO_XDD dd.c.SMOKE_NEWZERO_XDD	//At maximum smoke concentration
#define SMOKE_NEWZERO_VALUE dd.c.SMOKE_NEWZERO_VALUE	//Update background value
#define SMOKE_ALARM_VALUE dd.c.SMOKE_ALARM_VALUE	//Smoke alarm threshold
#define MCNT1 dd.c.MCNT1		//1 hour timer
#define MCNT2 dd.c.MCNT2
#define SGZJSQ dd.c.SGZJSQ		//Smoke fault count
#define HGZJSQ dd.c.HGZJSQ		//Heat fault count

