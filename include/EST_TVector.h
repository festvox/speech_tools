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
/*                       Author :  Paul Taylor                           */
/*                       Date   :  April 1996                            */
/*-----------------------------------------------------------------------*/
/*                           Vector class                                */
/*                                                                       */
/*=======================================================================*/

#ifndef EST_TVector_H__
#define EST_TVector_H__

#include <cstddef>
#include <iostream>
using namespace std; // FIXME: To be removed
#include "EST_bool.h"
#include "EST_rw_status.h"
#include "../base_class/EST_matrix_support.h"

#include "instantiate/EST_TVectorI.h"

template<class T> class EST_TMatrix;
template<class T> class EST_TList;
class EST_String;

/* A constants to make it clearer what is going on when we pass `-1'
  * meaning `current size' or `all the rest'
  */

extern std::ptrdiff_t const EST_CURRENT;
extern std::ptrdiff_t const EST_ALL;

/* When set bounds checks (safe but slow) are done on vector access */
#ifndef TVECTOR_BOUNDS_CHECKING
#    define TVECTOR_BOUNDS_CHECKING 0
#endif

#if TVECTOR_BOUNDS_CHECKING
#define A_CHECK a_check
#else
#define A_CHECK a_no_check
#endif

/** @class EST_TVector
 *  @brief Template vector
 *  @ingroup containerclasses
 *  @tparam T Type of vector elements

    This serves as a base class for a vector
     of type `T`.  This acts as a higher level
     version of a normal C array as defined as `float *x`, etc.

     The vector can be resized after declaration, access can be 
     with or without bounds checking.  Round brackets denote read-only
     access (for consts) while square brackets are for read-write access.
     In both cases references are returned.

     The standard operators () and [] should be thought of as 
     having no bounds checking, though they may do so optionally
     as a compile time option.  The methods EST_TVector::a_check and 
     EST_TVector::a_nocheck provide explicit boundary checking/nonchecking,
     both const and non-const versions are provided.

     Access through () and [] are guaranteed to be as fast as standard
     C arrays (assuming a reasonable optimizing compiler).  

     @code{.cpp}
     EST_FVector x(10);
     std::ptrdiff_t i;

     for (i=0; i < x.length(); ++i)
        x[i] = sqrt((float)i);
     
     x.resize(20);

     for (i=10; i < x.length(); ++i)
        x[i] = sqrt((float)i);

     @endcode

     To instantiate a template for a a vector of type `FooBar`

     @code{.cpp}
     #include "../base_class/EST_TVector.cc"
     // If you want List to vector conversion (and defined a TList)
     #include "../base_class/EST_Tvectlist.cc"
       
     template class EST_TVector<FooBar>;
     template std::ostream& operator << 
          (std::ostream &st, const EST_TVector<FooBar> &v);
     @endcode

     The EST library already has template vector instantiations for
     `int`, `float`, `double` and EST_String.  Also types are defined for them
     in \ref EST_types.h as EST_IVector, EST_FVector,
     EST_DVector and EST_StrVector for `int`s,
     `float`s, `doubles`s and \ref EST_String  respectively.

  * @see matrix_example */
template <class T>
class EST_TVector
{
public:
  using value_type = T;
  /* The memory management in this class could allow for negative indexing.
   * This class was using int for indexing.
   * The STL may use unsigned types for indexing, we won't.
   */
  using size_type = std::ptrdiff_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  // protected:
public:
  /** Pointer to the start of the vector. 
    * The start of allocated memory is p_memory-p_offset.
    */
  pointer p_memory; 

  /// Visible shape
  size_type p_num_columns;

  /// How to access the memory
  difference_type p_offset;
  size_type p_column_step;
  
  bool p_sub_matrix;

  
  /// The memory access rule, in one place for easy reference
  inline difference_type vcell_pos(difference_type c,
                                   size_type cs) const
    {return cs == 1 ? c : c * cs;}

  inline difference_type vcell_pos(difference_type c) const
    {
      return vcell_pos(c, 
		      p_column_step);
    }

  inline difference_type vcell_pos_1(difference_type c) const
    {
      return c;
    }

  /// quick method for returning \(x[n]\)
  inline const_reference fast_a_v(difference_type c) const { return p_memory[vcell_pos(c)]; }

  inline reference fast_a_v(difference_type c) { return p_memory[vcell_pos(c)]; }

  inline const_reference fast_a_1(difference_type c) const { return p_memory[vcell_pos_1(c)]; }
  inline reference fast_a_1(difference_type c) { return p_memory[vcell_pos_1(c)]; }

  /// Get and set values from array
  void set_values(const_pointer data, difference_type step, size_type start_c,
                  size_type num_c);
  void get_values(pointer data, difference_type step, size_type start_c,
                  size_type num_c) const;

  /// private copy function, called from all other copying functions.
  void copy(const EST_TVector<T> &a); 
  /// just copy data, no resizing, no size check.
  void copy_data(const EST_TVector<T> &a); 

  /// resize the memory and reset the bounds, but don't set values.
  void just_resize(size_type new_cols, pointer *old_vals);

  /// sets data and length to default values (0 in both cases).
  void default_vals();

public:
  ///default constructor
  EST_TVector(); 

  /// copy constructor
  EST_TVector(const EST_TVector<T> &v); 

  /// "size" constructor - make vector of size n.
  EST_TVector(size_type n);

  /// construct from memory supplied by caller
  EST_TVector(size_type n,
	      pointer memory, difference_type offset=0, bool free_when_destroyed=false);

  /// destructor.
  ~EST_TVector();

  /// default value, used for filling matrix after resizing
  static const_pointer def_val;

  /** A reference to this variable is returned if you try and access
   * beyond the bounds of the matrix. The value is undefined, but you
   * can check for the reference you get having the same address as
   * this variable to test for an error.
   */
  static pointer error_return;

  /** resize vector. If `set=1`, then the current values in
      the vector are preserved up to the new length `n`. If the
      new length exceeds the old length, the rest of the vector is
      filled with the `def_val`
  */
  void resize(size_type n, bool set = true);

  /** For when you absolutely have to have access to the memory.
   */
  const_pointer memory() const { return p_memory; }
  pointer memory() { return p_memory; }

  /**@name Access
   * Basic access methods for vectors.
   */
  ///@{

  /// number of items in vector.
  inline size_type num_columns() const { return p_num_columns; }
  /// number of items in vector.
  inline size_type length() const { return num_columns(); }
  /// number of items in vector.
  inline size_type n() const { return num_columns(); }

  /// read-only const access operator: without bounds checking
  inline const_reference a_no_check(difference_type n) const { return fast_a_v(n); }
  /// read/write non-const access operator: without bounds checking
  inline reference a_no_check(difference_type n) { return fast_a_v(n); }
  /// read-only const access operator: without bounds checking
  inline const_reference a_no_check_1(difference_type n) const { return fast_a_1(n); }
  /// read/write non-const access operator: without bounds checking
  inline reference a_no_check_1(difference_type n) { return fast_a_1(n); }

  // #define pp_a_no_check(V,N) (pp_fast_a(V,N))

  /// read-only const access operator: with bounds checking
  const_reference a_check(difference_type n) const;
  /// read/write non-const access operator: with bounds checking
  reference a_check(difference_type n);

  const_reference a(difference_type n) const { return A_CHECK(n); }
  reference a(difference_type n) { return A_CHECK(n); }

  /// read-only const access operator: return reference to nth member
  const_reference operator()(difference_type n) const { return A_CHECK(n); }

  // PT
  // /// non const access operator: return reference to nth member
  //  T &operator () (std::ptrdiff_t n) const {return a(n);}

  /// read/write non const access operator: return reference to nth member
  reference operator[](difference_type n) { return A_CHECK(n); }

  //@}

  void set_memory(pointer buffer, difference_type offset, size_type columns,
                  bool free_when_destroyed = false);

  /// assignment operator
  EST_TVector &operator=(const EST_TVector &s);

  /// Fill entire array will value `v`.
  void fill(const_reference v);

  /// Fill vector with default value
  void empty() { fill(*def_val); }

  /// is true if vectors are equal size and all elements are equal.
  bool operator==(const EST_TVector &v) const { return !((*this) != v); }
  /// is true if vectors are not equal size or a single elements isn't equal.
  bool operator!=(const EST_TVector &v) const;

  /// Copy data in and out. Subclassed by SimpleVector for speed.

  void copy_section(pointer dest, difference_type offset = 0,
                    difference_type num = -1) const;
  void set_section(const_pointer src, difference_type offset = 0,
                   difference_type num = -1);

  /// Create a sub vector.
  void sub_vector(EST_TVector<T> &sv, difference_type start_c = 0,
                  difference_type len = -1);
  /// print out vector.
  friend std::ostream &operator<<(std::ostream &st, const EST_TVector<T> &m) {
    for (difference_type i = 0; i < m.n(); ++i)
      st << m(i) << " ";
    st << std::endl;
    return st;
  }

  /// Matrix must be friend to set up subvectors
  friend class EST_TMatrix<T>;

  void integrity() const;
};

/// assignment operator: fill track with values in list `s`.

// This appears unuset and potentially causes a namespace clashes with std::set
// is sparrowhawk is used.
//   template<class T>
//     extern EST_TVector<T> &set(EST_TVector<T> &v, const EST_TList<T> &s);

#undef A_CHECK
#endif //EST_TVector_H__
