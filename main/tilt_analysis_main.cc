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
/*                  Authors:  Paul Taylor                                */
/*                  Date   :  Oct 95                                     */
/*-----------------------------------------------------------------------*/
/*                 Event RFC and Tilt labelling                          */
/*                                                                       */
/*=======================================================================*/

#include <cstdlib>
#include "EST_tilt.h"
#include "sigpr/EST_sigpr_utt.h"
#include "EST_cmd_line_options.h"
#include "ling_class/EST_relation_aux.h"
#include "EST_string_aux.h"

using namespace std;


#define SIL_NAMES "sil !ENTER !EXIT"
#define EVENT_NAMES "a rb arb m mrb"

void set_fn_start(EST_Relation &ev);
void default_rfc_params(EST_Features &op);
void override_rfc_params(EST_Features &rfc, EST_Option &al);
void rfc_analysis(EST_Track &fz, EST_Relation &ev, EST_Features &op);
void change_label(EST_Relation &seg, const EST_StrList &oname, 
		  const EST_String &nname);

void set_options(EST_Option &al, EST_Features &op);

void option_override(EST_Features &op, EST_Option al, 
		     const EST_String &option, const EST_String &arg);





void extract_channels(EST_Wave &single, const EST_Wave &multi,  EST_IList &ch_list);




int main(int argc, char *argv[])
{
    EST_Track fz, nfz;
    EST_Relation ev;
    EST_Option al;
    EST_Features op;
    EST_StrList files, event_list, sil_list;
    EST_String out_file, pstring;
    EST_Track speech, raw_fz;
    EST_Relation sil_lab;
    EST_Features rfc_op;

    parse_command_line
	(argc, argv, 
       EST_String("[input f0 file] -e [input event label file] -o [output file]"
	 "[options]")+
	 "Summary: produce rfc file from events and f0 contour\n"
	 "use \"-\" to make input and output files stdin/out\n"
	 "-h               Options help\n\n"+
	 options_track_input()+ "\n"
	 "-event_names   <string>  List of labels to be classed as events. \n"
	 "     Lists are specified as quoted strings with spaces \n"
	 "     separating each item, e.g.: \"a b c d\"\n\n"
	 "-sil_names     <string>  List of labels to be classed as silence \n"
	 "     Lists are specified as quoted strings with spaces \n"
	 "     separating each item, e.g.: \"pau sil #\"\n\n"
	 "-e             <ifile> Input event label file. This file contains \n"
	 "     the list of events to be parameterized, each with its approximate \n"
	 "     start and stop time marked. This file also contains silencesn \n"
	 "     which are used to decide where to insert and stop phrases \n\n"
	 "-o <ofile>   Output label file\n\n"
	 "-otype  <string>  File type of output file \n\n"
	 "-limit  <float>   start and stop limit in seconds. The rfc \n"
	 "     matching algorithm defines a search region within which it tries \n"
	 "     all possible rise and fall shapes. This option specifies how much \n"
         "     before the input label start time and how much after the input \n"
	 "     label end time the search region should be. Typical value, 0.1 \n\n"
	 "-range  <float>   Range of RFC search region. In addition to \n" 
	 "     the limit, the range defines the limits of the rfc matching \n" 
	 "     search region as a  percentage of the overall input label \n"
	 "     duration. Typical value, 0.25 (the search region is the first and \n"
	 "     last 25% of the label) \n\n"
	 "-smooth                  Smooth and Interpolate input F0 contour. \n"
	 "     rfc matching can only operate on smooth fully interpolated \n"
	 "     contours. This option must be used if the contour hasn't already \n"
	 "     been smoothed and interpolated\n\n"
	 "-w1 <float>      length in seconds of smoothing window prior\n"
	 "     to interpolation. Default value 0.05 \n\n"
	 "-w2 <float>      length in seconds of smoothing window after\n"
	 "     to interpolation. Default value 0.05 \n\n"
	 "-sf0 <ofile>    Save f0 contour that results from smoothing \n"
	 "-rfc   Save as RFC parameters instead of tilt\n\n", 
			files, al);

    default_rfc_params(rfc_op); 
    override_rfc_params(rfc_op, al);
    set_options(al, op);

    out_file = al.present("-o") ? al.val("-o") : (EST_String)"-";

    if (read_track(nfz, files.first(), al) == -1)
	    exit(-1);
    // REORG - extract proper f0 channel here
    nfz.copy_sub_track(fz, 0, EST_ALL, 0, 1);

    if (ev.load(al.val("-e")) != format_ok)
	exit(-1);

    pstring = (al.present("-event_names") ? al.val("-event_names"): 
	       EST_String("a b ab pos"));
    StringtoStrList(pstring, event_list);
    convert_to_broad(ev, event_list, "int_event", 1);

    // ensure all sil_names are re-written as sil
    pstring = (al.present("-sil_names") ? al.val("-sil_names"): 
	       EST_String(SIL_NAMES));
    StringtoStrList(pstring, sil_list);
    change_label(ev, sil_list, "sil");

    if (al.present("-smooth"))
    {
	sil_lab = ev;	
	StringtoStrList("sil", sil_list);
	convert_to_broad(sil_lab, sil_list, "pos", 0);	
	label_to_track(sil_lab, speech, fz.shift());
	raw_fz = fz;
	smooth_phrase(raw_fz, speech, op, fz);
    }

    if (al.present("-sf0"))
	fz.save(al.val("-sf0"));

    ev.f.set("name", "intevents");
    ev.f.set("timing_style", "segment");

//    set_fn_start(ev);

    // main RFC analysis function
    rfc_analysis(fz, ev, rfc_op);

    // convert to Tilt if necessary
    if (!al.present("-rfc"))
    {
	rfc_to_tilt(ev);
	ev.remove_item_feature("rfc");
    }

    ev.save(out_file);
}



void override_rfc_params(EST_Features &rfc, EST_Option &al)
{
    if (al.present("-limit"))
    {
	rfc.set("start_limit", al.fval("-limit"));
	rfc.set("stop_limit", al.fval("-limit", 0));
    }
    if (al.present("-range"))
	rfc.set("range", al.fval("-range"));
    if (al.present("-min_dur"))
	rfc.set("min_event_duration", al.fval("-min_dur"));
}

void set_options(EST_Option &al, EST_Features &op)
{
    // Nobody else has set window_length or second_length so
    // set defaults here
    op.set("window_length",0.05);
    op.set("second_length",0.05);
    option_override(op, al, "window_length", "-w1");
    option_override(op, al, "second_length", "-w2");
}    
