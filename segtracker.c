/*
 * $Id: segtracker.c 1.5 1998/05/31 10:11:16 olsen Exp olsen $
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

typedef char (* SegTrack(ULONG		Address __asm("a0"),
                             ULONG *	SegNum __asm("a1"),
                             ULONG *	Offset __asm("a2")));

struct SegSem
{
	struct SignalSemaphore	seg_Semaphore;
	SegTrack *				seg_Find;
};

/******************************************************************************/

BOOL
FindAddress(
	ULONG	address,
	LONG	nameLen,
	STRPTR	nameBuffer,
	ULONG *	segmentPtr,
	ULONG *	offsetPtr)
{
	struct SegSem * SegTracker;
	BOOL found = FALSE;

	Forbid();

	/* check whether SegTracker was loaded */
	SegTracker = (struct SegSem *)FindSemaphore("SegTracker");
	if(SegTracker != NULL)
	{
		STRPTR name;

		/* map the address to a name and a hunk/offset index */
		name = (*SegTracker->seg_Find)(address,segmentPtr,offsetPtr);
		if(name != NULL)
		{
			StrcpyN(nameLen,nameBuffer,name);

			found = TRUE;
		}
	}

	Permit();

	return(found);
}
