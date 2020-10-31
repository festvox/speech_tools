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
 /*                                                                       */
 /*                 Author: Richard Caley (rjc@cstr.ed.ac.uk)             */
 /*                   Date: Fri Oct 10 1997                               */
 /* --------------------------------------------------------------------  */
 /* A subclass of TMatrix which copies using memcopy. This isn't          */
 /* suitable for matrices of class objects which have to be copied        */
 /* using a constructor or specialised assignment operator.               */
 /*                                                                       */
 /*************************************************************************/

#include "EST_TSimpleMatrix.h"
#include "EST_TVector.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include "EST_cutils.h"


template<class T> 
void EST_TSimpleMatrix<T>::copy_data(const EST_TSimpleMatrix<T> &a)
{
    
  if (!a.p_sub_matrix && !this->p_sub_matrix)
    std::memcpy(&this->a_no_check(0,0),
	        &a.a_no_check(0,0),
	        this->num_rows()*this->num_columns()*sizeof(T)
	        );
  else
    {
    for (EST_TSimpleMatrix<T>::difference_type i = 0; i < this->num_rows(); ++i)
      for (EST_TSimpleMatrix<T>::difference_type j = 0; j < this->num_columns(); ++j)
	this->a_no_check(i,j) = a.a_no_check(i,j);
    }
}

template<class T> 
void EST_TSimpleMatrix<T>::copy(const EST_TSimpleMatrix<T> &a)
{
  if (this->num_rows() != a.num_rows() || this->num_columns() != a.num_columns())
    resize(a.num_rows(), a.num_columns(), 0);
  
  copy_data(a);
}

template<class T> 
EST_TSimpleMatrix<T>::EST_TSimpleMatrix(const EST_TSimpleMatrix<T> &in) : EST_TMatrix<T>(in)
{
    copy(in);
}

template<class T> 
void EST_TSimpleMatrix<T>::resize(EST_TSimpleMatrix<T>::size_type new_rows, 
				  EST_TSimpleMatrix<T>::size_type new_cols, 
				  int set)
{
  EST_TSimpleMatrix<T>::pointer old_vals=NULL;
  EST_TSimpleMatrix<T>::difference_type old_offset = this->p_offset;

  if (new_rows<0)
    new_rows = this->num_rows();
  if (new_cols<0)
    new_cols = this->num_columns();

  if (set)
    {
      if (!this->p_sub_matrix && new_cols == this->num_columns() && new_rows != this->num_rows())
	{
	  EST_TSimpleMatrix<T>::size_type copy_r = std::min(this->num_rows(), new_rows);

	  this->just_resize(new_rows, new_cols, &old_vals);

	  std::memmove(this->p_memory, old_vals, copy_r*new_cols*sizeof(T));
	  
	  if (new_rows > copy_r)
          {
	    if (*this->def_val == 0)
	      {
                  std::memset(
                      this->p_memory + copy_r*this->p_row_step,
                      0,
                      (new_rows-copy_r)*new_cols*sizeof(T)
                  );
	      }
	    else
	      {
		for(EST_TSimpleMatrix<T>::difference_type j=0; j<new_cols; j++)
		  for(EST_TSimpleMatrix<T>::difference_type i=copy_r; i<new_rows; i++)
		    this->a_no_check(i,j) = *this->def_val;
	      }
          }
	}
      else if (!this->p_sub_matrix)
	{
	  EST_TSimpleMatrix<T>::size_type old_row_step = this->p_row_step;
	  EST_TSimpleMatrix<T>::size_type old_column_step = this->p_column_step;
	  EST_TSimpleMatrix<T>::size_type copy_r = std::min(this->num_rows(), new_rows);
	  EST_TSimpleMatrix<T>::size_type copy_c = std::min(this->num_columns(), new_cols);
	  
	  this->just_resize(new_rows, new_cols, &old_vals);

	  this->set_values(old_vals,
		     old_row_step, old_column_step,
		     0, copy_r,
		     0, copy_c);

	  
	  for(EST_TSimpleMatrix<T>::difference_type i=0; i<copy_r; i++)
	    for(EST_TSimpleMatrix<T>::difference_type j=copy_c; j<new_cols; j++)
	      this->a_no_check(i,j) =  *this->def_val;
	  
	  if (new_rows > copy_r)
          {
	    if (*this->def_val == 0)
	      {
                  std::memset(
                      this->p_memory + copy_r*this->p_row_step,
                      0,
                      (new_rows-copy_r)*new_cols*sizeof(T));
	      }
	    else
	      {
		for(EST_TSimpleMatrix<T>::difference_type j=0; j<new_cols; j++)
		  for(EST_TSimpleMatrix<T>::difference_type i=copy_r; i<new_rows; i++)
		    this->a_no_check(i,j) = *this->def_val;
	      }
          }
	}
      else
	EST_TMatrix<T>::resize(new_rows, new_cols, 1);
    }
  else
    EST_TMatrix<T>::resize(new_rows, new_cols, 0);

  if (old_vals && old_vals != this->p_memory)
    delete [] (old_vals-old_offset);
}

template<class T> EST_TSimpleMatrix<T> &EST_TSimpleMatrix<T>::operator=(const EST_TSimpleMatrix<T> &in)
{
    copy(in);
    return *this;
}

