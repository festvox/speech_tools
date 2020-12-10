utils_lib_t = static_library(
  'utils_lib_t',
  sources: files('est_file.cc'),
  cpp_args : ['-DINSTANTIATE_TEMPLATES'],
  include_directories : ['.', '../include/']
)
libestbase_conv_libs += utils_lib_t

utils_lib = static_library(
  'utils_lib',
  sources: files(
    'cmd_line_aux.cc',
    'cmd_line.cc',
    'EST_cutils.c',
    'EST_error.c',
    'EST_swapping.cc',
    'filetrans.cc',
    'system_specific_unix.c',
#    'system_specific_win32.c',
    'util_io.cc'
  ),
  c_args : [
    '-DESTNAME=' + PROJECT_NAME,
    '-DESTDATE=' + PROJECT_DATE,
    '-DESTVERSION=' + PROJECT_VERSION,
    '-DESTLIBDIRC=' + ESTLIBDIRC,
    '-DESTSTATE=' + PROJECT_STATE,
    '-DESTOSTYPE=' + SYSTEM_TYPE
  ],
  include_directories : ['.', '../include/']
)
libestbase_conv_libs += utils_lib

utils_string_lib = static_library(
  'utils_string_lib',
  sources: files(
    'walloc.c'
  ),
  include_directories : ['.', '../include/'],
)

libestring_conv_libs += utils_string_lib



