/*************************************************************************/
/*                                                                       */
/*                Centre for Speech Technology Research                  */
/*                     University of Edinburgh, UK                       */
/*                         Copyright (c) 1996                            */
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
/*                    Author :  Paul Taylor                              */
/*                    Date   :  February 1996                            */
/*-----------------------------------------------------------------------*/
/*                    Event RFC Synthesis                                */
/*                                                                       */
/*=======================================================================*/

#include "EST_cmd_line.h"
#include "EST_tilt.h"
#include "EST_Track.h"
#include "ling_class/EST_relation_aux.h"
#include "EST_string_aux.h"

using namespace std;

void extract_channels(EST_Wave &single, const EST_Wave &multi,  EST_IList &ch_list);


int main (int argc, char *argv[])
{
    EST_Track fz, nfz;
    EST_Relation ev;
    EST_Option al, op;
    EST_String out_file("-"), ev_format, pstring;
    EST_StrList files, event_list;
    EST_Item *e;

    float shift;
    const float default_frame_shift = 0.01; // i.e 10ms intervals

    parse_command_line
	(argc, argv,
       EST_String("[input label file] -o [output file] [options]") +
	 "Summary: generate F0 file from tilt or RFC label file\n"
	 "use \"-\" to make input and output files stdin/out\n"
	 "-h               Options help\n\n"+
	 "-noconn          Synthesize events only - no connections in output\n"
	 "-o <ofile>       Output F0 file\n"
	 "-otype <string>  File type for output label file\n"
	 "-event_names   <string>  List of labels to be classed as events. \n"
	 "     Lists are specified as quoted strings with spaces \n"
	 "     separating each item, e.g.: \"a b c d\"\n\n"
	 "-s <float>       Frame spacing of generated contour in seconds\n",
	files, al);

    out_file = al.present("-o") ? al.val("-o") : (EST_String)"-";
    init_lib_ops(al, op);

    ev.load(files.first());

    // temporary fix until status of start and end is finalised
    float prev_end = 0.0;

    for (e = ev.head(); e; e = inext(e))
    {
	e->set("start", prev_end);
	prev_end = e->F("end");
    }

    pstring = al.present("-event_names") ? al.val("-event_names"): 
    EST_String("a b ab pos");
    StringtoStrList(pstring, event_list);

    convert_to_broad(ev, event_list, "int_event");
    shift = al.present("-s") ? al.fval("-s") : default_frame_shift;

    if (ev.f("intonation_style") == "tilt")
	tilt_synthesis(fz, ev, shift, al.present("-noconn"));
    else
    {
//	validate_rfc_stream(ev);
	fill_rfc_types(ev);
//	cout << ev;
	rfc_synthesis(fz, ev, shift, al.present("-noconn"));
    }

    fz.set_channel_name("F0", 0);

    fz.save(out_file, al.val("-otype"));
    return 0;
}

void override_lib_ops(EST_Option &a_list, EST_Option &al)
{
    // general options
    a_list.override_val("sample_rate", al.val("-f", 0));
}

