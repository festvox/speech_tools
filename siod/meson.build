siod_lib_deps = []
siod_lib_cargs = []

if not get_option('editline').disabled()
  ncurses = dependency('ncurses', required: false)
  if ncurses.found()
    siod_lib_cargs += '-DSUPPORT_EDITLINE'
    siod_lib_deps += ncurses
  else
    curses = dependency('curses', required: false)
    if curses.found()
      siod_lib_cargs += '-DSUPPORT_EDITLINE'
      siod_lib_deps += curses
    else
      termcaplib = dependency('termcaplib', required: false)
      if termcaplib.found()
        siod_lib_cargs += '-DSUPPORT_EDITLINE'
        siod_lib_deps += termcaplib
      else
        if get_option('editline').enabled()
          error('editline enabled, but no ncurses, curses or termcaplib found')
        else
          message('editline disabled because neither of ncurses, curses or termcaplib were found')
        endif
      endif
    endif
  endif
endif

if host_machine.system() == 'windows'
  winsock2_dep = cxx.find_library('wsock32')
  siod_lib_deps += winsock2_dep
endif



siod_t_lib = static_library(
  'siod_t_lib',
  sources: files(
    'siod.cc',
    'siod_est.cc',
  ),
  include_directories : ['.', '../include/'],
  cpp_args: ['-DINSTANTIATE_TEMPLATES']
)
libestools_conv_libs += siod_t_lib

if '-DSUPPORT_EDITLINE' in siod_lib_cargs
  siod_el_lib = static_library(
    'siod_el_lib',
    sources: files(
      'el_complete.c',
      'editline.c',
      'el_sys_unix.c',
    ),
    dependencies: siod_lib_deps,
    include_directories : ['.', '../include/'],
    c_args: siod_lib_cargs
  )
  libestools_conv_libs += siod_el_lib
endif

if not get_option('siod_python').disabled()
  python3_dep = dependency('python3', required: get_option('siod_python'))
  if python3_dep.found()
    siod_lib_cargs += '-DEST_SIOD_ENABLE_PYTHON'
    siod_lib_deps += python3_dep
  endif
endif

siod_lib = static_library(
  'siod_lib',
  sources: files(
    'siodeditline.c',
    'siodeditline.c',
    'slib.cc',
    'slib_core.cc',
    'slib_doc.cc',
    'slib_file.cc',
    'slib_format.cc',
    'slib_list.cc',
    'slib_math.cc',
    'slib_sys.cc',
    'slib_server.cc',
    'slib_str.cc',
    'slib_xtr.cc',
    'slib_repl.cc',
    'slib_python.cc',
    'slib_io.cc',
    'trace.cc'
  ),
  dependencies: siod_lib_deps,
  include_directories : ['.', '../include/'],
  c_args: siod_lib_cargs
)

libestools_conv_libs += siod_lib

