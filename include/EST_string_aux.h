/*************************************************************************/
/*                                                                       */
/*                Centre for Speech Technology Research                  */
/*                     University of Edinburgh, UK                       */
/*                     Copyright (c) 1994,1995,1996                      */
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
/*                    Author :  Paul Taylor, Simon King                  */
/*                    Date   :  1994-99                                  */
/*-----------------------------------------------------------------------*/
/*            Utility EST_String Functions header file                   */
/*                                                                       */
/*=======================================================================*/

#ifndef __EST_STRING_AUX_H__
#define __EST_STRING_AUX_H__

#include "EST_TList.h"
#include "EST_String.h"
#include "EST_types.h"
#include "EST_rw_status.h"

/** \defgroup utilityfunctionsforstrings Utility functions for strings
 */
 
 
/** \file
 *  \brief Utility EST_String Functions header file.
 *  \addtogroup utilityfunctionsforstrings
 *  @{
 *  \fn void StringtoStrList(EST_String s, EST_StrList &l, EST_String sep="")
 *  \brief Convert a EST_String to a EST_StrList by separating tokens in s delimited by the separator sep. By default, the string is assumed to be delimited by whitespace.
 *  \param s String to be split.
 *  \param l StringList the separated tokens will be stored.
 *  \param sep Token delimiter. By default, whitespace is used. 
 *  
 *  \fn void BracketStringtoStrList(EST_String s, EST_StrList &l, EST_String sep="")
 *  \brief Convert a EST_String enclosed in a single set of brackets to a EST_StrList by separating tokens in s delimited by the separator sep. By default, the string is assumed to be delimited by whitespace.
 *  \fn EST_read_status load_StrList(EST_String filename, EST_StrList &l)
 *  \brief Load tokens from a file and return them in a EST_StrList
 *  \fn EST_write_status save_StrList(EST_String filename, EST_StrList &l, EST_String style="words")
 *  \brief Save tokens from a EST_StrList. If style is set to "lines" each item is stored on a separate line, otherwise each item is separated by a single space.
 *  \fn void strip_quotes(EST_String &s, const EST_String quote_char="\"")
 *  \brief remove quotes from a string
 *  \fn EST_String itoString(int n)
 *  \brief Make a EST_String object from an integer
 *  \fn EST_String ftoString(float n, int pres=3, int width=0, int l=0)
 *  \brief Make a EST_String object from an float, with variable precision
 *  \fn int Stringtoi(EST_String s)
 *  \brief Make an int from a EST_String. EST_String equivalent of atoi()
 *  \fn int StrListtoIList(EST_StrList &s, EST_IList &il)
 *  \brief Convert a list of strings to a list of integers
 *  \fn int StrListtoFList(EST_StrList &s, EST_FList &il)
 *  \brief Convert a list of strings to a list of floats
 *  \fn void StrList_to_StrVector(EST_StrList &l, EST_StrVector &v)
 *  \brief Convert a list of strings to a vector of strings
 *  \fn void StrVector_to_StrList(EST_StrVector &v,EST_StrList &l)
 *  \brief Convert a vector of strings to a list of strings
 *  \fn int  StrVector_index(const EST_StrVector &v,const EST_String &s)
 *  \brief Search the vector and return the position of the first occurance of string s in the vector
 *  \fn int strlist_member(const EST_StrList &l,const EST_String &s)
 *  \brief Return true if s is in list l
 *  \fn int strlist_index(const EST_StrList &l,const EST_String &s)
 *  \brief Search the vector and return the position of the first occurance of string s in the list
 *  \fn EST_String basename(EST_String full, EST_String ext="")
 *  \brief This acts like the bourne shell basename command. By default, it strips any leading path from a string. If ext is defined, it strips any suffix matching this string.
 *  @}
 */

void StringtoStrList(EST_String s, EST_StrList &l, EST_String sep="");

void BracketStringtoStrList(EST_String s, EST_StrList &l, EST_String sep="");

EST_read_status load_StrList(EST_String filename, EST_StrList &l);
EST_write_status save_StrList(EST_String filename, EST_StrList &l, 
			      EST_String style="words");


void strip_quotes(EST_String &s, const EST_String quote_char="\"");

// makes EST_String from integer.
EST_String itoString(int n); 
// makes EST_String from float, with variable precision
EST_String ftoString(float n, int pres=3, int width=0, int l=0); 
int Stringtoi(EST_String s);

int StrListtoIList(EST_StrList &s, EST_IList &il);
int StrListtoFList(EST_StrList &s, EST_FList &il);

void StrList_to_StrVector(EST_StrList &l, EST_StrVector &v);
void StrVector_to_StrList(EST_StrVector &v,EST_StrList &l);
int  StrVector_index(const EST_StrVector &v,const EST_String &s);

int strlist_member(const EST_StrList &l,const EST_String &s);
int strlist_index(const EST_StrList &l,const EST_String &s);

// strips path off front of filename
EST_String basename(EST_String full, EST_String ext=""); 

// this is not the right place for these
void IList_to_IVector(EST_IList &l, EST_IVector &v);
void IVector_to_IList(EST_IVector &v,EST_IList &l);
int  IVector_index(const EST_IVector &v,const int s);

int ilist_member(const EST_IList &l,int i);
int ilist_index(const EST_IList &l,int i);

#endif // __EST_STRING_AUX_H__
