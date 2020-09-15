## Definitions for PulseAudio

INCLUDE_PULSE_AUDIO=1

MOD_DESC_PULSE_AUDIO=PulseAudio support

AUDIO_DEFINES += -DSUPPORT_PULSEAUDIO
AUDIO_INCLUDES += -I$(PULSE_INCLUDE)
MODULE_LIBS += -lpulse-simple -lpulse
PROJECT_LIBRARY_SYSLIBS_estbase += -lpulse-simple -lpulse

