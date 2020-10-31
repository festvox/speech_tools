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
/*                    Author :  Simon King                               */
/*                    Date   :  November 1996                            */
/*-----------------------------------------------------------------------*/
/*                   Lattice/Finite State Network                        */
/*                                                                       */
/*=======================================================================*/


#ifndef __EST_KALMAN_H__
#define __EST_KALMAN_H__

#include "EST_TVector.h"
#include "EST_FMatrix.h"

bool kalman_filter(EST_FVector &x_state,
		   EST_FMatrix &P_estimate_error_covariance,
		   EST_FMatrix &Q_process_noise_covariance,
		   EST_FMatrix &R_measurement_noise_covariance,
		   EST_FMatrix &A_state_time_step_model,
		   EST_FMatrix &H_state_to_measurement_model,
		   EST_FVector &z_measurement);

bool kalman_filter_Pinv(EST_FVector &x_state,
			EST_FMatrix &Pinv_estimate_error_covariance_inverse,
			EST_FMatrix &Q_process_noise_covariance,
			EST_FMatrix &Rinv_measurement_noise_covariance_inverse,
			EST_FMatrix &A_state_time_step_model,
			EST_FMatrix &H_state_to_measurement_model,
			EST_FVector &z_measurement);

#endif
