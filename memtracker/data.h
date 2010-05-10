/*
 * $Id: data.h,v 1.3 2007/02/19 21:40:51 laire Exp $
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

#ifndef global
#define global extern
#endif	/* global */

/******************************************************************************/

extern struct ExecBase *	SysBase;
extern struct DosLibrary *	DOSBase;

/******************************************************************************/
#ifdef __MORPHOS__
global struct Library * TimerBase;	/* required for GetSysTime() */
#endif
/******************************************************************************/

struct SegSem;
global struct SegSem * SegTracker;

/******************************************************************************/

global BYTE WakeupSignal;	/* this triggers the wipeout owner task. */

/******************************************************************************/

global UWORD PreWallSize;	/* number of bytes to precede every allocation. */
global UWORD PostWallSize;	/* number of bytes to follow every allocation. */

/******************************************************************************/

global BOOL IsActive;		/* is Wipeout active? */
global BOOL ShowFail;		/* show memory allocation failures? */
global BOOL WaitAfterHit;	/* wait for ^C after each hit? */
global BOOL NameTag;		/* tag all allocations with names? */
global BOOL NoReuse;		/* don't allow memory to be reused under Forbid()? */
global BOOL CheckConsistency; /* before memory is freed or allocated, check the 
                               * tracking list consistency
                               */

global LONG CheckDelay;		/* number of 1/10 seconds between memory checks. */
global LONG CheckOrphaned;	/* check for orphaned pool allocations, no really reliable because of AddTask Pool alloc/passing */

global BOOL ARegCheck;		/* run all address registers through SegTracker? */
global BOOL DRegCheck;		/* run all data registers through SegTracker? */
global BOOL StackCheck;		/* run stack contents through SegTracker? */
global LONG StackLines;		/* number of stack lines to show on each hit. */
global BOOL Quick;          /* enable the quick mode */
/******************************************************************************/

global UBYTE ProgramName[60]; /* program name: Wipeout */

/******************************************************************************/

global UBYTE GlobalNameBuffer[MAX_FILENAME_LEN];	/* global, shared name buffer */

/******************************************************************************/

global UBYTE GlobalDateTimeBuffer[2*LEN_DATSTRING+1]; /* global, shared date and time buffer */

/******************************************************************************/

global ULONG ModuleStart;
global ULONG ModuleSize;
global ULONG EmulationStart;
global ULONG EmulationSize;
