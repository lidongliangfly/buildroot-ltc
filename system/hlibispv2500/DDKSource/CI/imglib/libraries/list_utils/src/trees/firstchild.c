/*
******************************************************************************
*
*               file : firstchild.c
*             author : Imagination Technolgies
*          copyright : 2002,2005 by Imagination Technologies.
*                      All rights reserved.
*                      No part of this software, either material or conceptual
*                      may be copied or distributed, transmitted, transcribed,
*                      stored in a retrieval system or translated into any
*                      human or computer language in any form by any means,
*                      electronic, mechanical, manual or otherwise, or
*                      disclosed to third parties without the express written
*                      permission of:
*                        Imagination Technologies, Home Park Estate,
*                        Kings Langley, Hertfordshire, WD4 8LZ, U.K.
*
******************************************************************************
*/
/*
******************************************************************************
*/
//#include <metag/machine.inc>
#include "tre.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

/*
 ** FUNCTION:      TRE_firstChild
 **
 ** DESCRIPTION:   Locate first child.
 **                Relies on property that siblings are contiguous within the tree list.
 **
 ** RETURNS:       void *
 */

void           *
TRE_firstChild(void *item)
{
    void           *parent;

    parent = item;

    /*
     * Use property that children always subsequent to parents 
     */
    item = ((TRE_LINKAGE_T *) item)->next;

    /*
     * search by trial and error 
     */
    while (item != NULL) {
	if (((TRE_LINKAGE_T *) item)->parent == parent)
	    break;
	item = ((TRE_LINKAGE_T *) item)->next;
    }
    return (item);
}