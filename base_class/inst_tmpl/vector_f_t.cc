 /************************************************************************/
 /*                                                                      */
 /*                Centre for Speech Technology Research                 */
 /*                     University of Edinburgh, UK                      */
 /*                       Copyright (c) 1996,1997                        */
 /*                        All Rights Reserved.                          */
 /*                                                                      */
 /*  Permission is hereby granted, free of charge, to use and distribute */
 /*  this software and its documentation without restriction, including  */
 /*  without limitation the rights to use, copy, modify, merge, publish, */
 /*  distribute, sublicense, and/or sell copies of this work, and to     */
 /*  permit persons to whom this work is furnished to do so, subject to  */
 /*  the following conditions:                                           */
 /*   1. The code must retain the above copyright notice, this list of   */
 /*      conditions and the following disclaimer.                        */
 /*   2. Any modifications must be clearly marked as such.               */
 /*   3. Original authors' names are not deleted.                        */
 /*   4. The authors' names are not used to endorse or promote products  */
 /*      derived from this software without specific prior written       */
 /*      permission.                                                     */
 /*                                                                      */
 /*  THE UNIVERSITY OF EDINBURGH AND THE CONTRIBUTORS TO THIS WORK       */
 /*  DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING     */
 /*  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT  */
 /*  SHALL THE UNIVERSITY OF EDINBURGH NOR THE CONTRIBUTORS BE LIABLE    */
 /*  FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES   */
 /*  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN  */
 /*  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,         */
 /*  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF      */
 /*  THIS SOFTWARE.                                                      */
 /*                                                                      */
 /************************************************************************/
 /*                                                                      */
 /*                 Author: Richard Caley (rjc@cstr.ed.ac.uk)            */
 /*                   Date: Tue Aug 26 1997                              */
 /* -------------------------------------------------------------------  */
 /* Instantiate float basic vector classes.                              */
 /*                                                                      */
 /************************************************************************/

#include "EST_TVector.h"
#include "EST_TSimpleVector.h"

Declare_TVector_Base(float, 0, -123.456)
Declare_TSimpleVector(float)

#if defined(INSTANTIATE_TEMPLATES)

#include "../base_class/EST_TSimpleVector.cc"
#include "../base_class/EST_TVector.cc"
#include "../base_class/EST_Tvectlist.cc"

Instantiate_TVector(float)
Instantiate_TSimpleVector(float)

EST_write_status save(const EST_String &filename, const EST_TVector<float> &a)
{
    int i;
    ostream *outf;
    EST_String s;
    if (filename == "-")
	outf = &std::cout;
    else
	outf = new std::ofstream(filename);
    
    if (!(*outf)) return misc_write_error;

    for (i = 0; i < a.n(); ++i)
    {
      *outf << a(i) << "\t";
    }
    *outf << std::endl;
    
    if (outf != &std::cout)
	delete outf;
    return write_ok;
}

#endif
