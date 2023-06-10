audio_lib_cpp_args = []
audio_lib_deps = []

# nas

if not get_option('audio_nas').disabled()
  # nas does not provide a pkg-config file, so we do the detection manually:
  audio_nas_dep = dependency('audio', required: false)
  if not audio_nas_dep.found()
    audio_nas_dep = cxx.find_library('audio', has_headers: 'audio/audiolib.h', required: false)
    if audio_nas_dep.found()
      audio_lib_cpp_args += '-DSUPPORT_NAS'
      audio_lib_deps += audio_nas_dep
    else
      assert(not get_option('audio_nas').enabled(), 'NAS enabled but dependency not found')
    endif
  endif
endif

# esd
# esd has been removed from debian stable. Are there esd users out there?
audio_esd_dep = dependency('esound', required: get_option('audio_esd'))
if audio_esd_dep.found()
  audio_lib_cpp_args += '-DSUPPORT_ESD'
  audio_lib_deps += audio_esd_dep
endif

# sun16audio
if host_machine.system() == 'sunos' #  illumos and Solaris
  audio_lib_cpp_args += '-DSUPPORT_SUN16'
endif

# mplayer (disabled by default, not a robust solution)
if not get_option('audio_mplayer').disabled()
  audio_lib_cpp_args += '-DSUPPORT_MPLAYER'
endif


# winmm audio
if not get_option('audio_win32').disabled() and (host_machine.system() == 'windows' or host_machine.system() == 'cygwin')
  audio_lib_cpp_args += '-DSUPPORT_WIN32AUDIO'
  # Here I could try to possibly use find_library()...
  winmm_dep = cxx.find_library('winmm')
  audio_lib_deps += winmm_dep
endif

if host_machine.system() == 'windows'
  winsock2_dep = cxx.find_library('wsock32')
  audio_lib_deps += winsock2_dep
endif


# irix audio
if not get_option('audio_irix').disabled() and host_machine.system().startswith('irix')
  irix_dep = cxx.find_library('audio', has_headers: 'audio.h', required: audio_irix)
  if irix_dep.found()
    audio_lib_cpp_args += '-DSUPPORT_IRIX'
    audio_lib_deps += irix_dep
    # usleep not available on irix 5.3:
    if not cxx.has_function('usleep', prefix : '#include <unistd.h>')
      audio_lib_cpp_args += '-DSUPPORT_IRIX53'
    endif
  endif
endif

# os2audio
if not get_option('audio_os2').disabled()
  error('the meson build system for speech-tools does not support the os/2 operating system')
  # You will need -los2me, according to os2_audio.cc
endif

#macosxaudio
if not get_option('audio_osx').disabled() and host_machine.system() == 'darwin'
  audio_lib_cpp_args += '-DSUPPORT_MACOSX_AUDIO'
  # Here I could try to possibly use find_library()...
  osx_dep = declare_dependency(link_args: ['-framework', 'CoreAudio', '-framework', 'AudioUnit',
     '-framework', 'AudioToolbox', '-framework', 'Cocoa'])
  audio_lib_deps += osx_dep
endif

#pulseaudio
audio_pulse_dep = dependency('libpulse-simple', required: get_option('audio_pulseaudio'))
if audio_pulse_dep.found()
  audio_lib_cpp_args += '-DSUPPORT_PULSEAUDIO'
  audio_lib_deps += audio_pulse_dep
endif


#linuxsound
## alsa
audio_alsa_dep = dependency('alsa', required: get_option('audio_alsa'))
if audio_alsa_dep.found()
  audio_lib_cpp_args += '-DSUPPORT_ALSALINUX'
  audio_lib_deps += audio_alsa_dep
endif

#pipewire
audio_pipewire_dep = dependency('libpipewire-0.3', version: '>= 0.3.52', required: get_option('audio_pipewire'))
if audio_pipewire_dep.found()
  audio_lib_cpp_args += '-DSUPPORT_PIPEWIRE'
  audio_lib_deps += audio_pipewire_dep
endif

## voxware
if host_machine.system() == 'freebsd' or host_machine.system() == 'netbsd' or host_machine.system() == 'openbsd'
  audio_lib_cpp_args += '-DSUPPORT_FREEBSD16'
endif

if host_machine.system() == 'linux' and not audio_alsa_dep.found()
  audio_lib_cpp_args += '-DSUPPORT_VOXWARE'
endif

# The linux_sound.cc define logic could be cleaned up (e.g. unused SUPPORT_LINUX16)


audio_lib = static_library(
  'audio_lib',
  sources: files(
    'gen_audio.cc',
    'nas.cc',
    'esd.cc',
    'sun16audio.cc',
    'mplayer.cc',
    'win32audio.cc',
    'irixaudio.cc',
    'os2audio.cc',
    'macosxaudio.cc',
    'pulseaudio.cc',
    'linux_sound.cc'
  ),
  include_directories : ['.', '../include/'],
  install: false,
  cpp_args: audio_lib_cpp_args,
  dependencies: audio_lib_deps
)

libestbase_conv_libs += audio_lib

