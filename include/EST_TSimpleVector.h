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
 /*                                                                       */
 /*                 Author: Richard Caley (rjc@cstr.ed.ac.uk)             */
 /*                   Date: Fri Oct 10 1997                               */
 /* --------------------------------------------------------------------  */
 /* A subclass of TVector which copies using memcopy. This isn't          */
 /* suitable for matrices of class objects which have to be copied        */
 /* using a constructor or specialised assignment operator.               */
 /*                                                                       */
 /*************************************************************************/

#ifndef EST_TSimpleVector_H__
#define EST_TSimpleVector_H__

#include "EST_TVector.h"
#include "instantiate/EST_TSimpleVectorI.h"

/** \class EST_TSimpleVector
 *  @ingroup containerclasses

 *  A derived class from EST_TVector which is used for
 *  containing simple types, such as `float` or `int`.
*/
template <class T> class EST_TSimpleVector : public EST_TVector<T> {
public:
  using value_type = T;
  using typename EST_TVector<T>::size_type;
  using typename EST_TVector<T>::difference_type;
  using typename EST_TVector<T>::reference;
  using typename EST_TVector<T>::const_reference;
  using typename EST_TVector<T>::pointer;
  using typename EST_TVector<T>::const_pointer;

private:
    /// private copy function
    void copy(const EST_TSimpleVector<T> &a); 
public:
    ///default constructor
    EST_TSimpleVector() : EST_TVector<T>() {}; 
    /// copy constructor
    EST_TSimpleVector(const EST_TSimpleVector<T> &v);
    /// "size" constructor
    EST_TSimpleVector(size_type n): EST_TVector<T>(n) {}; 
    /// memory constructor
    EST_TSimpleVector(size_type n, pointer memory, difference_type offset=0, 
		      bool free_when_destroyed=false):
        EST_TVector<T>(n,memory, offset, free_when_destroyed) {}; 

    /// resize vector
    void resize(size_type n, bool set=true); 

    /// assignment operator
    EST_TSimpleVector &operator=(const EST_TSimpleVector<T> &s); 

    void copy_section(pointer dest, difference_type offset=0,
                      difference_type num=-1) const;
    void set_section(const_pointer src, difference_type offset=0,
                     difference_type num=-1);

    /// Fill entire array with 0 bits. 
    void zero(void);

    //    /// Fill vector with default value
    //    void empty(void) { if (*this->def_val == 0) zero(); else fill(*this->def_val); }
};

#endif
