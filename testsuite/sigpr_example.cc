/************************************************************************/
/*                                                                      */
/*                Centre for Speech Technology Research                 */
/*                     University of Edinburgh, UK                      */
/*                       Copyright (c) 1996,1997                        */
/*                        All Rights Reserved.                          */
/*                                                                      */
/*  Permission is hereby granted, free of charge, to use and distribute */
/*  this software and its documentation without restriction, including  */
/*  without limitation the rights to use, copy, modify, merge, publish, */
/*  distribute, sublicense, and/or sell copies of this work, and to     */
/*  permit persons to whom this work is furnished to do so, subject to  */
/*  the following conditions:                                           */
/*   1. The code must retain the above copyright notice, this list of   */
/*      conditions and the following disclaimer.                        */
/*   2. Any modifications must be clearly marked as such.               */
/*   3. Original authors' names are not deleted.                        */
/*   4. The authors' names are not used to endorse or promote products  */
/*      derived from this software without specific prior written       */
/*      permission.                                                     */
/*                                                                      */
/*  THE UNIVERSITY OF EDINBURGH AND THE CONTRIBUTORS TO THIS WORK       */
/*  DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING     */
/*  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT  */
/*  SHALL THE UNIVERSITY OF EDINBURGH NOR THE CONTRIBUTORS BE LIABLE    */
/*  FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES   */
/*  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN  */
/*  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,         */
/*  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF      */
/*  THIS SOFTWARE.                                                      */
/*                                                                      */
/************************************************************************/
/*                                                                      */
/*                 Author: Paul Taylor (pault@cstr.ed.ac.uk)            */
/*                   Date: Fri May  9 1997                              */
/* -------------------------------------------------------------------  */
/* Examples of Generation of Acoustic Feature Vectors from Waveforms    */
/*                                                                      */
/************************************************************************/

#include <cstdlib>
#include "EST_sigpr.h"
#include "EST_cmd_line.h"
#include "EST_inline_utils.h"
#include "EST_sigpr.h"

using namespace std;

/**@name Signal processing example code
  * 
  * @toc
  */
///@{

EST_StrList empty;

void print_map(EST_TrackMap &t);
void print_track_map(EST_Track &t);

int main(void)

{
    EST_StrList base_list; // decl
    EST_StrList delta_list; // decl
    EST_StrList acc_list; // decl
    EST_Option op, al; // decl
    init_lib_ops(al, op); 
    EST_Wave sig; // decl
    EST_Track fv, part; // decl
    float shift; // decl
    int i;


    cout << "position 1\n";

    /* Producing a single type of feature vector for an utterance */
    
    ///@ code
    
    int lpc_order = 16;
    sig.load(DATA "/kdt_001.wav");

    ///@ endcode

    /* Now allocate enough space in the track to hold the analysis. */
    ///@ code
    int num_frames;
    num_frames = (int)ceil(sig.end() / 0.01);
    fv.resize(num_frames, lpc_order + 1);
    ///@ endcode

    /* The positions of the frames, corresponding to the middle of their
	analysis window also needs to be set. For fixed frame analysis, this
	can be done with the fill_time() function: */

    ///@ code
    fv.fill_time(0.01);
    ///@ endcode

    /* The simplest way to do the actual analysis is as follows, which
	will fill the track with the values from the LP analysis using the
	default processing controls.
    */

    ///@ code
    sig2coef(sig, fv, "lpc");
    ///@ endcode

    /* In this style of analysis, default values are used to control the
	windowing mechanisms which split the whole signal into frames.
    
	Extending one time period before and one time period after the
	current time mark:
    */
    ///@ code
    sig2coef(sig, fv, "lpc", 2.0);
    ///@ endcode

    /* Extending 1.5 time periods before and  after the
    current time mark, etc;
    */
    ///@ code
    sig2coef(sig, fv, "lpc", 3.0);
    ///@ endcode

    /* The type of windowing function may be changed also as this
	can be passed in as an optional argument. First we 
	create a window function (This is explained more in \ref Windowing ).
    */
    ///@ code
    EST_WindowFunc *wf =  EST_Window::creator("hamming");
    ///@ endcode
    /* and then pass it in as the last argument
     */
    ///@ code
    sig2coef(sig, fv, "lpc", 3.0, wf);
    ///@ endcode
    ///@}

    /* Pitch-Synchronous vs fixed frame analysis.

      There are many ways to fill the time array for fixed frame analysis.

      manually:      

      */
    ///@{

    ///@ code
    num_frames = 300;
    fv.resize(num_frames, lpc_order + 1);
    shift = 0.01; // time interval in seconds

    for (i = 0; i < num_frames; ++i)
	fv.t(i) = shift * (float) i;
    ///@ endcode
    /* or by use of the  member function EST_Track::fill_time}
     */

    ///@ code
    fv.fill_time(0.01);
    ///@ endcode

    /* Pitch synchronous values can simply be read from pitchmark
     files:
    */
    ///@ code
    fv.load(DATA "/kdt_001.pm");
    make_track(fv, "lpc", lpc_order + 1);
    ///@ endcode

    /* Regardless of how the time points where obtain, the analysis
     function call is just the same:
    */
    ///@ code
    sig2coef(sig, fv, "lpc");
    ///@ endcode
    ///@}

    cout << "position 3\n";

    /* Naming Channels */
    ///@{
    ///@ code

    int cep_order = 16;
    EST_StrList map;

    map.append("$lpc-0+" Stringtoi(lpc_order));
    map.append("$cepc-0+" Stringtoi(cep_order));
    map.append("power");

    fv.resize(EST_CURRENT, map);
    ///@ endcode

    /* An alternative is to use add_channels_to_map()
	which takes a list of coefficient types and makes a map.
	The order of each type of processing is extracted from
	op. 
	*/

    ///@ code

    EST_StrList coef_types;

    coef_types.append("lpc");
    coef_types.append("cep");
    coef_types.append("power");

    map.clear();

    add_channels_to_map(map, coef_types, op);
    fv.resize(EST_CURRENT, map);

    ///@ endcode

    /* After allocating the right number of frames and channels 
	 in fv, we extract a sub_track, which has all the frames
	 (i.e. between 0 and EST_ALL) and all the lpc channels
    */
    ///@ code
    fv.sub_track(part, 0, EST_ALL, 0, "lpc_0", "lpc_N");
    ///@ endcode
    /* now call the signal processing function on this part: */
    ///@ code
    sig2coef(sig, part, "lpc");
    ///@ endcode

    /* We repeat the procedure for the cepstral coefficients, but this
	time take the next 8 channels (17-24 inclusive)  and calculate the coefficients:
    */
    ///@ code
    fv.sub_track(part, 0, EST_ALL, "cep_0", "cep_N");

    sig2coef(sig, part, "cep");
    ///@ endcode
    /* Extract the last channel for power and call the power function:
     */
    ///@ code
    fv.sub_track(part, 0, EST_ALL, "power", 1);
    power(sig, part, 0.01);

    ///@ endcode

     /* While the above technique is adequate for our needs and is
	a useful demonstration of sub_track extraction, the
	sigpr_base function is normally easier to use as it does
	all the sub track extraction itself. To perform the lpc, cepstrum
	and power analysis, we put these names into a StrList and
	call sigpr_base.
     */
    ///@ code
    base_list.clear(); // empty the list, just in case
    base_list.append("lpc");
    base_list.append("cep");
    base_list.append("power");

    sigpr_base(sig, fv, op, base_list);
    ///@ endcode
    /* This will call sigpr_track as many times as is necessary. 
     */
    ///@}

    /* Producing delta and acceleration coefficients  */
    ///@{
    ///@ code

    map.append("$cep_d-0+" Stringtoi(cep_order)); // add deltas
    map.append("$cep_a-0+" Stringtoi(cep_order)); // add accs

    fv.resize(EST_CURRENT, map); // resize the track.
    ///@ endcode
    /*	Given a EST_Track of coefficients fv, the delta
	function is used to produce the delta equivalents del.
    The following uses the track allocated above and
	generates a set of cepstral coefficients and then makes their
	delta and acc:

    */
    ///@ code

    EST_Track del, acc;

    fv.sub_track(part, 0, EST_ALL, 0, "cep_0", "cep_N"); // make subtrack of coefs
    sig2coef(sig, part, "cep");  // fill with cepstra

    // make subtrack of deltas
    fv.sub_track(del, 0, EST_ALL, 0, "cep_d_0", "cep_d_N"); 
    delta(part, del);  // calculate deltas of part, and place answer in del

    // make subtrack of accs
    fv.sub_track(acc, 0, EST_ALL, 0, "cep_a_0", "cep_a_N"); 
    delta(del, acc);  // calculate deltas of del, and place answer in acc
    ///@ endcode
    /* It is possible to directly calculate the delta coefficients of
	a type of coefficient, even if we don't have the base type.
	\ref sigpr_delta  will process the waveform, make a temporary
	track of the required type "lpc" and calculate the delta of this.
	</para><para>
	The following makes a set of delta reflection coefficients:
	
    */
    ///@ code
    map.append("$ref_d-0+" Stringtoi(lpc_order)); // add to map 
    fv.resize(EST_CURRENT, map); // resize the track.

    sigpr_delta(sig, fv, op, "ref");
    ///@ endcode
    /* an equivalent function exists for acceleration coefficients:
     */
    ///@ code
    map.append("$lsf_a-0+" Stringtoi(lpc_order)); // add acc lsf
    fv.resize(EST_CURRENT, map); // resize the track.

    sigpr_acc(sig, fv, op, "ref");

    ///@ endcode
    ///@}

    /* Windowing

      The \ref EST_Window  class provides a variety of means to
      divide speech into frames using windowing mechanisms.

      A window function can be created from a window name using the
      \ref EST_Window::creator  function:
     */
    ///@{
    ///@ code

    EST_WindowFunc *hamm =  EST_Window::creator("hamming");
    EST_WindowFunc *rect =  EST_Window::creator("rectangular");
    ///@ endcode
    /* This function can then be used to create a EST_TBuffer of 
	window values. In the following example the values from a
	256 point hamming window are stored in the buffer win_vals:
    */
    ///@ code
    EST_FVector frame;
    EST_FVector win_vals;

    hamm(256, win_vals);
    ///@ endcode

    /* The make_window function also creates a window:
     */
    ///@ code
    EST_Window::make_window(win_vals, 256, "hamming",-1);
    ///@ endcode

    /* this can then be used to make a frame of speech from the main EST_Wave
	sig. The following example extracts speech starting at sample 1000:
    */
    ///@ code
    for (i = 0; i < 256; ++i)
	frame[i] = (float)sig.a(i + 1000) * win_vals[i];
    ///@ endcode

    /* Alternatively, exactly the same operation can be performed in a
	single step by passing the window function to the
	\ref EST_Window::window_signal  function which takes a
	\ref EST_Wave  and performs windowing on a section of it,
	storing the output in the \ref EST_FVector  {\tt frame}.
    */
    ///@ code
    EST_Window::window_signal(sig, hamm, 1000, 256, frame, 1);
    ///@ endcode
    /* The window function need not be explicitly created, the window
	signal can work on just the name of the window type:
    */

    ///@ code
    EST_Window::window_signal(sig, "hamming", 1000, 256, frame, 1);
    ///@ endcode

    ///@}
    /* Frame based signal processing
      The signal processing library provides an extensive set of functions
      which operate on a single frame of coefficients.
      The following example shows one method of splitting the signal
      into frames and calling a signal processing algorithm.

      First set up the track for 16 order LP analysis:

      */
    ///@{
    ///@ code

    map.clear();
    map.append("$lpc-0+16");
    
    fv.resize(EST_CURRENT, map);

    ///@ endcode
    /* In this example, we take the analysis frame length to be 256 samples
	long, and the shift in samples is just the shift in seconds times the
	sampling frequency.
    */
    ///@ code
    int s_length = 256;
    int s_shift =  int(shift * float(sig.sample_rate()));
    EST_FVector coefs;
    ///@ endcode

    /* Now we set up a loop which calculates the frames one at a time.
    */
    ///@ code
    for (int k1 = 0; k1 < fv.num_frames(); ++k1)
    {
	int start = (k1 * s_shift) - (s_length/2);
	EST_Window::window_signal(sig, "hamming", start, s_length, frame, 1);

	fv.frame(coefs, k1); 	// Extract a single frame
	sig2lpc(frame, coefs); 	// Pass this to actual algorithm
    }
    ///@ endcode

    /* A slightly different tack can be taken for pitch-synchronous analysis.
	Setting up fv with the pitchmarks and channels:
    */
    ///@ code
    fv.load(DATA "/kd1_001.pm");
    fv.resize(EST_CURRENT, map);
    ///@ endcode
    /* Set up as before, but this time calculate the window starts and 
	lengths from the time points. In this example, the length is a 
	{\tt factor} (twice) the local frame shift.
	Note that the only difference between this function and the fixed
	frame one is in the calculation of the start and end points - the

	windowing, frame extraction and call to \ref sig2lpc  are exactly
	the same.
    */
    ///@ code
    float factor = 2.0;

    for (int k2 = 0; k2 < fv.num_frames(); ++k2)
    {
	s_length = irint(get_frame_size(fv, k2, sig.sample_rate())* factor);
	int start = (irint(fv.t(k2) * sig.sample_rate()) - (s_length/2));

	EST_Window::window_signal(sig, wf, start, s_length, frame, 1);

	fv.frame(coefs, k2);
	sig2lpc(frame, coefs);
    }
    ///@ endcode
    ///@}

    /* Filtering    */
    ///@{
    ///@ code

    EST_FVector filter;
    int freq = 400;
    int filter_order = 99;

    filter = design_lowpass_FIR_filter(sig.sample_rate(), 400, 99);
    ///@ endcode
    /* And now use this filter on the signal:
     */
    ///@ code
    FIRfilter(sig, filter);
    ///@ endcode
    /* For one-off filtering operations, the filter design can be
	done in the filter function itself. The \ref FIRlowpass_filter 
	function takes the signal, cut-off frequency and order as
	arguments and designs the filter on the fly. Because of the
	overhead of filter design, this function is expensive and
	should only be used for one-off operations.
    */
    ///@ code
    FIRlowpass_filter(sig, 400, 99);
    ///@ endcode
    /* The equivalent operations exist for high-pass filtering:
     */
    ///@ code
    filter = design_highpass_FIR_filter(sig.sample_rate(), 50, 99);
    FIRfilter(sig, filter);
    FIRhighpass_filter(sig, 50, 99);
    ///@ endcode
    /* Filters of arbitrary frequency response can also be designed using
	the \ref design_FIR_filter  function. 
    */
    ///@ code
    EST_FVector response(16);
    response[0] = 1;
    response[1] = 1;
    response[2] = 1;
    response[3] = 1;
    response[4] = 0;
    response[5] = 0;
    response[6] = 0;
    response[7] = 0;
    response[8] = 1;
    response[9] = 1;
    response[10] = 1;
    response[11] = 1;
    response[12] = 0;
    response[13] = 0;
    response[14] = 0;
    response[15] = 0;

    filter = design_FIR_filter(response, 15);

    FIRfilter(sig, response);
    ///@ endcode
    /*The normal filtering functions can cause a time delay in the
       filtered waveform. To attempt to eliminate this, a set of
       double filter function functions are provided which guarantees
       zero phase differences between the original and filtered waveform.
    */
    ///@ code
    FIRlowpass_double_filter(sig, 400);
    FIRhighpass_double_filter(sig, 40);
    ///@ endcode

    /* Sometimes it is undesirable to have the input signal overwritten.
	For these cases, a set of parallel functions exist which take
	a input waveform for reading and a output waveform for writing to.
    */
    ///@ code
    EST_Wave sig_out;

    FIRfilter(sig, sig_out, response);
    FIRlowpass_filter(sig, sig_out, 400);
    FIRhighpass_filter(sig, sig_out, 40);
    ///@ endcode
    ///@}

}

///@}


/**@page sigpr-example Example of Signal Processing code
   @brief Signal processing examples
   @dontinclude sigpr_example.cc

@tableofcontents
@section producing-feature-vector-for-utt Producing a single type of feature vector for an utterance

A number of types of signal processing can be performed by the
\ref sig2coef function. The following code demonstrates a simple
case of calculating the linear prediction (LP) coefficients for
a waveform.

First set the order of the lpc analysis to 16 (this entails 17 actual
coefficients) and then load in the waveform to be analysed.

  @skipline //@ code
  @until //@ endcode

Now allocate enough space in the track to hold the analysis.
The following command resizes `fv` to have enough frames for
analysis frames at 0.01 intervals up to the end of the waveform,
(sig.end()), and enough channels to store `lpc_order + 1` coefficients.
The channels are named so as to take lpc coefficients.

  @skipline //@ code
  @until //@ endcode

The positions of the frames, corresponding to the middle of their
analysis window also need to be set. For fixed frame analysis, this
can be done with the EST_Track::fill_time() function:

  @skipline //@ code
  @until //@ endcode

The simplest way to do the actual analysis is as follows, which
will fill the track with the values from the LP analysis using the
default processing controls.

  @skipline //@ code
  @until //@ endcode

In this style of analysis, default values are used to control the
windowing mechanisms which split the whole signal into frames.

Specifically, each frame is defined to start a certain distance 
before the time interval, and extending the same distance after.
This distance is calculated as a function of the local window
spacing and can be adjusted as follows:

Extending one time period before and one time period after the
current time mark:

  @skipline //@ code
  @until //@ endcode

Extending 1.5 time periods before and  after the
current time mark, etc;

  @skipline //@ code
  @until //@ endcode

The type of windowing function may be changed also as this
can be passed in as an optional argument. First we create a window 
function (This is explained more in \ref Windowing).

  @skipline //@ code
  @until //@ endcode
  and then pass it in as the last argument

  @skipline //@ code
  @until //@ endcode


  @section pitchvsfixframe Pitch-Synchronous vs fixed frame analysis.

  Most of the core signal processing functions operate on individual
  frames of speech and are oblivious as to how these frames were
  extracted from the original speech. This allows us to take the frames
  from anywhere in the signal: specifically, this facilitates two
  common forms of analysis:

   - **fixed frame**:  The time points are space at even intervals 
   throughout the signal.
   - **pitch-synchronous**:  The time points represent *pitchmarks*
   and correspond to a specific position in each pitch period,
   e.g. the instant of glottal closure.

  It is a simple matter to fill the time array, but normally 
  pitchmarks are read from a file or taken from another signal
  processing algorithm (see \ref "Pitchmark functions").

  There are many ways to fill the time array for fixed frame analysis.

  manually:      

  @skipline //@ code
  @until //@ endcode
  
  or by use of the  member function \ref EST_Track::fill_time

  @skipline //@ code
  @until //@ endcode

  Pitch synchronous values can simply be read from pitchmark
     files:

  @skipline //@ code
  @until //@ endcode

  Regardless of how the time points where obtain, the analysis
  function call is just the same:

  @skipline //@ code
  @until //@ endcode

  @section sigpr-example-naming-channels Naming Channels

  Multiple types of feature vector can be stored in the same Track.
  Imagine that we want lpc, cepstrum and power
  coefficients in that order in a track. This can be achieved by using
  the \ref sig2coef function multiple times, or by the wrap
  around \ref sigpr_base function.

  It is vitally important here to ensure that before passing the
  track to the signal processing functions that it has the correct
  number of channels and that these are appropriately named. This is
  most easily done using the track map facility, explained
  in \ref est_trac_naming_channels.

  For each call, we only us the part of track that is relevant.
  The EST_Track::sub_track member function is used to get
  this. In the following example, we are assuming here that 
  `fv` has sufficient space for 17 lpc coefficients, 8 cepstrum 
  coefficients and power and that they are stored in that order.

  @skipline //@ code
  @until //@ endcode

  An alternative is to use \ref add_channels_to_map()
  which takes a list of coefficient types and makes a map.
  The order of each type of processing is extracted from op. 

  @skipline //@ code
  @until //@ endcode

  After allocating the right number of frames and channels 
  in `fv`, we extract a sub_track, which has all the frames
  (i.e. between 0 and EST_ALL) and all the lpc channels.
  
  @skipline //@ code
  @until //@ endcode

  now call the signal processing function on this part:

  @skipline //@ code
  @until //@ endcode

  We repeat the procedure for the cepstral coefficients, but this
  time take the next 8 channels (17-24 inclusive)  and calculate the coefficients:

  @skipline //@ code
  @until //@ endcode
  
  Extract the last channel for power and call the power function:

  @skipline //@ code
  @until //@ endcode

  While the above technique is adequate for our needs and is
  a useful demonstration of sub_track extraction, the
  \ref sigpr_base function is normally easier to use as it does
  all the sub track extraction itself. To perform the lpc, cepstrum
  and power analysis, we put these names into a EST_StrList and
  call \ref sigpr_base.

  @skipline //@ code
  @until //@ endcode
  
  This will call \ref sigpr_track as many times as is necessary. 

  @section sigpr-deltaacc Producing delta and acceleration coefficients

  Delta coefficients represent the numerical differentiation of a
  track, and acceleration coefficients represent the second
  order numerical differentiation.

  By convention, delta coefficients have a "_d" suffix and acceleration
  coefficients "_a". If the coefficient is multi-dimensional, the
  numbers go after the "_d" or "_a".
  
  @skipline //@ code
  @until //@ endcode

  Given a EST_Track of coefficients `fv`, the \ref EST_Track::delta
  function is used to produce the delta equivalents `del`.
  The following uses the track allocated above and
  generates a set of cepstral coefficients and then makes their
  delta and acc:

  @skipline //@ code
  @until //@ endcode
  
  It is possible to directly calculate the delta coefficients of
  a type of coefficient, even if we don't have the base type.
  \ref sigpr_delta will process the waveform, make a temporary
  track of the required type "lpc" and calculate the delta of this.

  The following makes a set of delta reflection coefficients:

  @skipline //@ code
  @until //@ endcode
  
  an equivalent function exists for acceleration coefficients:

  @skipline //@ code
  @until //@ endcode

  @section sigpr-windowing Windowing

  The \ref EST_Window class provides a variety of means to
  divide speech into frames using windowing mechanisms.
  
  A window function can be created from a window name using the
  EST_Window::creator function:
  
  @skipline //@ code
  @until //@ endcode
  
  This function can then be used to create a EST_TBuffer of 
  window values. In the following example the values from a 
  256 point hamming window are stored in the buffer `win_vals`:

  @skipline //@ code
  @until //@ endcode

  The make_window function also creates a window:

  @skipline //@ code
  @until //@ endcode

  this can then be used to make a frame of speech from the main EST_Wave
  `sig`. The following example extracts speech starting at sample 1000:

  @skipline //@ code
  @until //@ endcode

  Alternatively, exactly the same operation can be performed in a
  single step by passing the window function to the
  EST_Window::window_signal function which takes a
  EST_Wave and performs windowing on a section of it,
  storing the output in the EST_FVector `frame`.

  @skipline //@ code
  @until //@ endcode

  The window function need not be explicitly created, the window
  signal can work on just the name of the window type:

  @skipline //@ code
  @until //@ endcode

  @section sigpr-example-frames Frame based signal processing

  The signal processing library provides an extensive set of functions
  which operate on a single frame of coefficients.
  The following example shows one method of splitting the signal
  into frames and calling a signal processing algorithm.

  First set up the track for 16 order LP analysis:

  @skipline //@ code
  @until //@ endcode
  
  In this example, we take the analysis frame length to be 256 samples
  long, and the shift in samples is just the shift in seconds times the
  sampling frequency.

  @skipline //@ code
  @until //@ endcode

  Now we set up a loop which calculates the frames one at a time.
  `start` is the start position in samples of each frame.
  The EST_Window::window_signal function is called which
  makes a EST_FVector frame of the speech via a hamming window. 
  
  Using the EST_Track::frame function, the EST_FVector 
  `coefs` is set to frame `k` in the track. It is important
  to understand that this operation involves setting an internal
  smart pointer in `coefs` to the memory of frame `k`. This
  allows the signal processing function \ref sig2lpc to operate
  on an input and output EST_FVector, without any copying to or
  from the main track. After the \ref sig2lpc call, the kth frame
  of `fv` is now filled with the LP coefficients.
  
  @skipline //@ code
  @until //@ endcode

  A slightly different tack can be taken for pitch-synchronous analysis.
  Setting up fv with the pitchmarks and channels:

  @skipline //@ code
  @until //@ endcode
  
  Set up as before, but this time calculate the window starts and 
  lengths from the time points. In this example, the length is a 
  `factor` (twice) the local frame shift.
  Note that the only difference between this function and the fixed
  frame one is in the calculation of the start and end points - the
  
  windowing, frame extraction and call to \ref sig2lpc are exactly
  the same.

  @skipline //@ code
  @until //@ endcode

  @section sigpr-filtering Filtering 

  In the EST library we so far have two main types of filter,
  **finite impulse response (FIR)** filters and **linear prediction (LP)**
  filters. **infinite impulse response (IIR)** filters are not yet 
  implemented, though LP filters are a special case of these.

  Filtering involves 2 stages: the design of the filter and the
  use of this filter on the waveform.  

  First we examine a simple low-pass filter which attempts to suppress
  all frequencies about a cut-off. Imagine we want to low pass filter
  a signal at 400Hz. First we design the filter:

  @skipline //@ code
  @until //@ endcode
  
  And now use this filter on the signal:

  @skipline //@ code
  @until //@ endcode
  
  For one-off filtering operations, the filter design can be
  done in the filter function itself. The \ref FIRlowpass_filter
  function takes the signal, cut-off frequency and order as
  arguments and designs the filter on the fly. Because of the
  overhead of filter design, this function is expensive and
  should only be used for one-off operations.

  @skipline //@ code
  @until //@ endcode

  The equivalent operations exist for high-pass filtering:

  @skipline //@ code
  @until //@ endcode
  
  Filters of arbitrary frequency response can also be designed using
  the \ref design_FIR_filter function. This function takes a
  EST_FVector of order \f$2^{N}\f$ which specifies the desired frequency
  response up to 1/2 the sampling frequency. The function returns
  a set of filter coefficients that attempt to match the desired
  reponse.

  @skipline //@ code
  @until //@ endcode

  The normal filtering functions can cause a time delay in the
  filtered waveform. To attempt to eliminate this, a set of
  double filter function functions are provided which guarantees
  zero phase differences between the original and filtered waveform.

  @skipline //@ code
  @until //@ endcode

  Sometimes it is undesirable to have the input signal overwritten.
  For these cases, a set of parallel functions exist which take
  a input waveform for reading and a output waveform for writing to.

  @skipline //@ code
  @until //@ endcode

*/

///@}

