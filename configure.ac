dnl########################################################################
dnl                                                                      ##
dnl               Centre for Speech Technology Research                  ##
dnl                    University of Edinburgh, UK                       ##
dnl                      Copyright (c) 1996-2001                         ##
dnl                       All Rights Reserved.                           ##
dnl                                                                      ##
dnl Permission is hereby granted, free of charge, to use and distribute  ##
dnl this software and its documentation without restriction, including   ##
dnl without limitation the rights to use, copy, modify, merge, publish,  ##
dnl distribute, sublicense, and/or sell copies of this work, and to      ##
dnl permit persons to whom this work is furnished to do so, subject to   ##
dnl the following conditions:                                            ##
dnl  1. The code must retain the above copyright notice, this list of    ##
dnl     conditions and the following disclaimer.                         ##
dnl  2. Any modifications must be clearly marked as such.                ##
dnl  3. Original authors' names are not deleted.                         ##
dnl  4. The authors' names are not used to endorse or promote products   ##
dnl     derived from this software without specific prior written        ##
dnl     permission.                                                      ##
dnl                                                                      ##
dnl THE UNIVERSITY OF EDINBURGH AND THE CONTRIBUTORS TO THIS WORK        ##
dnl DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING      ##
dnl ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT   ##
dnl SHALL THE UNIVERSITY OF EDINBURGH NOR THE CONTRIBUTORS BE LIABLE     ##
dnl FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES    ##
dnl WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN   ##
dnl AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,          ##
dnl ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF       ##
dnl THIS SOFTWARE.                                                       ##
dnl                                                                      ##
dnl########################################################################
AC_PREREQ([2.69])
AC_INIT
AC_CONFIG_SRCDIR([include/EST.h])

AC_CANONICAL_TARGET
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB
AC_CHECK_TOOL(AR, ar)

AC_C_BIGENDIAN

AC_CHECK_LIB(ncurses, tputs, [TERMCAPLIB=-lncurses], [TERMCAPLIB=-lcurses])
dnl if test "$TERMCAPLIB" != "-ltermcap"; then
dnl    AC_CHECK_LIB(termcap, tputs, [TERMCAPLIB=-ltermcap], [TERMCAPLIB=-lncurses])
dnl 
AC_SUBST(TERMCAPLIB)

dnl Which compiler do we have here
AC_ARG_VAR(COMPILERTYPE, [compiler profile to use from config/compilers. This
           is used to set compiler flags on libraries and source file dependency resolution])
dnl If the user has not set COMPILERTYPE, check for some compilers:
if test "x${COMPILERTYPE}" = "x"; then
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <stdio.h>]], [[int j= 
                #if __GNUC__ == 2 && __GNUC_MINOR__ == 95
                3;
                #endif ]])],[COMPILERTYPE=gcc295],[])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <stdio.h>]], [[int j= 
                #if __GNUC__ == 3 
                3;
                #endif ]])],[COMPILERTYPE=gcc32],[])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <stdio.h>]], [[ int j=
                #if __GNUC__ == 2 && __GNUC_MINOR__ == 96
                3;
                #endif ]])],[COMPILERTYPE=gcc296],[])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <stdio.h>]], [[int j=
                #if __GNUC__ == 2 && __GNUC_MINOR__ == 91
                3;
                #endif ]])],[COMPILERTYPE=egcs],[])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <stdio.h>]], [[int j=
                #if __GNUC__ == 2 && __GNUC_MINOR__ == 8
                3;
                #endif ]])],[COMPILERTYPE=gcc28],[])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <stdio.h>]], [[int j =
                #if defined(__GNUC__)
                3;
                #endif ]])],[COMPILERTYPE=gcc],[])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <stdio.h>]], [[int j =
                #if defined(__clang__)
                3;
                #endif ]])],[COMPILERTYPE=clang],[])
fi
dnl If the user has not set COMPILERTYPE and the checks did not deliver
dnl results, set COMPILERTYPE to basename $CC.
if test "x${COMPILERTYPE}" = "x"; then
    COMPILERTYPE=`basename $CC`
fi
AC_SUBST(COMPILERTYPE)

AC_ARG_VAR(SHARED, [SHARED=0 does not build shared libraries. SHARED=1 builds
 static libraries. SHARED=2 builds shared libraries.])
if test "x${SHARED}" = "x"; then
    SHARED=0
fi

AC_ARG_VAR(DEBUG, [DEBUG=0 does not append debug flags. DEBUG=1 appends debug
 flags. Flags can also be passed using CFLAGS])
if test "x${DEBUG}" = "x"; then
    DEBUG=0
fi

AC_ARG_VAR(OPTIMISE, [Choose optimization level from 0 to 4. Default 3. Level 4 disables debug. ])
if test "x${OPTIMISE}" = "x"; then
    OPTIMISE=3
fi
AC_SUBST(OPTIMISE)

AC_ARG_VAR(WARN, [ Enable warning flags (WARN=1) or disable them (WARN=0) ])
if test "x${WARN}" = "x"; then
    WARN=1
fi
AC_SUBST(WARN)

AC_ARG_VAR(PROFILE, [ Enable a profiled build (e.g. PROFILE=gprof, PROFILE=gcov) ])
if test "x${PROFILE}" = "x"; then
    PROFILE=
fi
AC_SUBST(PROFILE)

LINUXAUDIO=none
AC_CHECK_HEADER(alsa/asoundlib.h,
              [LINUXAUDIO="alsa"])
AC_SUBST(LINUXAUDIO)

AC_ARG_WITH([nas_audio],
            [AS_HELP_STRING([--with-nas_audio],
              [enable NCD's network audio system])],
            [NAS_AUDIO=NAS_AUDIO],
            [NAS_AUDIO=])
AC_SUBST(NAS_AUDIO)

AC_ARG_WITH([pulseaudio],
  [AS_HELP_STRING([--with-pulseaudio],
  [Compile PulseAudio audio module @<:@default=no@:>@])],
  [],
  [with_pulseaudio=no])


PULSE_AUDIO=
AS_IF([test "x$with_pulseaudio" != xno],
      [PULSE_AUDIO="PULSE_AUDIO"],
      []
)

AC_SUBST(PULSE_AUDIO)

OMP_OPTS=
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <omp.h>]], [[ int j=1;]])],[OMP_OPTS="-fopenmp"],[])
AC_SUBST(OMP_OPTS)
OMP_DEFS=
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <omp.h>]], [[ int j=1;]])],[OMP_DEFS="-DOMP_WAGON=1"],[])
AC_SUBST(OMP_DEFS)

AC_CONFIG_FILES([config/config config/user_flags.mak])
AC_OUTPUT
