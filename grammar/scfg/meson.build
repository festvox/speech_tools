grammar_scfg_t_lib = static_library(
  'grammar_scfg_t_lib',
  sources: files(
    'EST_SCFG.cc',
    'EST_SCFG_inout.cc'
  ),
  cpp_args: ['-DINSTANTIATE_TEMPLATES'],
  include_directories : ['../../include/']
)

libestools_conv_libs += grammar_scfg_t_lib



grammar_scfg_lib = static_library(
  'grammar_scfg_lib',
  sources: files(
    'EST_SCFG_Chart.cc'
  ),
  include_directories : ['../../include/']
)

libestools_conv_libs += grammar_scfg_lib


