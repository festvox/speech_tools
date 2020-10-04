ling_class_t_lib = static_library(
  'ling_class_t_lib',
  sources: files(
    'apml.cc',
    'EST_FeatureFunctionContext.cc',
    'EST_FeatureFunctionPackage.cc',
    'EST_utterance_aux.cc',
    'EST_Utterance.cc',
    'EST_UtteranceFile.cc',
    'genxml.cc',
    'item_feats.cc',
    'ling_class_init.cc',
    'ling_t.cc',
    'solexml.cc'
  ),
  include_directories : ['.', '../include/'],
  cpp_args : ['-DINCLUDE_XML_FORMATS', '-DINSTANTIATE_TEMPLATES']
)
libestbase_conv_libs += ling_class_t_lib



ling_class_lib = static_library(
  'ling_class_lib',
  sources: files(
    'EST_item_aux.cc',
    'EST_Item.cc',
    'EST_item_content_aux.cc',
    'EST_Item_Content.cc',
    'EST_relation_aux.cc',
    'EST_Relation.cc',
    'EST_relation_compare.cc',
    'EST_Relation_mls.cc',
    'EST_relation_track.cc',
    'item_aux.cc',
    'relation_io.cc',
    'standard_feature_functions.cc',
  ),
  include_directories : ['.', '../include/'],
  cpp_args : ['-DINCLUDE_XML_FORMATS']
)
libestbase_conv_libs += ling_class_lib

