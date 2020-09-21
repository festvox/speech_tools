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
/*                 Author :  Alan Black and Paul Taylor                  */
/*                 Date   :  June 1996                                   */
/*-----------------------------------------------------------------------*/
/*  Non public wave related functions                                    */
/*                                                                       */
/*=======================================================================*/
#ifndef __WAVEP_H__
#define __WAVEP_H__

#include <cstdio>

/* The following three (raw, alaw and ulaw) cannot be in the table as they cannot */
/* identify themselves from files (all three are unheadered)                */
enum EST_read_status load_wave_raw(EST_TokenStream &ts, short **data, int
	 *num_samples, int *num_channels, int *word_size, int
	 *sample_rate,  enum EST_sample_type_t *sample_type, int *bo, int
	 offset, int length, int isample_rate, enum EST_sample_type_t
	 isample_type, int ibo, int inc);
enum EST_write_status save_wave_raw(FILE *fp, const short *data, int offset,
	 int num_samples, int num_channels, 
	 int sample_rate,
	 enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_raw_header(FILE *fp,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_raw_data(FILE *fp, const short *data, int offset,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_read_status load_wave_ulaw(EST_TokenStream &ts, short **data, int
	 *num_samples, int *num_channels, int *word_size, int
	 *sample_rate,  enum EST_sample_type_t *sample_type, int *bo, int
	 offset, int length);
enum EST_write_status save_wave_ulaw(FILE *fp, const short *data, int offset,
				int length, int num_channels, 
				int sample_rate,
				enum EST_sample_type_t, int bo);

enum EST_write_status save_wave_ulaw_header(FILE *fp,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_ulaw_data(FILE *fp, const short *data, int offset,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_read_status load_wave_alaw(EST_TokenStream &ts, short **data, int
	 *num_samples, int *num_channels, int *word_size, int
	 *sample_rate,  enum EST_sample_type_t *sample_type, int *bo, int
	 offset, int length);
enum EST_write_status save_wave_alaw(FILE *fp, const short *data, int offset,
				int length, int num_channels, 
				int sample_rate,
				enum EST_sample_type_t, int bo);

enum EST_write_status save_wave_alaw_header(FILE *fp,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_alaw_data(FILE *fp, const short *data, int offset,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_read_status load_wave_nist(EST_TokenStream &ts, short **data, int
	 *num_samples, int *num_channels, int *word_size, int
	 *sample_rate,  enum EST_sample_type_t *sample_type, int *bo, int
	 offset, int length);

enum EST_write_status save_wave_nist(FILE *fp, const short *data, int offset,
			       int num_samples, int num_channels, 
			       int sample_rate,
			       enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_nist_header(FILE *fp,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_nist_data(FILE *fp, const short *data, int offset,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_read_status load_wave_est(EST_TokenStream &ts, short **data, int
	 *num_samples, int *num_channels, int *word_size, int
	 *sample_rate,  enum EST_sample_type_t *sample_type, int *bo, int
	 offset, int length);

enum EST_write_status save_wave_est(FILE *fp, const short *data, int offset,
			       int num_samples, int num_channels, 
			       int sample_rate,
			       enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_est_header(FILE *fp,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_est_data(FILE *fp, const short *data, int offset,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_read_status load_wave_sd(EST_TokenStream &ts, short **data, int
	 *num_samples, int *num_channels, int *word_size, int
	 *sample_rate,  enum EST_sample_type_t *sample_type, int *bo, int
	 offset, int length);

enum EST_write_status save_wave_sd(FILE *fp, const short *data, int offset,
			      int num_samples, int num_channels, 
			      int sample_rate, 
			      enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_sd_header(FILE *fp,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_sd_data(FILE *fp, const short *data, int offset,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_read_status load_wave_audlab(EST_TokenStream &ts, short **data, int
	 *num_samples, int *num_channels, int *word_size, int
	 *sample_rate,  enum EST_sample_type_t *sample_type, int *bo, int
	 offset, int length);

enum EST_write_status save_wave_audlab(FILE *fp, const short *data, int offset,
			       int num_samples, int num_channels, 
			       int sample_rate, 
			       enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_audlab_header(FILE *fp,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_audlab_data(FILE *fp, const short *data, int offset,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_read_status load_wave_snd(EST_TokenStream &ts, short **data, int
	 *num_samples, int *num_channels, int *word_size, int
	 *sample_rate,  enum EST_sample_type_t *sample_type, int *bo, int
	 offset, int length);

enum EST_write_status save_wave_snd(FILE *fp, const short *data, int offset,
			       int num_samples, int num_channels, 
			       int sample_rate, 
			       enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_snd_header(FILE *fp,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_snd_data(FILE *fp, const short *data, int offset,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_read_status load_wave_aiff(EST_TokenStream &ts, short **data, int
	 *num_samples, int *num_channels, int *word_size, int
	 *sample_rate,  enum EST_sample_type_t *sample_type, int *bo, int
	 offset, int length);

enum EST_write_status save_wave_aiff(FILE *fp, const short *data, int offset,
				int num_samples, int num_channels, 
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_aiff_header(FILE *fp,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_aiff_data(FILE *fp, const short *data, int offset,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_read_status load_wave_riff(EST_TokenStream &ts, short **data, int
	 *num_samples, int *num_channels, int *word_size, int
	 *sample_rate,  enum EST_sample_type_t *sample_type, int *bo, int
	 offset, int length);

enum EST_write_status save_wave_riff(FILE *fp, const short *data, int offset,
				int num_samples, int num_channels, 
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_riff_header(FILE *fp,
				int num_samples, int num_channels,
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

enum EST_write_status save_wave_riff_data(FILE *fp, const short *data, int offset,
				int num_samples, int num_channels, 
				int sample_rate,
				enum EST_sample_type_t sample_type, int bo);

#endif /* __EST_WAVEP_H__ */
