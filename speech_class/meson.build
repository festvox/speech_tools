speech_class_t_lib = static_library(
  'speech_class_t_lib',
  sources: files(
    'EST_TrackMap.cc',
    'EST_Track.cc',
    'wave_t.cc',
    'track_t.cc',
    'EST_wave_aux.cc',
    'EST_TrackFile.cc',
    'EST_WaveFile.cc',
  ),
  cpp_args: ['-DINSTANTIATE_TEMPLATES'],
  include_directories : ['.', '../include/']
)
libestbase_conv_libs += speech_class_t_lib


speech_class_lib = static_library(
  'speech_class_lib',
  sources: files(
    'EST_Wave.cc',
    'EST_track_aux.cc',
    'EST_wave_temp.cc',
    'EST_wave_cuts.cc',
    'ssff.cc',
    'esps_io.cc',
    'esps_utils.cc',
    'EST_wave_io.cc',
    'EST_wave_utils.cc'
  ),
  include_directories : ['.', '../include/']
)
libestbase_conv_libs += speech_class_lib

