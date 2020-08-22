/*************************************************************************/
/*                                                                       */
/*                Centre for Speech Technology Research                  */
/*                     University of Edinburgh, UK                       */
/*                     Copyright (c) 1995,1996                           */
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


#ifndef __EST_FFT_H__
#define __EST_FFT_H__

#include "EST_Wave.h"
#include "EST_Track.h"
#include "EST_FMatrix.h"

/**@defgroup FastFourierTransformfunctions Fast Fourier Transform functions
   @ingroup FunctionsForGeneratingFrames

These are the low level functions where the actual FFT is
performed. Both slow and fast implementations are available for
historical reasons. They have identical functionality. At this time,
vectors of complex numbers are handled as pairs of vectors of real and
imaginary numbers.

### What is a Fourier Transform ?

The Fourier transform of a signal gives us a frequency-domain
representation of a time-domain signal. In discrete time, the Fourier
Transform is called a Discrete Fourier Transform (DFT) and is given
by:

\f[y_k = \sum_{t=0}^{n-1} x_t \; \omega_{n}^{kt} \; ; \; k=0...n-1 \f]

where \f$y = (y_0,y_1,... y_{n-1})\f$ is the DFT (of order \f$n\f$ ) of the
signal \f$x = (x_0,x_1,... x_{n-1})\f$, where
\f$\omega_{n}^{0},\omega_{n}^{1},... \omega_{n}^{n-1}\f$ are the n
complex nth roots of 1.


The Fast Fourier Transform (FFT) is a very efficient implementation of
a Discrete Fourier Transform. See, for example "Algorithms" by Thomas
H. Cormen, Charles E. Leiserson and Ronald L. Rivest (pub. MIT Press),
or any signal processing textbook.

*/

///@{

/** \brief Basic in-place FFT. 

There's no point actually using this - use \ref fastFFT
instead. However, the code in this function closely matches the
classic FORTRAN version given in many text books, so is at least easy
to follow for new users.

The length of `real` and `imag` must be the same, and must be 
a power of 2 (e.g. 128).

@see slowIFFT
@see FastFFT */
int slowFFT(EST_FVector &real, EST_FVector &imag);

/** \brief Alternate name for slowFFT
*/
inline int FFT(EST_FVector &real, EST_FVector &imag){
    return slowFFT(real, imag);
}

/** \brief Basic inverse in-place FFT
*/
int slowIFFT(EST_FVector &real, EST_FVector &imag);

/** \brief Alternate name for slowIFFT
*/
inline int IFFT(EST_FVector &real, EST_FVector &imag){
    return slowIFFT(real, imag);
}

/** \brief Power spectrum using the fastFFT function.

The power spectrum is simply the squared magnitude of the
FFT. The result real and imaginary parts are both set equal
to the power spectrum (you only need one of them !)
*/
int power_spectrum(EST_FVector &real, EST_FVector &imag);

/** \brief Power spectrum using the slowFFT function
*/
int power_spectrum_slow(EST_FVector &real, EST_FVector &imag);

/** \brief Fast FFT 
An optimised implementation by Tony Robinson to be used
in preference to slowFFT
*/
int fastFFT(EST_FVector &invec);

// Auxiliary for fastFFT
int fastlog2(int);

///@}


#endif // __EST_FFT_H__

