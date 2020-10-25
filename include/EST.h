/*************************************************************************/
/*                                                                       */
/*                Centre for Speech Technology Research                  */
/*                     University of Edinburgh, UK                       */
/*                         Copyright (c) 1996                            */
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
/*    Authors:  Paul Taylor, Simon King, Alan Black, Richard Caley       */
/*                Date   :  June 1994-March 1997                         */
/*-----------------------------------------------------------------------*/
/*           Edinburgh Speech Tools General Header File                  */
/*                                                                       */
/*=======================================================================*/
#ifndef __EST_H__
#define __EST_H__

/** \defgroup basicclasses Basic Classes
 */

/** \defgroup containerclasses Container Classes
 *  \ingroup basicclasses
 *  \brief Classes useful to contain other objects
 */
 
/** \defgroup stringclasses String Classes
 *  \ingroup basicclasses
 *  \brief Classes useful to work with text and strings
 */

/** \defgroup supportclasses Support Classes
 *  \ingroup basicclasses
 *  \brief Classes used as a support to other classes
 */

// Standard include files.
#include "EST_system.h"
#include <cstdlib>

#include "EST_String.h"
#include "EST_string_aux.h"
#include "EST_types.h"

// Utilities
#include "EST_util_class.h"

#include "EST_cutils.h"
#include "EST_io_aux.h"

// Audio I/O
#include "EST_audio.h"

// Speech Classes
#include "EST_speech_class.h"

// Linguistic Classes
#include "EST_ling_class.h"

// Signal Processing
#include "EST_sigpr.h"

// Grammar
#include "EST_grammar.h"

// Stats
#include "EST_stats.h"

#endif /* __EST_H__ */
