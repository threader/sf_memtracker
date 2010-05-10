/*
 * $Id: installpatches.h,v 1.2 2006/02/02 17:45:35 laire Exp $
 *
 * :ts=4
 *
 * Wipeout -- Traces and munges memory and detects memory trashing
 *
 * Written by Olaf `Olsen' Barthel <olsen@sourcery.han.de>
 * Public Domain
 */

#ifndef _INSTALLPATCHES_H
#define _INSTALLPATCHES_H 1

/****************************************************************************/
 
#ifndef global
#define global extern
#endif	/* global */

/****************************************************************************/

/* this defines the function pointers the original memory allocation routines
 * will respond to after we have patched them.
 */

//global APTR (*OldAllocMemAligned)(APTR SysBase, ULONG size, ULONG attr, ULONG align, ULONG offset);
//global APTR OldAllocMem;
APTR (*OldAllocMem)(register ULONG size __asm("d0"),
                                register ULONG flags  __asm("d1"),
                                register APTR SysBase __asm("a6"));
//global APTR OldFreeMem;
APTR (*OldFreeMem)(register APTR mem __asm("a1"),
                                register ULONG size  __asm("d0"),
                                register APTR SysBase __asm("a6"));
//global APTR (*OldAllocVecAligned)(APTR SysBase, ULONG size, ULONG attr, ULONG align, ULONG offset);
//global APTR OldAllocVec;
APTR (*OldAllocVec)(register ULONG size __asm("d0"),
                                register ULONG flags  __asm("d1"),
                                register APTR SysBase __asm("a6"));
//global APTR OldFreeVec;
APTR (*OldFreeVec)(register APTR mem __asm("a1"),
                                register APTR SysBase __asm("a6"));
//global APTR OldCreatePool;
APTR (*OldCreatePool)(register ULONG memFlags __asm("d0"),
                                register ULONG puddleSize  __asm("d1"),
                                register ULONG treshSize  __asm("d2"),
                                register APTR SysBase __asm("a6"));
//global APTR OldDeletePool;
void (*OldDeletePool)(register struct ProtectedPool *pool __asm("a0"),register APTR SysBase __asm("a6"));
//global APTR OldFlushPool;
//global APTR (*OldAllocPooledAligned)(APTR SysBase, APTR pool, ULONG size, ULONG align, ULONG offset);
//global APTR OldAllocPooled;
APTR (*OldAllocPooled)(register struct Pool *pool __asm("a0"),
                                register ULONG size  __asm("d0"),
                                register APTR SysBase __asm("a6"));
//global APTR OldFreePooled;
void (*OldFreePooled)(register struct ProtectedPool *pool __asm("a0"),
                                register APTR *memory __asm("a1"),
                                register ULONG size  __asm("d0"),
                                register APTR SysBase __asm("a6")
                                );
//global APTR OldAllocVecPooled;
//global APTR OldFreeVecPooled;

/****************************************************************************/

#endif /* _INSTALLPATCHES_H */
