grammar_wfst_t_lib = static_library(
  'grammar_wfst_t_lib',
  sources: files(
    'EST_WFST.cc',
   'wfst_regex.cc',
    'wfst_ops.cc',
    'wfst_transduce.cc',
    'kkcompile.cc',
  ),
  cpp_args: ['-DINSTANTIATE_TEMPLATES'],
  include_directories : ['.', '../../include/']
)

libestools_conv_libs += grammar_wfst_t_lib

grammar_wfst_lib = static_library(
  'grammar_wfst_lib',
  sources: files(
    'wfst_aux.cc',
    'ltscompile.cc',
    'rgcompile.cc',
    'tlcompile.cc',
    'wfst_train.cc'
  ),
  include_directories : ['.', '../../include/']
)

libestools_conv_libs += grammar_wfst_lib


