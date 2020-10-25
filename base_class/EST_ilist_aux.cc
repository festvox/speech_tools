/*************************************************************************/
/*                                                                       */
/*                Centre for Speech Technology Research                  */
/*                     University of Edinburgh, UK                       */
/*                    Copyright (c) 1994,1995,1996                       */
/*                        All Rights Reserved.                           */
/*                                                                       */
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
/*                                                                       */
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
/*                      Author :  Paul Taylor, Simon King                */
/*                      Date   :  1994-99                                */
/*-----------------------------------------------------------------------*/
/*                    IList i/o utility functions                        */
/*                                                                       */
/*=======================================================================*/

#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include "EST_types.h"
#include "EST_String.h"
#include "EST_Pathname.h"
#include "EST_string_aux.h"
#include "EST_cutils.h"
#include "EST_Token.h"

int ilist_member(const EST_IList &l,int i)
{
    EST_Litem *p;
    for (p = l.head(); p != 0; p = p->next())
	if (l.item(p) == i)
	    return true;

    return false;
}

int ilist_index(const EST_IList &l,int i)
{
    EST_Litem *p;
    int j=0;
    for (p = l.head(); p != 0; p = p->next())
    {
	if (l.item(p) == i)
	    return j;
	j++;
    }

    return -1;
}


void IList_to_IVector(EST_IList &l, EST_IVector &v)
{
    int len,i;

    len = l.length();
    v.resize(len);

    //EST_TBI *p;
    EST_Litem *p;
    for (p = l.head(),i=0; p != 0; p = p->next(),i++)
	v[i] = l(p);
}


void IVector_to_IList(EST_IVector &v, EST_IList &l)
{
    int i;
    l.clear();
    for (i=0;i<v.length();i++)
      l.append(v[i]);
}


int IVector_index(const EST_IVector &v,const int s)
{
    int i;
    for(i=0;i<v.length();i++)
	if(v(i) == s)
	    return i;

    return -1;

}
