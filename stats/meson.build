
stats_t_lib = static_library(
  'stats_t_lib',
  sources: files(
    'dynamic_program.cc'
  ),
  include_directories : ['../include/'],
  cpp_args: ['-DINSTANTIATE_TEMPLATES']
)

libestbase_conv_libs += stats_t_lib


stats_lib = static_library(
  'stats_lib',
  sources: files(
    'EST_cluster.cc',
    'EST_multistats.cc',
    'confusion.cc',
    'EST_Discrete.cc',
    'EST_DProbDist.cc',
    'EST_ols.cc',
    'EST_viterbi.cc'
  ),
  include_directories : ['../include/']
)

libestbase_conv_libs += stats_lib

if get_option('kalman_filter')
  subdir('kalman_filter')
endif
if get_option('wagon')
  subdir('wagon')
endif


