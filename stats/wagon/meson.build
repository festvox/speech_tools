openmp = dependency('openmp', required: false) # meson builtin

stats_wagon_deps = []
stats_wagon_cpp_args = ['-DINSTANTIATE_TEMPLATES']

if openmp.found()
  stats_wagon_deps = [openmp]
  stats_wagon_cpp_args += '-DOMP_WAGON'
endif

stats_wagon_t_lib = static_library(
  'stats_wagon_t_lib',
  sources: files(
    'wagon.cc',
  ),
  include_directories : ['../../include/'],
  cpp_args: stats_wagon_cpp_args,
  dependencies: stats_wagon_deps
)

libestools_conv_libs += stats_wagon_t_lib

stats_wagon_lib = static_library(
  'stats_wagon_lib',
  sources: files(
    'dlist.cc',
    'wagon_aux.cc',
    'wagonint.cc'
  ),
  include_directories : ['../../include/']
)

libestools_conv_libs += stats_wagon_lib
