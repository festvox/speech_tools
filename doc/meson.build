doxy_repl = {
  'VERSION': meson.project_version(),
  'TOP_SRCDIR': meson.source_root(),
  'TOP_BUILDDIR': meson.build_root()
}

# The DoxyFile that exists in the current directory is used by Makefile
# The DoxyFile.in file is used by meson.
doxyfile = configure_file(
  input: files('DoxyFile.in'),
  output: 'DoxyFile',
  configuration: doxy_repl,
  install: false
)

doc_man_progs = []
subdir('man')
doxygen = find_program('doxygen', native: true, required: false)

doc_sources += 'bibliography.bib'

if doxygen.found() and not meson.is_cross_build()
  docs = custom_target(
    'docs',
    command: [doxygen.full_path(), doxyfile],
    depends: doc_man_progs,
    depend_files: doc_sources,
    install: true,
    install_dir: join_paths(get_option('datadir'), 'doc', 'speech-tools'),
    output: ['html']
  )
endif
