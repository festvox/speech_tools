/*************************************************************************/
/*                                                                       */
/*                Centre for Speech Technology Research                  */
/*                     University of Edinburgh, UK                       */
/*                      Copyright (c) 1995,1996                          */
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
/*                      Author :  Paul Taylor                            */
/*                      Date   :  April 1995                             */
/*-----------------------------------------------------------------------*/
/*                     Change EST_Wave utility main                      */
/*                                                                       */
/*=======================================================================*/
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "EST_Wave.h"
#include "EST_cmd_line.h"
#include "EST_cmd_line_options.h"
#include "EST_sigpr.h"
#include "EST_wave_aux.h"
#include "EST.h"

using namespace std;
#define sgn(x) (x>0?1:x?-1:0)

void wave_extract_channel(EST_Wave &single, const EST_Wave &multi,  EST_IList &ch_list);


void extract_channels(EST_Wave &single, const EST_Wave &multi,  EST_IList &ch_list);


int main (int argc, char *argv[])
{
    EST_Wave sig, sigload;
    EST_String in_file("-"), out_file("-"), op_file(""), test;
    EST_Option al;
    EST_StrList files;
    EST_Litem *p;


    parse_command_line
	(argc, argv, 
	 EST_String("[input file0] [input file1] ... -o [output file]\n")+
	 "Summary: change/copy/combine waveform files\n"+
	 "use \"-\" to make input and output files stdin/out\n"+
	 "-h               Options help\n\n"+
	 options_wave_input()+ 
	 options_wave_output()+
	 "-scale <float> Scaling factor. Increase or descrease the amplitude\n"
	 "    of the whole waveform by the factor given\n\n"

	 "-scaleN <float>  Scaling factor with normalization. \n"
	 "    The waveform is scaled to its maximum level, after which \n"
	 "    it is scaled by the factor given\n\n"

	 "-lpfilter <int>  Low pass filter, with cutoff frequency in Hz \n"
	 "    Filtering is performed by a FIR filter which is built at run \n"
	 "    time. The order of the filter can be given by -forder. The \n"
	 "    default value is 199\n\n"

	 "-hpfilter <int>  High pass filter, with cutoff frequency in Hz \n"
	 "    Filtering is performed by a FIR filter which is \n"
	 "    built at run time. The order of the filter can \n"
	 "    be given by -forder. The default value is 199.\n\n"

	 "-forder <int>  Order of FIR filter used for lpfilter and \n"
	 "    hpfilter. This must be ODD. Sensible values range \n"+
	 "    from 19 (quick but with a shallow rolloff) to 199 \n"
	 "    (slow but with a steep rolloff). The default is 199.\n\n"

	 "-fafter Do filtering after other operations such as \n"
	 "    resampling (default : filter before other operations)\n\n"

	 "-info Print information about file and header. \n"
	 "    This option gives useful information such as file \n"
	 "    length, sampling rate, number of channels etc\n"
	 "    No output is produced\n\n"

	 "-add A new single channel waveform is created by adding \n"
	 "    the corresponding sample points of each input waveform\n\n"

	 "-pc <string> Combine input waveforms to form a single \n"
	 "    multichannel waveform.  The argument to this option controls \n"
	 "    how long the new waveform should be. If the option \n"
	 "    is LONGEST, the output wave if the length of the \n"
	 "    longest input wave and shorter waves are padded with \n"
	 "    zeros at the end. If the option is FIRST, the length \n"
	 "    of the new waveform is the length of the first file \n"
	 "    on the command line, and subsequent waves are padded \n"
	 "    or cut to this length\n\n"

	 "-key <ifile> Label file designating subsections, for use with \n"
	 "    -divide. The KEYLAB file is a label file which specifies \n"
	 "    where chunks (such as individual sentences) in \n"
	 "    a waveform begin and end. See section of wave extraction.\n\n"

	 "-divide  Divide a single input waveform into multiple output \n"
	 "    waveforms. Each output waveform is extracted from the \n"
	 "    input waveform by using the KEYLAB file, which \n"
	 "    specifies the start and stop times for each chunk. \n"
	 "    The output files are named according to the filename \n"
	 "    in the KEYLAB file, with extension given by -ext. See \n"
	 "    section on wave extraction\n\n"
		       
	 "-ext <string>    File extension for divided waveforms\n\n"
         
         "-compress <float> Apply Dynamic Range Compression by factor specified \n" 		       

	 "-extract <string> Used in conjunction with -key to extract a \n"
	 "    single section of waveform from the input \n"
	 "    waveform. The argument is the name of a file given \n"
	 "    in the file column of the KEYLAB file.\n",
	 files, al);

    out_file = al.present("-o") ? al.val("-o") : (EST_String)"-";

    // There will always be at least one (or stdin)
    // The first is dealt specially in case its *way* big
    if (read_wave(sig, files.first(), al) != format_ok)
	exit(-1);
    if (al.present("-info")) 
	wave_info(sig);
    // concat or parallelize remaining input files

    if (files.length() > 1)
    {
	for (p= files.head()->next(); p != 0; p=p->next())
	{
	    if (read_wave(sigload, files(p), al) != format_ok)
		exit(-1);
	    if (al.present("-info")) 
		wave_info(sigload);
	    else if (al.present("-pc"))
	    {
		if ((downcase(al.val("-pc")) == "longest") &&
		    (sig.num_samples() < sigload.num_samples()))
		    sig.resize(sigload.num_samples());
		else /* "first" or sig is longer */
		    sigload.resize(sig.num_samples());
		sig |= sigload;
	    }
	    else if (al.present("-add"))
		add_waves(sig, sigload);
	    else
		sig += sigload;
	}
    }

    if (al.present("-info")) 
	exit(0);    // done what I've been asked to so stop

    // All input files are now in a single wave called sig

    // default is to filter before any resampling etc.
    // (this may cause problems for multiplexed data !)
    if(!al.present("-fafter")){
	if(al.present("-lpfilter"))
	    FIRlowpass_filter(sig,al.ival("-lpfilter"),al.ival("-forder"));
	if(al.present("-hpfilter"))
	    FIRhighpass_filter(sig,al.ival("-hpfilter"),al.ival("-forder"));
    }

    if (al.present("-c"))	// extract a channel from a multi-channel wave
    {
	EST_StrList s;
	EST_IList il;
	EST_Wave nsig;
	StringtoStrList(al.val("-c"), s, " ,"); // separator can be space or comma
	StrListtoIList(s, il);
	extract_channels(nsig, sig, il);
	sig = nsig;
    }
    
    if (al.present("-F"))	// resample
	sig.resample(al.ival("-F"));
    
    if (al.present("-compress")) // Dynamic Range Compression
    {
        float mu = al.fval("-compress" , 0);
        float lim = 30000.0;

        sig.compress(mu, lim);
    } 

    if (al.present("-scale"))	// rescale
    {
	float scale = al.fval("-scale", 0);
	sig.rescale(scale);
    }
    if (al.present("-scaleN"))	// rescale
    {
	float scale = al.fval("-scaleN", 0);
	if ((scale < 0) || (scale > 1.0))
	{
	    cerr << "ch_wave: -scaleN must be in range 0 to 1" << endl;
	    exit(-1);
	}
	sig.rescale(scale,1);
    }

    EST_Relation key;

    if (al.present("-divide"))
    {
	EST_WaveList wl;
	if (!al.present("-key"))
	{
	    cerr << "Must have key file specified when dividing waveform\n";
	    exit (-1);
	}
	if (key.load(al.val("-key")) != format_ok)
	    exit(-1);

        if (wave_divide(wl, sig, key, al.val("-ext", 0)) == -1)
	    exit(0);
	for (p = wl.head(); p; p = p->next())
	    wl(p).save(wl(p).name(), al.val("-otype", 0));
	exit(0);
    }
    else if (al.present("-extract"))
    {
	EST_Wave e;
	if (!al.present("-key"))
	{
	    cerr << "Must have key file specified when dividing waveform\n";
	    exit (-1);
	}
	if (key.load(al.val("-key")) != format_ok)
	    exit(-1);

        if (wave_extract(e, sig, key, al.val("-extract")) == -1)
	    exit (-1);
	sig = e;
    }

    // if we are filtering after other operations
    if(al.present("-fafter")){
	if(al.present("-lpfilter"))
	    FIRlowpass_filter(sig,al.ival("-lpfilter"),al.ival("-forder"));
	if(al.present("-hpfilter"))
	    FIRhighpass_filter(sig,al.ival("-hpfilter"),al.ival("-forder"));
    }

    write_wave(sig, out_file, al);
    return 0;
}


