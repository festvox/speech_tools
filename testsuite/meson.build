pymod = import('python')
python3 = pymod.find_installation()
testsuite_tests = ['string', 'hash', 'pathname', 'track', 'token', 'complex',
    'list', 'kvl', 'handle', 'named_enum', 'deq', 'ling', 'feature']
# disabled: sigpr

extra_args = {'hash_regression': [join_paths(meson.source_root(),'lib/example_data/alice')]}

speech_tools_paths = []
speech_tools_executables = [] # EXECUTABLES.values()
foreach exec_name,exec : EXECUTABLES
  speech_tools_paths += exec_name.to_upper() + '=' + exec.full_path()
  speech_tools_executables += exec
endforeach


foreach mode : ['example', 'regression']
  foreach test : testsuite_tests
    testname = test + '_' + mode
    exe = executable(
      testname,
      sources: testname + '.cc',
      link_with: [estools, estbase, eststring],
      include_directories: ['../include'],
      cpp_args: ['-DTVECTOR_BOUNDS_CHECKING',
                 '-DINSTANTIATE_TEMPLATES',
                 '-DDATA="' + join_paths(meson.source_root(),'lib/example_data') + '"']
    )
    if testname in extra_args
      args = extra_args[testname]
    else
      args = []
    endif
    test(testname, python3,
         args: [join_paths(meson.current_source_dir(), 'run_test.py'),
                testname,
                exe.full_path(),
                join_paths(meson.current_source_dir(), 'correct')
         ] + args,
         depends: exe
    )
  endforeach
endforeach


shell = find_program('sh', native: true)

testsuite_scripts = ['ch_wave', 'ch_track', 'viterbi', 'wagon', 'tilt', 'lpc']

foreach test_script : testsuite_scripts
  test(test_script + '.sh', shell,
       args: [join_paths(meson.current_source_dir(), test_script + '.sh')],
       depends: speech_tools_executables,
       env : [
           'DATA=' + join_paths(meson.source_root(),'lib/example_data/'),
           'OUTPUT=' + test_script + '_script.out',
           'OUTFILE=' +  test_script + '.tree' # only used in wagon.sh
        ] + speech_tools_paths
  )
endforeach

