# All the speech tools binaries use the parse_command_line() function, that expects
# a definition of the command line options and a synopsis of the usage.
# The Speech Tools library is able to parse those descriptions and provide them in a
# standard sgml format, when called with -sgml_synopsis or -sgml_options
# (e.g. ch_wave -sgml_options)
#
# Here we use an xslt template to convert the sgml output from those binaries into
# documentation usable by doxygen.
# 

foreach doc_required_opt : ['scfg', 'wfst', 'ols', 'wagon', 'rxp', 'siod']
  if not get_option(doc_required_opt)
    warning('The documentation can not be fully built without enabling' + doc_required_opt)
  endif
endforeach

xsltproc = find_program('xsltproc', native: true, required: false)
awk = find_program('awk', native: true, required: false)
sh = find_program('sh', native: true, required: false)

xslt_dep_files = files('convert-synopsis.xslt', 'convert-options.xslt', 'create_dox.sh')


# /tmp/speech_tools/doc/man/create_dox.sh \
#    /path/to/ch_wave \
#    /path/to/ch_wave_man.dox.body \
#    /tmp/speech_tools/doc/man/ \
#    /tmp/builddir/ \
#    /usr/bin/xsltproc \
#    /usr/bin/awk

if xsltproc.found() and awk.found() and sh.found() and not meson.is_cross_build()

foreach exe_name, exe_meson_object : EXECUTABLES
  doc_man_progs += custom_target(
    exe_name + '.dox',
    depend_files: [xslt_dep_files, files(exe_name + '_man.dox.body')],
    depends: exe_meson_object,
    command: [
    meson.current_source_dir() + '/create_dox.sh',
      exe_meson_object.full_path(),
      join_paths(meson.current_source_dir(), exe_name + '_man.dox.body'),
      meson.current_source_dir(),
      meson.current_build_dir(),
      xsltproc.full_path(),
      awk.full_path()
    ],
    output: [exe_name + '.dox']
  )
endforeach

endif # xsltproc.found() and awk.found() and sh.found()

