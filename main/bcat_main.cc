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
 /*                   Date: Thu Aug 14 1997                               */
 /* --------------------------------------------------------------------  */
 /* A simple file concatenator which does everything in binary            */
 /* mode. For use in the tests on Windows etc.                            */
 /*                                                                       */
 /*************************************************************************/


#include <cstdio>
#include "EST.h"
#include "EST_String.h"
#include "EST_error.h"

using namespace std;

#define BUFFER_SIZE (1024)


/** @name <command>bcat</command> <emphasis>Binary safe version of cat</emphasis>
    @id bcat-manual
  * @toc
 */

//@{


/**@name Synopsis
  */
//@{

//@synopsis

/**
bcat is a trivial file concatenation program. It exists to allow testing
of various file splitting operations under the cygwin environment on Windows
where the distinction between binary and text data is important.
 */

//@}

/**@name OPTIONS
  */
//@{

//@options

//@}


int main(int argc, char *argv[]) 
{ 
    EST_StrList files;
    EST_Option settings, cmd_line;

    parse_command_line
	(argc, argv, 
	 EST_String("-o [ofile] [files...]\n")+
	 "Summary; concatenate files in binary mode\n"+
	 "-o <ofile>       Output file of binary data\n",
	 files, cmd_line);

    EST_String out_file;

    if (cmd_line.present("-o"))
      out_file = cmd_line.val("-o");
    else
      EST_error("No output file specified");

    FILE *dest;

    if ((dest=fopen(out_file, "wb")) == NULL) {
      EST_sys_error("Can't create '%s'", (const char *)out_file);
      return -1;
    }

    EST_Litem *item;

    for(item=files.head(); item; item = item->next())
      {
	FILE *src;

	if ((src=fopen(files(item), "rb"))==NULL) {
	  EST_sys_error("can't read '%s'", (const char *)files(item));
	  return -1;
	}

	unsigned int n;
	char buf[BUFFER_SIZE];

	while((n=fread(buf, sizeof(char), BUFFER_SIZE, src)) >0)
	  if (fwrite(buf, sizeof(char), n, dest) < n)
	    EST_sys_error("write error");

	fclose(src);
      }

    fclose(dest);

    return 0;
}
	



