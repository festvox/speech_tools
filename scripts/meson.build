
sed = find_program('sed', native: true)
perl = find_program('perl')

foreach script : ['resynth', 'make_wagon_desc']
  configure_file(
    input : script + '.sh',
    output : script,
    copy: true,
    install : true,
    install_mode: 'rwxr-xr-x',
    install_dir : 'bin'
  )
endforeach

foreach script : ['pm', 'raw_to_xgraph']
  cus_target = custom_target(script,
    input: script + '.prl',
    output: script,
    command : [sed, '-e', 's@__PERL__@' + perl.full_path() + '@g', '@INPUT@'],
    capture: true,
    install : true,
    install_mode: 'rwxr-xr-x',
    install_dir : 'bin'
  )
endforeach

