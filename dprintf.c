/*
 * $Id: dprintf.c 1.5 1998/04/12 17:29:04 olsen Exp olsen $
 *
 * :ts=4
 *
 * Wipeout -- Traces and munges memory and detects memory trashing
 *
 * Written by Olaf `Olsen' Barthel <olsen@sourcery.han.de>
 * Public Domain
 */

#ifndef _GLOBAL_H
#include "global.h"
#endif	/* _GLOBAL_H */

/******************************************************************************/

typedef VOID (PUTCHAR)(UBYTE c __asm("d0"),APTR putChData __asm("a3"));

/******************************************************************************/

/* these are in rawio.asm */
//extern VOID SerPutChar(UBYTE c __asm("d0"),APTR putChData __asm("a3"));
extern VOID ParPutChar(UBYTE c __asm("d0"),APTR putChData __asm("a3"));

/******************************************************************************/

//STATIC PUTCHAR putChar = SerPutChar;

/******************************************************************************/

VOID
ChooseParallelOutput(VOID)
{
	Forbid();

	/* use the parallel port output routine. */
	kprintf("not support to use parallel output\n");
	//putChar = ParPutChar;

	Permit();
}

#define REG_A3 __asm("a3")
#define REG_D0 __asm("d0")

/******************************************************************************/
struct RawDoFmtData
{
STRPTR buffer;
LONG  length;
LONG  result;
};
STATIC VOID Stuffer(void)
{
register struct RawDoFmtData *data REG_A3;
register UBYTE c REG_D0;
data->result++;

//if (data->length > 0)
{
 //if (data->length == 1)
 // c = '\0';

 *data->buffer++ = c;
 data->length--;
}
}

long VSNPrintf(UBYTE *buffer,long buffersize,CONST UBYTE *string, APTR args)
{
	struct RawDoFmtData data;
	data.result = 0;
	data.length = buffersize;
	data.buffer = buffer;
	RawDoFmt(string, args, (VOID (*)())&Stuffer, &data);
    return data.result;
}
char buff[32768];
static const UWORD SerPutChar[] =
{
0x16C0, /* move.b d0,(a3)+ */
0x4E75, /* rts */
};


VOID
DVPrintf(const STRPTR format,const va_list varArgs)
{
	/* printf() style text formatting and output */
	RawDoFmt((STRPTR)format,(APTR)varArgs,&SerPutChar,&buff[0]);
	kprintf("%s",&buff[0]);
}

VOID
DPrintf(const STRPTR format,...)
{
	va_list varArgs;

	/* printf() style text formatting and output, varargs version */

	va_start(varArgs,format);
	DVPrintf(format,varArgs);
	va_end(varArgs);
}
