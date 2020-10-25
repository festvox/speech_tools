/*************************************************************************/
/*                                                                       */
/*                Centre for Speech Technology Research                  */
/*                     University of Edinburgh, UK                       */
/*                         Copyright (c) 1998                            */
/*                        All Rights Reserved.                           */
/*  Permission is hereby granted, free of charge, to use and distribute  */
/*  this software and its documentation without restriction, including   */
/*  without limitation the rights to use, copy, modify, merge, publish,  */
/*  distribute, sublicense, and/or sell copies of this work, and to      */
/*  permit persons to whom this work is furnished to do so, subject to   */
/*  the following conditions:                                            */
/*   1. The code must retain the above copyright notice, this list of    */
/*      conditions and the following disclaimer.                         */
/*   2. Any modifications must be clearly marked as such.                */
/*   3. Original authors' names are not deleted.                         */
/*   4. The authors' names are not used to endorse or promote products   */
/*      derived from this software without specific prior written        */
/*      permission.                                                      */
/*  THE UNIVERSITY OF EDINBURGH AND THE CONTRIBUTORS TO THIS WORK        */
/*  DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING      */
/*  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT   */
/*  SHALL THE UNIVERSITY OF EDINBURGH NOR THE CONTRIBUTORS BE LIABLE     */
/*  FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES    */
/*  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN   */
/*  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,          */
/*  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF       */
/*  THIS SOFTWARE.                                                       */
/*                                                                       */
/*************************************************************************/
/*                       Author :  Alan W Black                          */
/*                       Date   :  February 1998                         */
/* --------------------------------------------------------------------- */
/*   Functions for LIST relations                                        */
/*                                                                       */
/*************************************************************************/
#ifndef __EST_RELATION_LIST_H__
#define __EST_RELATION_LIST_H__

#include "EST_Item.h"

/** Given a node `l`, return true if
    `c` after it in a list relation. */
int in_list(const EST_Item *c, const  EST_Item *l);


/** Add a item after node `n`, and return the new
item. If `n` is the first item in the list, the 
new item becomes the head of the list, otherwise it is inserted between
`n` and it's previous current item.
If `p` is 0, make a new node for the new
item, otherwise add `p` to this relation as the
next item in `n`'s relation.  */

EST_Item *add_after(const EST_Item *n, EST_Item *p=0);

/** Add a item before node `n`, and return the new
item. If `n` is the first item in the list, the 
new item becomes the head of the list, otherwise it is inserted between
`n` and it's previous current item.
If `p` is 0, make a new node for the new
item, otherwise add `p` to this relation as the
previous item in `n`'s relation.  */

EST_Item *add_before(const EST_Item *n, EST_Item *p=0);

/** Remove the given item.
*/

void remove_item_list(EST_Relation *rel, EST_Item *n);

//@}
//@}
#endif
