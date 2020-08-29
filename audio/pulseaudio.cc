/*************************************************************************/
/*                                                                       */
/*                Centre for Speech Technology Research                  */
/*                     University of Edinburgh, UK                       */
/*                      Copyright (c) 1997,1998                          */
/*                            Red Hat, Inc.                              */
/*                         Copyright (c) 2008                            */
/*                        All Rights Reserved.                           */
/*                                                                       */
/*  Permission is hereby granted, free of charge, to use and distribute  */
/*  this software and its documentation without restriction, including   */
/*  without limitation the rights to use, copy, modify, merge, publish,  */
/*  distribute, sublicense, and/or sell copies of this work, and to      */
/*  permit persons to whom this work is furnished to do so, subject to   */
/*  the following conditions:                                            */
/*   1. The code must retain the above copyright notice, this list of    */
/*      conditions and the following disclaimer.                         */
/*   2. Any modifications must be clearly marked as such.                */
/*   3. Original authors' names are not deleted.                         */
/*   4. The authors' names are not used to endorse or promote products   */
/*      derived from this software without specific prior written        */
/*      permission.                                                      */
/*                                                                       */
/*  THE UNIVERSITY OF EDINBURGH AND THE CONTRIBUTORS TO THIS WORK        */
/*  DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING      */
/*  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT   */
/*  SHALL THE UNIVERSITY OF EDINBURGH NOR THE CONTRIBUTORS BE LIABLE     */
/*  FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES    */
/*  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN   */
/*  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,          */
/*  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF       */
/*  THIS SOFTWARE.                                                       */
/*                                                                       */
/*************************************************************************/
/*  Optional support for PulseAudio                                      */
/*=======================================================================*/

#include "EST_Wave.h"
#include "EST_Option.h"
#include "audioP.h"

using namespace std;

#ifdef SUPPORT_PULSEAUDIO

#include <pulse/simple.h>
int pulse_supported = TRUE;

#define AUDIOBUFFSIZE 256
// #define AUDIOBUFFSIZE 20480

int play_pulse_wave(EST_Wave &inwave, EST_Option &al)
{
    pa_sample_spec *ss;
    pa_simple *s;
    short *waveform;
    int num_samples;
    int err=0, i;

    ss = walloc(pa_sample_spec,1);
    ss->rate = inwave.sample_rate();
    ss->channels = inwave.num_channels();

    ss->format = PA_SAMPLE_S16NE;
    
    s = pa_simple_new(
                    NULL,      /* use default server */
                    "festival",
                    PA_STREAM_PLAYBACK,
                    NULL,      /* use default device */
                    "Speech",
                    ss,
                    NULL,      /* default channel map */
                    NULL,      /* default buffering attributes */
                    &err);
    if (err < 0)
        return 0;

    waveform = inwave.values().memory();
    num_samples = inwave.num_samples();

    for (i=0; i < num_samples; i += AUDIOBUFFSIZE/2)
    {
        if (i + AUDIOBUFFSIZE/2 < num_samples)
            pa_simple_write(s,&waveform[i],(size_t)AUDIOBUFFSIZE,&err);
        else
            pa_simple_write(s,&waveform[i],(size_t)(num_samples-i)*2,&err);
    }

    pa_simple_drain(s,&err);
    pa_simple_free(s);
    wfree(ss);

    return 1;
}

int record_pulse_wave(EST_Wave &inwave, EST_Option &al)
{
    return -1;
}

#else /* SUPPORT_PULSEAUDIO */

int pulse_supported = FALSE;

int play_pulse_wave(EST_Wave &inwave, EST_Option &al)
{
    (void)inwave;
    (void)al;
    cerr << "Audio: pulseaudio not compiled in this version" << endl;
    return -1;
}

int record_pulse_wave(EST_Wave &inwave, EST_Option &al)
{
    (void)inwave;
    (void)al;
    cerr << "Audio: pulseaudio not compiled in this version" << endl;
    return -1;
}


#endif /* SUPPORT_PULSEAUDIO */
