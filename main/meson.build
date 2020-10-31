executables = [
  'align', # not installed in debian
  'bcat',
  'ch_lab',
  'ch_track',
  'ch_utt',
  'ch_wave',
  'design_filter', # not installed in debian
  'dp',
  'na_play',
  'na_record',
  'ngram_build',
  'ngram_test',
  'pda',
  'pitchmark',
  'sig2fv',
  'sigfilter',
  'spectgen',
  'tilt_analysis',
  'tilt_synthesis',
  'viterbi',
]

if get_option('scfg')
  executables += [
    'scfg_make',
    'scfg_train',
    'scfg_test',
    'scfg_parse',
  ]
endif

if get_option('wfst')
  executables += [
    'wfst_build',
    'wfst_run',
    'wfst_train' # not installed in debian
  ]
endif

if get_option('ols')
  executables += [
    'ols',
    'ols_test'
  ]
endif

#if get_option('kalman_filter')
#  executables += [
#  'fit_linear_model',
#  'match_linear_models',
#  ]
#endif

if get_option('wagon')
  executables += [
  'wagon',
  'wagon_test',
  ]
endif

if get_option('rxp')
  executables += 'xml_parser' # not installed in debian
endif

if get_option('siod')
  executables += 'siod' # not installed in debian
endif

openmp = dependency('openmp', required: false)
if openmp.found()
  main_wagon_deps = [openmp]
  main_wagon_cpp_args = '-DOMP_WAGON'
else
  main_wagon_deps = []
  main_wagon_cpp_args = []

endif

main_na_record_deps = []
main_na_record_cpp_args = []

# winmm audio
if (host_machine.system() == 'windows' or host_machine.system() == 'cygwin')
  # Here I could try to possibly use find_library()...
  winmm_dep = cxx.find_library('winmm')
  main_na_record_deps += winmm_dep
endif

if host_machine.system() == 'windows'
  winsock2_dep = cxx.find_library('wsock32')
  main_na_record_deps += winsock2_dep
endif


EXECUTABLES = {}
foreach prog : executables
  if prog == 'wagon'
    main_exec_deps = main_wagon_deps
    main_exec_cpp_args = main_wagon_cpp_args
  elif prog == 'na_record'
    main_exec_deps = main_na_record_deps
    main_exec_cpp_args = main_na_record_cpp_args
  else
    main_exec_deps = []
    main_exec_cpp_args = []
  endif
  exe = executable(
    prog,
    sources: prog + '_main.cc',
    include_directories: ['../include'],
    cpp_args: main_exec_cpp_args,
    dependencies: main_exec_deps,
    link_with: [estools, estbase, eststring],
    install: true
  )
  EXECUTABLES += {prog: exe}
endforeach



