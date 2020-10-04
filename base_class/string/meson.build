base_class_string_lib = static_library(
  'base_class_string_lib',
  sources: files(
  'regerror.c',
  'regsub.c',
  'EST_strcasecmp.c',
  'EST_String.cc',
  'EST_Regex.cc',
  'EST_Chunk.cc',
  'regexp.cc'
  ),
  include_directories : ['.', '..', '../../include/']
)


libestring_conv_libs += base_class_string_lib

