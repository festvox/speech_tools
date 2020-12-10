
# These are headers and template headers that should not be compiled
# Most of them have .cc extensions, probably because when they were written
# templates were so new that it was confusing to have implementations in header files.
base_class_headers = files(
  'EST_matrix_support.h',
  'EST_TBuffer.cc',
  'EST_TDeque.cc',
  'EST_THash.cc',
  'EST_TKVL.cc',
  'EST_TList.cc',
  'EST_TMatrix.cc',
  'EST_TNamedEnum.cc',
  'EST_TSimpleMatrix.cc',
  'EST_TSimpleVector.cc',
  'EST_TSortable.cc',
  'EST_TTimeIndex.cc',
  'EST_Tvectlist.cc',
  'EST_TVector.cc'

)

# Since speech tools include/ headers expect these headers to be on ../base_class
# we set up the $includedir/speech_tools/ to have a base_class/ and an include/ directory
install_headers(
  base_class_headers,
  subdir : meson.project_name() / 'base_class'
)


# Files that need to instantiate templates:

base_class_tsrcs = files(
  'EST_Featured.cc',
  'EST_Features.cc'
)

base_class_t_lib = static_library(
  'base_class_t_lib',
  sources: base_class_tsrcs,
  cpp_args : ['-DINSTANTIATE_TEMPLATES'],
  include_directories : ['.', '../include/']
)

libestbase_conv_libs += base_class_t_lib


# Files that do not instantiate templates:
base_class_cpp = files(
  'EST_UList.cc',
  'EST_Option.cc',
  'EST_StringTrie.cc',
  'EST_Token.cc',
  'vec_mat_aux.cc',
  'THash_aux.cc',
  'EST_FMatrix.cc',
  'EST_Complex.cc',
  'EST_Val.cc',
  'EST_matrix_support.cc',
  'rateconv.cc',
  'EST_IMatrix.cc',
  'EST_SMatrix.cc',
  'EST_DMatrix.cc',
  'vec_mat_aux_d.cc',
  'EST_FeatureData.cc',
  'EST_slist_aux.cc',
  'EST_svec_aux.cc',
  'EST_ilist_aux.cc',
  'EST_features_aux.cc',
  'EST_features_io.cc',
  'vec_mat_aux_i.cc'
)

if host_machine.system() == 'windows'
  base_class_cpp += files('EST_Pathname_win32.cc')
else
  base_class_cpp += files('EST_Pathname_unix.cc')
endif


base_class_lib = static_library(
  'base_class_lib',
  sources: base_class_cpp,
  include_directories : ['.', '../include/']
)

libestbase_conv_libs += base_class_lib

subdir('inst_tmpl')
subdir('string')

