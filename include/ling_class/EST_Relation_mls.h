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
/*   Functions for Multi-linear structure relations                      */
/*                                                                       */
/*************************************************************************/
#ifndef __EST_RELATION_MLS_H__
#define __EST_RELATION_MLS_H__

#include "EST_Item.h"

inline EST_Item *link1(EST_Item *n) { return idown(idown(idown(n))); }
inline EST_Item *link2(EST_Item *n) { return idown(inext(idown(idown(n)))); }
inline EST_Item *linkn(EST_Item *n) { return idown(last(idown(idown(n)))); }

EST_Item *link(int l,EST_Item *n);

inline EST_Item *linkedfrom(EST_Item *n) { return iup(iup(first(iup(n)))); }
int linked(EST_Item *from, EST_Item *to);

 inline EST_Item *next_link(EST_Item *n) { return idown(inext(iup(n))); }

void add_link(EST_Item *from, EST_Item *to);
void remove_link(EST_Item *from, EST_Item *to);

#endif
