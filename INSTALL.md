# INSTALLATION

## Release notes

This documentation covers version 2.5.1 of the Edinburgh Speech Tools
Library. While previous versions of the speech tools were primarily
released solely to support the Festival Speech Synthesis System, the
Edinburgh Speech Tools Library now contains sufficiently useful tools
that it is of use in its own right.

Although hope that the speech tools has stabilised to a certain extent
and less structural changes will occur in future versions we don't
guaranteed future compatibility, although every effort will be made to
make upgrading as easy as possible. In addition, we warn that while
several programs and routines are quite mature, others are young and
have not be rigorously tested. Please do not assume these programs
work.

## Requirements

The Edinburgh Speech Tools provide a Makefile based build system and a new
build system based on meson (mesonbuild.com). This new build system has
the following advantages:

- Can use more than one process to build in parallel
- Honors --prefix to install in any directory
- Uses out-of-source builds (the build directory is not the source directory)
- Leverages meson standards for cross-compilation

However the meson-based build system has been less tested than the
Makefile-based system.

In order to compile and install the Edinburgh Speech Tools you need
the following:

### A C++ compiler

The current Edinburgh Speech Tools version aims to be compilable by any
C++-11 compliant compiler. We have tested both GCC and clang. We aim to
provide support for Visual C++ as well.

If you happen to require a code change for your specific platform, please
report it at https://github.com/festvox/speech_tools/issues.

### GNU make

If you want to use the Makefile-based build system, you will need make.
Any recent version will work, the various make programs that come with
different UNIX systems are wildly varying and hence it makes it too
difficult to write Makefiles which are portable, so we depend on a
version of make which is available for all of the platforms we are
aiming at.

### meson and ninja

If you want to use the meson-based build system, you will need meson.
Meson is a python3 based build system, so you will need to have python3
installed and then install meson. meson uses ninja as backend, so you may
want to install it as well. This is typically done using:

    pip3 install --user --upgrade meson ninja

## Supported Systems

We have successfully compiled and tested the speech tools on the
following systems, except where specified we include support for both
shared and static versions of the libraries:

Sun Sparc Solaris 2.5.1/2.6/2.7/2.9
      GCC 2.7.2, GCC 2.8.1, gcc-2.95.3, gcc-3.2 gcc-3.3

MacOS GCC 4.2.1 (Snow Leopard default)

Linux GCC 4.2 - 4.8.0

Windows 7/8 GCC (from Cygwin 1.7), Visual C++ (VS2010,VS2012).

We recommend the use of GCC 4.6 if you can use it, it is the most likely one to
work. Some of the compilers listed above produce a large number of
warnings when compiling the code.

Previous versions of the system have successfully compiled under SGI
IRIX 5.3, 6.x, OSF (Alphas) and HPUX but at time of writing this we have
not yet rechecked this version.  AIX4.3 probably works.


## Java is no longer supported!

The java directory contains optional Java classes which give some
access to speech tools facilities from Java programs.  This has been
created to support the fringe graphical interface. There are three
levels of support enabled by the JAVA JAVA_MEDIA and JAVA_CPP options
in the config file. JAVA compiles some very basic classes intended to
allow very simple simulation of speech tools facilities in pure Java
programs. JAVA_MEDIA is similar but uses the Jva Media Framework to
play sound. JAVA_CPP compiles classes which use the Java native
interface to provide access to the actual speech tools C++ classes.

You may (for instance on Solaris using gcc) need to make shared
libraries for some compiler support libraries in order to comple the
full JAVA_CPP support. See Appendix A for details.

## Windows 95/98/NT/XP/Vista/7/8 Port

We have done two ports of this code to Windows machines, one uses the
Cygwin package, which provides a Unix like environment under on Win32
systems, the other is a native port using Visual C++.

We recommend using only Windows 7.

The port using Visual C++ does not provide all of the
features of the Unix and Cygwin versions. You will need access to a
Unix or Cygwin system to create the makefiles used for the Visual C++
compilation.

Both Cygwin and Visual C++ ports have a number of limitations. 

Shared library creation is not supported.
      Creation of Windows DLLs is different enough from creation of Unix
      shared libraries that the support does not carry directly across, and
      we haven't yet had time to work on it.

Java not supported
      Because the Java support is related to the creation of shared 
      libraries, this is also not yet implemented for Windows. 

Command line editing limited
      Because of the limits of the Windows DOS console window, the 
      command line editing in siod is less reliable (for instance on 
      very long lines). 

(Visual C++) Networking not supported
      Networking under Win32 is different from Unix in a number of 
      fairly fundamental ways, we haven't tackled this at all. 

There are no doubt other differences we have not noticed. We don't use
Windows for any of our work and so the Windows builds of our systems
don't get the extensive use the unix builds do.

# BUILDING IT

## Configuration

### Meson instructions

Run `meson setup --help` to see all the options meson provides. See the
additional specific options for Edinburg Speech Tools defined in the
`meson_options.txt` file. Use:

    meson setup --prefix="/your/installation/directory" -Daudio_pulseaudio=false builddir

This will create the `builddir` directory with your desired configuration.

### Makefile instructions

All compile-time configuration for the system is done through GNU 
configure.  On most systems you can configure the system
by

          unix$ ./configure

This creates the file config/config which for most machines will be
suitable.  In some circumstances the default.s generated from this
may not be what you want and you may wish to edit this file.

For Linux we now fully support shared libraries and even recommend
them. However if you are going to do a lot of development and don't
understand the consequences of shared libraries and getting
LD_LIBRARY_PATH correct (or what that is) we recommend you compile
unshared, the default. If you are going to simply run the speech tools
(and festival) then shared is a reasonable option. Uncomment the line
in the config file

          # SHARED = 2

Shared support under Solaris is complete for all the speech tools. If
you need to exec festival scripts using a version of festival built
with shared libraries, you must either execute them from a featureful
shell (e.g. bash), install the shared libraries in a standard place or
explicitly set LD_LIBRARY_PATH. Solaris's standard shell doesn't
support script execution of shells within shells.

Simple choices for common set ups are given near the top of this
file. But for some sub-systems you will also need to change pathnames
for external library support.

## Compilation

### Meson instructions

From the previous step, you can start the compilation process with:

    meson compile -C builddir

Once the build finishes, you can run the test suite:

    meson test -C builddir

### Makefile instructions

Once you have configured config/config you can compile the system. 

          unix$ gmake

Note this must be GNU make, which may be called make on your system,
or gmake or gnumake. This will compile all library functions and all
the executables. If you wish to only compile the library itself then
use

          unix$ gmake make_library

Note that if you compile with -g (uncommenting DEBUG = 1 is
config/config the library and the corresponding binaries will be
large. Particularly the executables, you will need in order of 150
megabytes to compile the system, if your C++ libraries are not
compiled as shared libraries. If you compile without -g the whole
library directory is about 12 megabytes on Linux (which has shared
libraries for libstdc++ or about 26 megabytes of Sparc Solaris (which
does not have a shared library libstdc++ by default). This is almost
entirely due to the size of the executables. C++ does not make small
binaries.

In general we have made the system compile with no warnings. However
for some compilers this has proved to be near impossible. SunOS
include files have a number of system declarations missing, so many
system functions (e.g. fprintf) will appear to be undeclared. Sun's CC
compiler also likes to complain about missing source for some code
even though the code exists within our system and is deliberately in
separate files ro make it modular.

To test the system after compilation 

          unix$ gmake test

## Installing the system

### Meson instructions

Run:

    meson install -C builddir

If the installation directory specified in `prefix` is not standard
(`/usr`, `/usr/local`), you will have to add `$prefix/bin` to your path and
`$prefix/lib` (where the shared libraries are) into your ldconfig settings,
for instance setting `LD_LIBRARY_PATH` to the directory where the shared
libraries are.

In case you have trouble setting `LD_LIBRARY_PATH` you can use 
`--default-library=static` in the meson setup.


### Makefile instructions

All executables are linked to from speech_tools/bin and you should add
that to your PATH in order to use them.

Include files are speech_tools/include/ and the three generated
libraries are speech_tools/lib/libestools.a,
speech_tools/lib/libestbase.a and speech_tools/lib/libestring.a. For
most cases a three will be required.

If space is a premium, compiled with the shared option (binaries
will be then be substantially smaller) and you can delete all .o files

Some aspects of the system have further dependencies which depend of
the option selected at compile time. Specifically the readline
libraries and Netaudio libraries.

### Visual Studio instructions:

These are uptodate instructions for Visual C++ builds.
VS2010 was tested but older versions may work

Requirements:
MS Windows 7 (or Windows 8)
Visual C++ (VS2010 or VS2012)
cygwin 1.7 or later
speech_tools-2.3
festival-2.3

Download and install cygwin.
Optionally download emacs so you have a decent editor :)
Download speech_tools and festival tar.gz files.
Download required festival lexicons and voices.

Using cygwins bash shell:
  mkdir C:/festival
  cd C:/festival

Using cygwin's tar command unpack:
  tar xvfz speech_tools-2.3.tar.gz 
  tar xvfz festival-2.3.tar.gz
  tar xvfz festlex... festvox...
(where festlex... and festvox... are the voice and lexicon files you
need.  Do not use winzip to unpack the voices it corrupts them!)

Create Visual C++ make files: (this may be slow...)
  cd speech_tools
  make VCMakefile
  cp config/vc_config_make_rules-dist config/vc_config_make_rules

  cd ../festival
  make VCMakefile
  cp config/vc_config_make_rules-dist config/vc_config_make_rules

Finally make festival init_modules code. (If you add new modules you
either need to edit init_modules.cc by hand or rerun this step.)
  make -C src/modules init_modules.cc

edit config/vc_config_make_rules and change:
  SYSTEM_LIB=c:\\festival\\lib
to:
  SYSTEM_LIB=c:\\festival\\festival\\lib
(or to wherever you unpacked festival)

Now switch to a windows command prompt.
If necessary execute: VCVARSALL.BAT from the VC++ directory structure to set up
VC++ environment. (you may do this automatically at boot or login, or it should be 
automatic if using the terminal provided by Visual studio)

Build speech_tools and festival:
  cd c:\festival\speech_tools
  nmake /nologo /FVCMakefile

  cd ..\festival
  nmake /nologo /FVCMakefile

At this point you should be able to run festival by typing:
  src\main\festival



