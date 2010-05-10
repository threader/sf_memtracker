/*
 * $Id: installpatches.c 1.6 1998/04/12 17:39:51 olsen Exp olsen $
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

#define LVOAllocMem         -198
#define LVOFreeMem          -210
#define LVOAllocVec         -684
#define LVOFreeVec          -690
#define LVOCreatePool       -696
#define LVODeletePool       -702
#define LVOAllocPooled      -708
#define LVOFreePooled      -714

/******************************************************************************/

typedef (* FPTR)();

/******************************************************************************/

/* library vector offsets from amiga.lib */
//extern ULONG FAR LVOAllocMem;
//extern ULONG FAR LVOFreeMem;
//extern ULONG FAR LVOAllocVec;
//extern ULONG FAR LVOFreeVec;
//extern ULONG FAR LVOCreatePool;
//extern ULONG FAR LVODeletePool;
//extern ULONG FAR LVOAllocPooled;
//extern ULONG FAR LVOFreePooled;

/******************************************************************************/

/* these are in patches.asm */
//extern APTR ASM NewAllocMemFrontEnd(REG(d0) ULONG	byteSize,
//                                    REG(d1) ULONG	attributes);
//
//extern VOID ASM NewFreeMemFrontEnd(REG(a1) APTR		memoryBlock,
//                                   REG(d0) ULONG	byteSize);
//
//extern APTR ASM NewAllocVecFrontEnd(REG(d0) ULONG	byteSize,
//                                    REG(d1) ULONG	attributes);
//
//extern VOID ASM NewFreeVecFrontEnd(REG(a1) APTR	memoryBlock);
//
//extern APTR ASM NewCreatePoolFrontEnd(REG(d0) ULONG	memFlags,
//                                      REG(d1) ULONG	puddleSize,
//                                      REG(d2) ULONG	threshSize);
//
//extern VOID ASM NewDeletePoolFrontEnd(REG(a0) APTR poolHeader);
//
//extern APTR ASM NewAllocPooledFrontEnd(REG(a0) APTR		poolHeader,
//                                       REG(d0) ULONG	memSize);
//
//extern VOID ASM NewFreePooledFrontEnd(REG(a0) APTR	poolHeader,
//                                      REG(a1) APTR	memoryBlock,
//                                      REG(d0) ULONG	memSize);

/******************************************************************************/

#undef global
#define global

/* declare the vector stubs */
#include "installpatches.h"

/******************************************************************************/

VOID
InstallPatches(VOID)
{
	Forbid();

	/* the function pointers returned by SetFunction() do not exactly match
	 * the pointer types they are assigned to; I hate to typedef them all,
	 * so I just tell the compiler not show warning messages for this kind
	 * of problem
	 */
	#ifdef __SASC
	{
		#pragma msg 225 ignore push
	}
	#endif /* __SASC */

	/* redirect all these memory allocation routines to our monitoring code */
	OldAllocMem		= (FPTR)SetFunction((struct Library *)SysBase,LVOAllocMem,		(ULONG (*)())NewAllocMem_FrontEnd);
	OldFreeMem		= (FPTR)SetFunction((struct Library *)SysBase,LVOFreeMem,		(ULONG (*)())NewFreeMem_FrontEnd);
//
    OldAllocVec		= (FPTR)SetFunction((struct Library *)SysBase,LVOAllocVec,		(ULONG (*)())NewAllocVec_FrontEnd);
	OldFreeVec		= (FPTR)SetFunction((struct Library *)SysBase,LVOFreeVec,		(ULONG (*)())NewFreeVec_FrontEnd);

	/* the following do not exist in Kickstart 2.04 */
	if(SysBase->LibNode.lib_Version >= 39)
	{
		OldCreatePool	= (FPTR)SetFunction((struct Library *)SysBase,LVOCreatePool,		(ULONG (*)())NewCreatePool_FrontEnd);
		OldDeletePool	= (FPTR)SetFunction((struct Library *)SysBase,LVODeletePool,		(ULONG (*)())NewDeletePool_FrontEnd);

		OldAllocPooled	= (FPTR)SetFunction((struct Library *)SysBase,LVOAllocPooled,	(ULONG (*)())NewAllocPooled_FrontEnd);
		OldFreePooled	= (FPTR)SetFunction((struct Library *)SysBase,LVOFreePooled,		(ULONG (*)())NewFreePooled_FrontEnd);
	}



	#ifdef __SASC
	{
		#pragma msg 225 pop
	}
	#endif /* __SASC */

	Permit();
}
