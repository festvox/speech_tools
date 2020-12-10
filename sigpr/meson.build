sigpr_t_lib = static_library(
  'sigpr_t_lib',
  sources: files(
    'EST_Window.cc'
  ),
  include_directories : ['../include/'],
  cpp_args: ['-DINSTANTIATE_TEMPLATES']
)
libestbase_conv_libs += sigpr_t_lib


sigpr_lib = static_library(
  'sigpr_lib',
  sources: files(
    'delta.cc',
    'filter.cc',
    'sigpr_frame.cc',
    'sigpr_utt.cc',
    'pitchmark.cc',
    'spectrogram.cc',
    'misc.cc',
    'fft.cc'
  ),
  include_directories : ['../include/']
)
libestbase_conv_libs += sigpr_lib

subdir('pda')
