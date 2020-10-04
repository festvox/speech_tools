grammar_ngram_t_lib = static_library(
  'grammar_ngram_t_lib',
  sources: files(
    'lattice_t.cc'
  ),
  cpp_args: ['-DINSTANTIATE_TEMPLATES'],
  include_directories : ['../../include/']
)

libestools_conv_libs += grammar_ngram_t_lib

grammar_ngram_lib = static_library(
  'grammar_ngram_lib',
  sources: files(
    'EST_Ngrammar.cc',
    'ngrammar_io.cc',
    'ngrammar_aux.cc',
    'ngrammar_utils.cc',
    'EST_lattice.cc',
    'EST_lattice_io.cc',
    'freqsmooth.cc',
    'EST_PST.cc'
  ),
  include_directories : ['../../include/']
)

libestools_conv_libs += grammar_ngram_lib


