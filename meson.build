project('speech-tools', ['cpp', 'c'], version : '2.5.1',
        default_options : ['c_std=c99', 'cpp_std=c++11'], meson_version: '>=0.55.0')

PROJECT_NAME = 'Edinburgh Speech Tools Library'
PROJECT_DATE = 'July 2020'
PROJECT_VERSION = meson.project_version()
PROJECT_STATE = 'current'
SYSTEM_TYPE = host_machine.cpu_family() + '_' + host_machine.system()
ESTLIB_SUBDIR = join_paths(get_option('datadir'), meson.project_name())
ESTLIBDIRC = join_paths(get_option('prefix'), ESTLIB_SUBDIR)
SIOD_SUBDIR = join_paths(ESTLIB_SUBDIR, 'siod')
DOCDIR = join_paths(get_option('prefix'), get_option('datadir'), 'doc', meson.project_name())

# From bindir find the relative path to ESTLIB_SUBDIR
# This needs from a relative_to computation, not available on meson right now
# See: https://github.com/mesonbuild/meson/pull/7908
ESTRELLIBDIR = join_paths('..', ESTLIB_SUBDIR)

cc = meson.get_compiler('c')
cxx = meson.get_compiler('cpp')

if cxx.has_argument('-fno-implicit-templates')
  add_project_arguments('-fno-implicit-templates', language : 'cpp')
endif

# https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
if cxx.get_id() == 'msvc' and cxx.has_argument('/Zc:__cplusplus')
  add_project_arguments('/Zc:__cplusplus', language : 'cpp')
endif


v_array = meson.project_version().split('.')
v_major = v_array[0]
v_minor = v_array[1]
v_patch = v_array[2]

pkg_config_h_subdirs = []
libestbase_conv_libs = []
libestools_conv_libs = []
libestring_conv_libs = []

doc_sources = []

feature_dependencies = {
  'scfg': ['siod'],
  'ols': ['siod'],
  'wagon': ['siod'],
  'wfst': ['siod']
}

foreach feature, deplist : feature_dependencies
  missing_dep = []
  if get_option(feature)
    foreach dep : deplist
      if not get_option(dep)
        missing_dep += dep
      endif
    endforeach
    if missing_dep.length() > 0
      error('Feature ' + feature + ' depends on ' + ', '.join(missing_dep) + '. Please enable it')
    endif
  endif
endforeach


subdir('audio')
subdir('base_class')
subdir('grammar')
subdir('include')
subdir('intonation')
subdir('ling_class')
if get_option('rxp')
  subdir('rxp')
endif
subdir('sigpr')
if get_option('siod')
  subdir('siod')
endif
subdir('speech_class')
subdir('stats')
subdir('utils')

eststring = library('eststring',
  soversion : v_major + '.' +  v_minor,
  link_whole: libestring_conv_libs,
  install: true
)

estbase = library('estbase',
  soversion : v_major + '.' +  v_minor,
  link_whole : libestbase_conv_libs,
  link_with: eststring,
  install: true
)

estools = library('estools',
  soversion : v_major + '.' +  v_minor,
  link_whole : libestools_conv_libs,
  link_with: [estbase, eststring],
  install: true
)

subdir('main')
subdir('scripts')
subdir('testsuite')
subdir('lib')

subdir('doc')

pkg = import('pkgconfig')

pkg.generate(
  eststring,
  name: 'eststring',
  description: 'Edinburgh Speech Tools Library (eststring)',
  subdirs: pkg_config_h_subdirs,
  version: meson.project_version(),
  variables:
  [
    'pkgdatadir=${prefix}/' + ESTLIB_SUBDIR,
    'sioddir=${prefix}/' + SIOD_SUBDIR
  ],
  filebase : 'eststring'
)

pkg.generate(
  estbase,
  name: 'estbase',
  description: 'Edinburgh Speech Tools Library (estbase)',
  requires: eststring,
  subdirs: pkg_config_h_subdirs,
  version: meson.project_version(),
  variables:
  [
    'pkgdatadir=${prefix}/' + ESTLIB_SUBDIR,
    'sioddir=${prefix}/' + SIOD_SUBDIR
  ],
  filebase : 'estbase'
)

pkg.generate(
  estools,
  name: 'estools',
  description: 'Edinburgh Speech Tools Library (estools)',
  requires: [estbase, eststring],
  subdirs: pkg_config_h_subdirs,
  version: meson.project_version(),
  variables:
  [
    'pkgdatadir=${prefix}/' + ESTLIB_SUBDIR,
    'sioddir=${prefix}/' + SIOD_SUBDIR
  ],
  filebase : 'estools'
)

pkg.generate(
  name: meson.project_name(),
  description: 'Edinburgh Speech Tools Library',
  requires: [estools, estbase, eststring],
  subdirs: pkg_config_h_subdirs,
  version: meson.project_version(),
  variables:
  [
    'pkgdatadir=${prefix}/' + ESTLIB_SUBDIR,
    'sioddir=${prefix}/' + SIOD_SUBDIR
  ],
  filebase : meson.project_name()
)

