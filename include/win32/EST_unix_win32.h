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
 /*                   Date: Tue Sep4th 1997                               */
 /* --------------------------------------------------------------------  */
 /* Define unix things for win32.                                         */
 /*                                                                       */
 /*************************************************************************/


#if !defined(__EST_UNIX_WIN32_H__)
#define __EST_UNIX_WIN32_H__ 1

/* force this to be loaded first */
#ifdef __cplusplus
#include <iostream>
#endif

#include<stdint.h>

#ifdef __cplusplus
static inline int getpid(void)
	{ return (int)GetCurrentProcessId(); }
#else
#    define getpid() GetCurrentProcessId()
#endif

#ifdef __cplusplus
extern "C" {
#endif
  int unix_waitpid(int pid, int *statusp, int flags);
  int unix_fork(void);
#ifdef __cplusplus
}
#endif
#define waitpid(P, SP, FL) unix_waitpid((P), (SP), (FL))

#define WNOHANG 1

#define fork() unix_fork()

#define rint(N) ((float)(int)((N)+0.5))

#ifdef __cplusplus
extern "C" {
#endif
  int unix_access(const char *file, int mode);
#ifdef __cplusplus
}
#endif

#define access(FILE,MODE) unix_access(FILE, MODE)

#define F_OK 1
#define W_OK 2
#define R_OK 4

#ifdef __cplusplus
extern "C" {
#endif
  int unix_read(HANDLE fd, char *buffer, int n);
  int unix_write(HANDLE fd, const char *buffer, int n);
#ifdef __cplusplus
}
#endif

#define read(FD,B,N) _read((FD),(B),(N))

#ifdef __cplusplus
extern "C" {
#endif
  char *unix_getcwd(char *buffer, int maxlength);
#ifdef __cplusplus
}
#endif

#define getcwd(P, L) unix_getcwd((P), (L))
#define chdir(D) SetCurrentDirectory(D)

#if !defined(memcpy)
#   define memcpy(DST, SRC, N) CopyMemory((DST), (SRC), (N))
#endif

#endif
