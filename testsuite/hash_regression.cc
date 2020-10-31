
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
 /*                 Author: Richard Caley (rjc@cstr.ed.ac.uk)            */
 /*                   Date: Wed Apr  9 1997                              */
 /************************************************************************/
 /*                                                                      */
 /* Simple inverted index as a test of the hash type.                    */
 /*                                                                      */
 /************************************************************************/

#include <iostream>
#include <fstream>
#include "EST_String.h"
#include "EST_Token.h"
#include "EST_THash.h"

using namespace std;

#define LINE_LENGTH 1000

EST_Regex RX_Word("[A-Z]?[a-z]+\\('[a-z]+\\)?");

#define WORD "Latitude"

int
main(int argc, const char *argv[])
{
  EST_TStringHash<int> places(10);
  int line_no = 1;
  EST_TokenStream file;

  if (argc != 2)
    return 1;

  if (file.open(argv[1]) != 0) {
    return -1;
  }
  file.set_WhiteSpaceChars("");
  file.set_SingleCharSymbols("\n");
  file.set_PunctuationSymbols("");
  file.set_PrePunctuationSymbols("");

while(! file.eof())
  {
    EST_String line;

    line = (EST_String)file.get();

    if (file.eof())
      break;

    if (line == "\n")
	line_no++;

    int p=0, len;

    while((p = line.search(RX_Word, len, p)) >= 0)
      {
	EST_String word(line.at(p, len));

	places.add_item(word, line_no);
	p += len;
      }
  }

cout << WORD "  is on line " << places.val(WORD) << "\n";

places.dump(cout);

return 0;
}

