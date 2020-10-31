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
 /*************************************************************************/
 /*                                                                       */
 /*                 Author: Richard Caley (rjc@cstr.ed.ac.uk)             */
 /*                   Date: Tue Mar 10 1998                               */
 /* --------------------------------------------------------------------  */
 /* Support functions for all matrix types.                               */
 /*                                                                       */
 /*************************************************************************/

#include <iostream>
#include "EST_TVector.h"
#include "EST_matrix_support.h"
#include "EST_bool.h"

using namespace std;

const std::ptrdiff_t EST_CURRENT=-1;
const std::ptrdiff_t EST_ALL=-1;

bool EST_matrix_bounds_check(int r,
			     int c,
			     int num_rows,
			     int num_columns,
			     bool set)
{
  const char *what = set?"set":"access";

  if ((r < 0) || (r >= num_rows))
    {
      cerr << "Tried to " << what << " row " << r << " of " << num_rows << " row matrix\n";
      return false;
    }
  if ((c < 0) || (c >= num_columns))
    {
	cerr << "Tried to " << what << " column " << c << " of " << num_columns << " column matrix\n";
	return false;
    }

  return true;
}

bool EST_matrix_bounds_check(int r, int nr,
			     int c, int nc,
			     int num_rows,
			     int num_columns,
			     bool set)
{
  const char *what = set?"set":"access";

  if (nr>0)
    {
      if ((r < 0) || (r >= num_rows))
	{
	  cerr << "Tried to " << what << " row " << r << " of " << num_rows << " row matrix\n";
	  return false;
	}
      if (r+nr-1 >= num_rows)
	{
	  cerr << "Tried to " << what << " row " << r+nr-1 << " of " << num_rows << " row matrix\n";
	  return false;
	}
    }
  if (nc>0)
    {
      if ((c < 0) || (c >= num_columns))
	{
	  cerr << "Tried to " << what << " column " << c << " of " << num_columns << " column matrix\n";
	  return false;
	}
      if (c+nc-1 >= num_columns)
	{
	  cerr << "Tried to " << what << " column " << c+nc-1 << " of " << num_columns << " column matrix\n";
	  return false;
	}
    }

  return true;
}

bool EST_vector_bounds_check(int c,
			     int num_columns,
			     bool set)
{
  const char *what = set?"set":"access";

  if ((c < 0) || (c >= num_columns))
    {
	cerr << "Tried to " << what << " column " << c << " of " << num_columns << " column vector\n";
	return false;
    }

  return true;
}

bool EST_vector_bounds_check(int c, int nc,
			     int num_columns,
			     bool set)
{
  const char *what = set?"set":"access";

  if (nc>0)
    {
      if ((c < 0) || (c >= num_columns))
	{
	  cerr << "Tried to " << what << " column " << c << " of " << num_columns << " column vector\n";
	  return false;
	}
      if (c+nc-1 >= num_columns)
	{
	  cerr << "Tried to " << what << " column " << c+nc-1 << " of " << num_columns << " column vector\n";
	  return false;
	}
    }
  return true;
}

