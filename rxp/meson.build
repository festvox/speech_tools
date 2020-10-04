rxp_t_lib = static_library(
  'rxp_t_lib',
  sources: files(
    'XML_Parser.cc'
  ),
  include_directories : ['../include/rxp', '../include/'],
  cpp_args : ['-DCHAR_SIZE=8', '-DINSTANTIATE_TEMPLATES']
)
libestbase_conv_libs += rxp_t_lib



rxp_lib = static_library(
  'rxp_lib',
  sources: files(
    'charset.c',
    'dtd.c',
    'string16.c',
    'url.c',
    'ctype16.c',
    'input.c',
    'stdio16.c',
    'system.c',
    'xmlparser.c'
  ),
  include_directories : ['../include/rxp', '../include/'],
  c_args : ['-DCHAR_SIZE=8'],
)
libestbase_conv_libs += rxp_lib


