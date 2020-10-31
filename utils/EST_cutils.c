/*************************************************************************/
/*                                                                       */
/*                Centre for Speech Technology Research                  */
/*                     University of Edinburgh, UK                       */
/*                       Copyright (c) 1996,1997                         */
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
/*                 Author :  Alan W Black and Paul Taylor                */
/*                 Date   :  July 1996                                   */
/*-----------------------------------------------------------------------*/
/*               Various Low level C utilities                           */
/*                                                                       */
/*=======================================================================*/
#define _POSIX_C_SOURCE 200809L
#include "EST_cutils.h"
#include "EST_unix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define _S_S_S(S) #S
#define STRINGIZE(S) _S_S_S(S)

const char * const est_tools_version = 
     STRINGIZE(ESTVERSION) ":" STRINGIZE(ESTSTATE) " " STRINGIZE(ESTDATE) ;

const char * const est_name = STRINGIZE(ESTNAME);

#ifdef ESTLIBDIRC
#    define ESTLIBDIR STRINGIZE(ESTLIBDIRC)
#endif

#ifndef ESTLIBDIR
#define ESTLIBDIR "/usr/local/lib/speech_tools"
#endif

const char * est_libdir = ESTLIBDIR;

const char * const est_ostype = STRINGIZE(ESTOSTYPE);

#ifndef ESTRELLIBDIR
#define ESTRELLIBDIR NULL
#endif

static const char * const est_path_rel_bin = ESTRELLIBDIR;

static bool is_path_valid(const char *path)
{
  if (path == NULL) return false;
  const char *filename = "siod/init.scm";
  char *fname = malloc((strlen(path) + strlen(filename) + 1)*sizeof(char));
  if (fname == NULL) return false;
  sprintf(fname, "%s%s", path, filename);
  bool is_valid = access( fname, F_OK ) != -1;
  free(fname);
  return is_valid;
}

static bool get_current_binary_location(char *buf, size_t bufsize)
{
  /* There is not a standard way to do this in C99. Not all implementations have
     been tested */
  #if defined(_WIN32)
  DWORD r = GetModuleFileNameA(NULL, buf, bufsize);
  return r > 0 && r < bufsize;
  #elif defined(__APPLE__)
  uint32_t size = bufsize;
  return (_NSGetExecutablePath(buf, &size) == 0);
  #elif defined(__linux__)
  return (readlink("/proc/self/exe", buf, bufsize) > 0);
  #elif defined(__DragonFly__)
  return (readlink("/proc/curproc/file", buf, bufsize) > 0);
  #elif defined(__FreeBSD__)
  if (readlink("/proc/curproc/exe", buf, bufsize) > 0)
    return true;
  int mib[4];
  mib[0] = CTL_KERN;
  mib[1] = KERN_PROC;
  mib[2] = KERN_PROC_PATHNAME;
  mib[3] = -1;
  sysctl(mib, 4, buf, &bufsize, NULL, 0);
  return true;
  #elif defined(__NetBSD__)
  if (readlink("/proc/curproc/exe", buf, bufsize) > 0)
    return true;
  #elif defined(__OpenBSD__)
  buf[0] = '\0';
  return false; /* Not implemented */
  #elif defined(__sun) && defined(__SVR4) /* solaris */
  const char *res = getexecname();
  if (res == NULL) return false;
  if (snprintf(buf, bufsize, "%s", res) > 0) return true;
  #endif
  return false;
}

static bool chop_dirname(char *buf, size_t bufsize) {
  if (buf == NULL) return false;
  ptrdiff_t buflen = (ptrdiff_t) strlen(buf);
  if (buflen == (ptrdiff_t) bufsize) return false;
  if (buflen == 0) return false;
  for (ptrdiff_t i = buflen - 1; i >= 0; --i) {
    if (buf[i] == '/' || buf[i] == '\\') {
      buf[i+1] = '\0';
      return true;
    }
  }
  return false;
}

char *get_estlibdir(const char *path, const char *path_rel_bin)
{
  /* Return the path to estlibdir. Search if any of the following are valid:
   * - The given path.
   *   + If path is a NULL pointer, it is ignored
   *   + Otherwise, path is searched.
   * - ESTLIBDIR environment variable
   * - Hardcoded path, if it is not NULL
   * - Relative paths to the executed binary location. 
   *   + If path_rel_bin is NULL, a hardcoded relative path is tested
   *   + Otherwise the current binary is located (on a best effort) and the relative
   *     path is tested
   *
   * A path is considered valid if there is a siod/init.scm file inside it.
   * If a path is valid, this function returns the path. You will have to free it.
   * If no path is valid, this function returns NULL
   */
  /* given paths */
  const char *candidate;
  if (is_path_valid(path)) {
    return wstrdup(path);
  }
  /* environment variable */
  candidate = getenv("ESTLIBDIR");
  if (is_path_valid(candidate)) {
    return wstrdup(candidate);
  }
  /* hardcoded value */
  if (is_path_valid(ESTLIBDIR)) {
    return wstrdup(ESTLIBDIR);
  }
  /* get path of the current binary */
  if (path_rel_bin == NULL) path_rel_bin = est_path_rel_bin;
  if (path_rel_bin == NULL) return NULL;
  size_t len_path_rel_bin = strlen(path_rel_bin);
  /* prevent overflow with a malformed path_rel_bin: */
  if (len_path_rel_bin > SIZE_MAX-8192) return NULL;
  char *buf = calloc(8192+len_path_rel_bin, sizeof(char));
  if (buf == NULL) return NULL;
  if (!get_current_binary_location(buf, 8191+len_path_rel_bin)) {
    free(buf);
    return NULL;
  }
  /* Directory where the current binary is */
  if (!chop_dirname(buf, 8191+len_path_rel_bin)) {
    free(buf);
    return NULL;
  }
  size_t len_dirname = strlen(buf);
  memcpy(buf + len_dirname, path_rel_bin, len_path_rel_bin*sizeof(char));
  buf[len_dirname + len_path_rel_bin] = '\0';
  if (is_path_valid(buf)) {
    char * out = wstrdup(buf);
    free(buf);
    return out;
  }
  free(buf);
  return NULL;
}

char *cmake_tmp_filename()
{
    char *tdir;
    char fname[1024];
    static int n=0;
    char *t1;
    int i,j;

    if (((tdir=getenv("TMPDIR")) == NULL) &&
	((tdir=getenv("TEMP")) == NULL) &&
	((tdir=getenv("TMP")) == NULL))
	tdir = "/tmp";
    
    t1 = wstrdup(tdir);

    /* If it contains a double quote there might be a security hole */
    for (j=i=0; t1[i] != '\0'; i++)
	if (t1[i] != '"')
	    t1[j++]=t1[i];

    sprintf(fname,"%s/est_%05ld_%05d",t1,(long)getpid(),n++);
    return wstrdup(fname);
}

enum EST_bo_t str_to_bo(const char *boname)
{
    /* EST_String to byte order */

    if ((streq(boname,"hilo")) || (streq(boname,"big")) || 
	(streq(boname,"MSB")) ||  (streq(boname,"big_endian")))
	return bo_big;
    else if ((streq(boname,"lohi")) || (streq(boname,"little")) || 
	     (streq(boname,"LSB")) ||  (streq(boname,"little_endian")))
	return bo_little;
    else if ((streq(boname,"native")) || (streq(boname,"mine")))
	return (EST_BIG_ENDIAN ? bo_big : bo_little);
    else if ((streq(boname,"nonnative")) || (streq(boname,"other")) ||
	     (streq(boname,"wrong")) || (streq(boname,"swap")) ||
	     (streq(boname,"swapped")))
	return (EST_BIG_ENDIAN ? bo_little : bo_big);
    else
    {
	fprintf(stderr,"Unknown byte swap format: \"%s\" assuming native\n",
		boname);
	return (EST_BIG_ENDIAN ? bo_big : bo_little);
    }

}    

const char *bo_to_str(enum EST_bo_t bo)
{
    /* byte order to str */

    switch (bo)
    {
      case bo_big:    return "hilo";
      case bo_little: return "lohi";
      default:
	fprintf(stderr,"Unrecognized byte order %d\n",bo);
	return "unrecognized";
    }
}

