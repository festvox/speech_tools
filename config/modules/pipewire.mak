## Definitions for PipeWire

INCLUDE_PipeWire=1

MOD_DESC_PIPEWIRE=PipeWire support

AUDIO_DEFINES += -DSUPPORT_PIPEWIRE
AUDIO_INCLUDES += -I$(PIPEWIRE_INCLUDE)
MODULE_LIBS += -lpipewire-0.3 -lpipewire
PROJECT_LIBRARY_SYSLIBS_estbase += -lpipewire-0.3 -lpipewire


