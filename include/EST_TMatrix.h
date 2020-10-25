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
 /*                     Author :  Paul Taylor                             */
 /*                  Rewritten :  Richard Caley                           */
 /* --------------------------------------------------------------------- */
 /*                         Matrix class                                  */
 /*                                                                       */
 /*************************************************************************/

#ifndef TMatrix_H__
#define TMatrix_H__

#include <iostream>
#include <cstddef>

#include "EST_rw_status.h"
#include "EST_TVector.h"
#include "instantiate/EST_TMatrixI.h"

/* When set bounds checks (safe but slow) are done on matrix access */
#ifndef TMATRIX_BOUNDS_CHECKING
#    define TMATRIX_BOUNDS_CHECKING 0
#endif

#if TMATRIX_BOUNDS_CHECKING
#define A_CHECK a_check
#else
#define A_CHECK a_no_check
#endif

/** \class EST_TMatrix
  * \ingroup containerclasses
  * \brief Template Matrix class. This is an extension of the EST_TVector class to two dimensions.
  *
  * @see matrix_example
  * @see EST_TVector
  */
template <typename T> 
class EST_TMatrix : public EST_TVector<T>
{

public:
  using typename EST_TVector<T>::value_type;
  using typename EST_TVector<T>::size_type;
  using typename EST_TVector<T>::difference_type;
  using typename EST_TVector<T>::reference;
  using typename EST_TVector<T>::const_reference;
  using typename EST_TVector<T>::pointer;
  using typename EST_TVector<T>::const_pointer;

protected:
  /// Visible shape
  size_type p_num_rows; 
  
  /// How to access the memory
  size_type p_row_step;

  inline difference_type mcell_pos(difference_type r, difference_type c,
			       difference_type rs, difference_type cs) const
    { return (rs==1?r:(r*rs)) + (cs==1?c:(c*cs));}

  inline difference_type mcell_pos(difference_type r, difference_type c) const {

    return mcell_pos(r, c, this->p_row_step, this->p_column_step);
  }

  inline difference_type mcell_pos_1(difference_type r, difference_type c) const {

    (void)r;
    return c;
  }

  /// quick method for returning `x[m][n]`
  inline const_reference fast_a_m(difference_type r, difference_type c) const 
    { return this->p_memory[mcell_pos(r,c)]; }
  inline reference fast_a_m(difference_type r, difference_type c) 
    { return this->p_memory[mcell_pos(r,c)]; }

  inline const_reference fast_a_1(difference_type r, difference_type c) const 
    { return this->p_memory[mcell_pos_1(r,c)]; }
  inline reference fast_a_1(difference_type r, difference_type c) 
    { return this->p_memory[mcell_pos_1(r,c)]; }
  

    /// Get and set values from array
  void set_values(const_pointer data, 
		  difference_type r_step, difference_type c_step,
		  size_type start_r, size_type num_r,
		  size_type start_c, size_type num_c
		  );
  void get_values(pointer data, 
		  difference_type r_step, difference_type c_step,
		  size_type start_r, size_type num_r,
		  size_type start_c, size_type num_c
		  ) const;

  /// private resize and copy function. 
  void copy(const EST_TMatrix<T> &a);
  /// just copy data, no resizing, no size check.
  void copy_data(const EST_TMatrix<T> &a); 

  /// resize the memory and reset the bounds, but don't set values.
  void just_resize(size_type new_rows, size_type new_cols, pointer* old_vals);

  /// sets data and length to default values (0 in both cases).
  void default_vals();
public:

  ///default constructor
  EST_TMatrix(); 

  /// copy constructor
  EST_TMatrix(const EST_TMatrix<T> &m); 

  /// "size" constructor
  EST_TMatrix(size_type rows, size_type cols); 

  /// construct from memory supplied by caller
  EST_TMatrix(size_type rows, size_type cols, 
	      pointer memory, difference_type offset=0, bool free_when_destroyed=false);

  /// EST_TMatrix

  ~EST_TMatrix();

  /**@name access
    * Basic access methods for matrices.
    */
  //@{

  /// return number of rows
  size_type num_rows() const {return this->p_num_rows;}
  /// return number of columns
  size_type num_columns() const {return this->p_num_columns;}

  /// const access with no bounds check, care recommend
  inline const_reference a_no_check(difference_type row, difference_type col) const 
    { return fast_a_m(row,col); }
  /// access with no bounds check, care recommend
  inline reference a_no_check(difference_type row, difference_type col) 
    { return fast_a_m(row,col); }

  inline const_reference a_no_check_1(difference_type row, difference_type col) const { return fast_a_1(row,col); }
  inline reference a_no_check_1(difference_type row, difference_type col) { return fast_a_1(row,col); }

  /// const element access function 
  const T& a_check(difference_type row, difference_type col) const;
  /// non-const element access function 
  T& a_check(difference_type row, difference_type col);

  const_reference a(difference_type row, difference_type col) const { return A_CHECK(row,col); }
  reference a(difference_type row, difference_type col) { return A_CHECK(row,col); }

  /// const element access operator
  const_reference operator () (difference_type row, difference_type col) const { return a(row,col); }
  /// non-const element access operator
  reference operator () (difference_type row, difference_type col) { return a(row,col); }
  
  //@}

  bool have_rows_before(difference_type n) const;
  bool have_columns_before(difference_type n) const;

  /** resize matrix. If `set=true`, then the current values in
      the matrix are preserved up to the new size `n`. If the
      new size exceeds the old size, the rest of the matrix is
      filled with the `def_val`
  */
    void resize(size_type rows, size_type cols, bool set=true); 

  /// fill matrix with value v
  void fill(const_reference v);
  void fill() { fill(*this->def_val); }

  /// assignment operator
  EST_TMatrix &operator=(const EST_TMatrix &s); 

  /// The two versions of what might have been operator +=
  EST_TMatrix &add_rows(const EST_TMatrix &s); 
  EST_TMatrix &add_columns(const EST_TMatrix &s); 

  /**@name Sub-Matrix/Vector Extraction
    *
    * All of these return matrices and vectors which share
    * memory with the original, so altering values them alters
    * the original. 
    */
  ///@{

  /// Make the vector `rv` a window onto row `r`
  void row(EST_TVector<T> &rv, int r, int start_c=0, int len=-1);
  /// Make the vector `cv` a window onto column `c`
  void column(EST_TVector<T> &cv, int c, int start_r=0, int len=-1);
  /// Make the matrix `sm` a window into this matrix.
  void sub_matrix(EST_TMatrix<T> &sm,
		  int r=0, int numr=EST_ALL, 
		  int c=0, int numc=EST_ALL);
  ///@}

  /**@name Copy in and out
    * Copy data between buffers and the matrix.
    */
  ///@{
    /** Copy row `r` of matrix to `buf`. `buf`
        should be pre-malloced to the correct size.
        */
    void copy_row(int r, T *buf, int offset=0, int num=-1) const;

    /** Copy row `r` of matrix to
        `buf`. `buf` should be
        pre-malloced to the correct size.  */
    
    void copy_row(int r, EST_TVector<T> &t, int offset=0, int num=-1) const;

    /** Copy column `c` of matrix to `buf`. `buf`
        should be pre-malloced to the correct size.
        */
    void copy_column(int c, T *buf, int offset=0, int num=-1) const;

    /** Copy column `c` of matrix to
        `buf`. `buf` should
        be pre-malloced to the correct size.  */

    void copy_column(int c,  EST_TVector<T> &t, int offset=0, int num=-1)const;

    /** Copy buf into row `n` of matrix. 
        */
    void set_row(int n, const T *buf, int offset=0, int num=-1);

    void set_row(int n, const EST_TVector<T> &t, int offset=0, int num=-1)
      { set_row(n, t.memory(), offset, num); }

    void set_row(int r, 
                 const EST_TMatrix<T> &from, int from_r, int from_offset=0,
                 int offset=0, int num=-1); // set nth row


    /** Copy buf into column `n` of matrix.         
      */
    void set_column(int n, const T *buf, int offset=0, int num=-1);

    void set_column(int n, const EST_TVector<T> &t, int offset=0, int num=-1)
      { set_column(n, t.memory(), offset, num); }
    
    void set_column(int c, 
                    const EST_TMatrix<T> &from, int from_c, int from_offset=0, 
                    int offset=0, int num=-1); // set nth column

  /** For when you absolutely have to have access to the memory.
    */
  void set_memory(T *buffer, int offset, int rows, int columns, 
		  int free_when_destroyed=0);

  ///@}

  /**@name Matrix file input / output
    */
  ///@{
  /// load Matrix from file - Not currently implemented.
  EST_read_status  load(const class EST_String &filename);
  /// save Matrix to file `filename`
  EST_write_status save(const class EST_String &filename) const;

  /// print matrix.
  friend std::ostream& operator << (std::ostream &st,const EST_TMatrix<T> &a)
    {
        for (size_type i = 0; i < a.num_rows(); ++i) {
            for (size_type j = 0; j < a.num_columns(); ++j) 
                st << a.a_no_check(i, j) << " "; 
            st << std::endl;
        }
        return st;
    }
  ///@}
  
};

#undef A_CHECK

#endif // TMatrix_H__

