 /*************************************************************************/
 /*                                                                       */
 /*                Centre for Speech Technology Research                  */
 /*                     University of Edinburgh, UK                       */
 /*                       Copyright (c) 1996,1997                         */
 /*                        All Rights Reserved.                           */
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
 /*                   Date: Tue Jul 22 1997                               */
 /* --------------------------------------------------------------------- */
 /* Example of list class use.                                            */
 /*                                                                       */
 /*************************************************************************/

#include <cstdlib>
#include <iostream>
#include "EST_TKVL.h"
#include "EST_Option.h"
#include "EST_util_class.h"
#include "EST_types.h"

#if defined(DATAC)
#    define __STRINGIZE(X) #X
#    define DATA __STRINGIZE(DATAC)
#endif

int main(void)
{
    EST_StrStr_KVL kvl;  // decl
    EST_Litem *p; //decl
    EST_Option al; //decl
    EST_Option op; //decl

    // add item simply appends key value pairs onto the end of the list.
    // This function is useful for the initial building of a list.
    
    //@ code
      kvl.add_item("street", "South Bbridge");
      kvl.add_item("city", "Edinburgh");
      kvl.add_item("post code", "EH1 1HN");
      kvl.add_item("country", "United Kingdom");

    //@ endcode

    // by default, if a new entry has the same key name as an existing key,
    // it will not overwrite this, leaving 2 items with the same key.
    // The first will be the one accessed.
    // You can overwrite existing keys by adding a flag to this function.
    // Note  that this is much slower as all the existing keys must
    // be checked.
    
    //@ code

      kvl.add_item("country", "Scotland", 1);
      
    //@ endcode

    // This is equivalent to the change_item function, which is
    // used to overwrite existing entries:

    //@ code

      kvl.change_val("country", "Caledonia");

    //@ endcode

    // KVL_Access

    // Items are accessed by the val function, indexed by the key:
    // This prints the value associated with the key "country".
    //@ code
    
    cout << kvl.val("country") << endl;
    //@ endcode

    // An error is given if the key doesn't exist:
    //@ code
    cout << kvl.val("state") << endl;
    //@ endcode

    // This can be turned off by use of a flag. In this case the default
    // value is returned.

    //@ code
    cout << kvl.val("state", 0) << endl;
    //@ endcode

    // A on-the fly default value can be specified by putting using the
    // val_def function:

    //@ code
    cout << kvl.val_def("state", "unknown") << endl;
    //@ endcode

    // present() returns true of the key exists:
    //@ code
    if (kvl.present("state"))
	cout << kvl.val("state") << endl;;
    //@ endcode

    // Normally, direct access to the list is not needed, but for
    // efficiency's sake, it is sometimes useful to be able to directly
    // access items. The {\tt list} variable contains the key/value
    // list, from this, \ref EST_Litem  pointers can be set to items, and
    // then used in access functions:

    //@ code
    for (p=kvl.head(); p != 0; p=p->next())
	 cout << kvl.val(p) << " " << kvl.key(p) << endl;
    //@ endcode

    // this can also be used to change values: the following changes the
    // value of the pair pointed to by p to "Scotland".

    //@ code
    kvl.change_val(p, "Scotland");
    //@ endcode

    // The name of the key can be changed similarly:

    //@ code
    kvl.change_key(p, "Nation");
    //@ endcode


    // load in options from file. The file is in the form of one key
    // value pair per line. The key ends at the end of the first
    // whitespace delimited token, which allows the values to have
    // spaces. Eg.
    // Country  Scotland
    // Street South Bridge
    // Number 80
    // Height 23.45

    // load in file
    //@ code
    op.load(DATA "/options.file");
    //@ endcode

    // All the normal EST_KVL accessing and addition functions
    // work. Although the type of the value is a String, functions are
    // provided to allow easy casting to ints and floats.

    //@ code
    cout << op.val("Street") << endl;
    //@ endcode
    // print out number as an integer
    
    //@ code
    cout << op.ival("Number") << endl;
    //@ endcode
    
    // print out height as a float
    //@ code
    cout << op.fval("Height") << endl;
    //@ endcode
    // Often, one wishes to override an existing value if a new value
    // has been set. The override_val function is useful for this. In
    // the following example, the command line argument is held in the
    // {\tt al} object. A default value is put in the length field. If
    // the command line option is present, it overrides "length",
    // otherwise "length" is left unchanged:

    //@ code
    op.add_fitem("length", 39.78);
    op.override_fval("length", al.fval("-l", 0));
    //@ endcode

    // This is quicker than the alternative:

    //@ code
    op.add_fitem("length", 39.78);

    if (al.present("-l"))
	op.override_fval("length", al.fval("-l", 0));

    //@ endcode

}



/** @page EST_KVL-example EST_KVL Example 
    @brief Example of Key-Value list
    @tableofcontents
    @dontinclude kvl_example.cc
    
    @section KVL_Addition Adding items to a KVL

    EST_KVL::add_item simply appends key value pairs onto the end of the list.
    This function is useful for the initial building of a list.
    
    @skipline //@ code
    @until //@ endcode

    By default, if a new entry has the same key name as an existing key,
    it will not overwrite this, leaving 2 items with the same key.
    The first will be the one accessed.
    You can overwrite existing keys by adding a flag to this function.
    Note  that this is much slower as all the existing keys must
    be checked.

    @skipline //@ code
    @until //@ endcode

    This is equivalent to the EST_KVL::change_item function, which is
    used to overwrite existing entries:
    
    @skipline //@ code
    @until //@ endcode
    
   
    @section KVL_Access Accessing EST_KVL
    The usual way to access the list is to pass in the name of the
    key to the EST_StrStr_KVL::val function, which then returns the value
    associated with that key.
    @skipline //@ code
    @until //@ endcode


    Items are accessed by the val function, indexed by the key: This 
    prints the value associated with the key "country".
    @skipline //@ code
    @until //@ endcode
    
    An error is given if the key doesn't exist:
    @skipline //@ code
    @until //@ endcode
    
    This can be turned off by use of a flag. In this case the default
    value is returned.
    
    @skipline //@ code
    @until //@ endcode
    
    A on-the fly default value can be specified by putting using the
    EST_KVL::val_def function:
    
    @skipline //@ code
    @until //@ endcode

    EST_TKVL::present() returns true of the key exists.
    
    Normally, direct access to the list is not needed, but for
    efficiency's sake, it is sometimes useful to be able to directly
    access items. The `list` variable contains the key/value
    list, from this, EST_Litem pointers can be set to items, and
    then used in access functions:

    @skipline //@ code
    @until //@ endcode

    This can also be used to change values: the following changes the
    value of the pair pointed to by p to "Scotland".

    @skipline //@ code
    @until //@ endcode

    The name of the key can be changed similarly:
    
    @skipline //@ code
    @until //@ endcode


    
    @section EST_Option EST_Option
    
    The EST_Option class is a high level version of the EST_TKVL class with
    strings for both keys and values. It is often used for lists of
    options, especially command line arguments.

    Load in options from file. The file is in the form of one key
    value pair per line. The key ends at the end of the first
    whitespace delimited token, which allows the values to have
    spaces. Eg.

        Country  Scotland
        Street South Bridge
        Number 80
        Height 23.45

    Load in file:
    @skipline //@ code
    @until //@ endcode

    All the normal EST_KVL accessing and addition functions
    work. Although the type of the value is a String, functions are
    provided to allow easy casting to ints and floats.

    @skipline //@ code
    @until //@ endcode
    
    Print out number as an integer:
    
    @skipline //@ code
    @until //@ endcode
    
    Print out height as a float:
    @skipline //@ code
    @until //@ endcode

    Often, one wishes to override an existing value if a new value
    has been set. The override_val function is useful for this. In
    the following example, the command line argument is held in the
    `al` object. A default value is put in the length field. If
    the command line option is present, it overrides "length",
    otherwise "length" is left unchanged:

    @skipline //@ code
    @until //@ endcode
    
    This is quicker than the alternative:

    @skipline //@ code
    @until //@ endcode
    
  */

