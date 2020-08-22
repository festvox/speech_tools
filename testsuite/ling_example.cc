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

#include "EST_unix.h"
#include "EST_ling_class.h"

using namespace std;


int main(void)
{
  
  /*Adding basic information to an EST_Item */

  //@ code
  EST_Item p;
  
  p.set("POS", "Noun");
  p.set("NAME", "example");
  p.set("FOCUS", "+");
  p.set("DURATION", 2.76);
  p.set("STRESS", 2);

  //@ endcode

  /* Accessing basic information in an Item */

  //@ code
  cout << "Part of speech for p is " << p.S("POS") << endl;
  cout << "Duration for p is " << p.F("DURATION") << endl;
  cout << "Stress value for p is " << p.I("STRESS") << endl;
  //@ endcode

  /* A optional default value can be given if a result 
   * is always desired */

  //@ code
  cout << "Part of speech for p is " 
      << p.S("POS") << endl;
  cout << "Syntactic Category for p is " 
      << p.S("CAT", "Noun") << endl; // noerror
  //@ endcode

  /* Nested feature structures in items */

  //@ code
  
  p.set("NAME", "d");
  p.set("VOICE", "+");
  p.set("CONTINUANT", "-");
  p.set("SONORANT", "-");

  EST_Features f;  
  p.set("PLACE OF ARTICULATION", f); // copy in empty feature set here
  
  p.A("PLACE OF ARTICULATION").set("CORONAL", "+");
  p.A("PLACE OF ARTICULATION").set("ANTERIOR", "+");
  //@ endcode

  /* or by filling the values in an EST_Features object and
    * copying it in:
    */

  //@ code
  EST_Features f2;
  
  f2.set("CORONAL", "+");
  f2.set("ANTERIOR", "+");
  
  p.set("PLACE OF ARTICULATION", f2);
  //@ endcode
	

  /* Nested features can be accessed by multiple calls to the
   * accessing commands:
   */
  
  //@ code
  cout << "Anterior value is: " << p.A("PLACE OF ARTICULATION").S("ANTERIOR");
  cout << "Coronal value is: " << p.A("PLACE OF ARTICULATION").S("CORONAL");
  //@ endcode

  //@ code
  cout << "Anterior value is: " << p.S("PLACE OF ARTICULATION.ANTERIOR");
  cout << "Coronal value is: " << p.S("PLACE OF ARTICULATION.CORONAL");
  //@ endcode
	  

  //@ code
  
  p.set("PLACE OF ARTICULATION.CORONAL", "+");
  p.set("PLACE OF ARTICULATION.ANTERIOR", "+");
  //@ endcode

  /* this is the easiest and most commonly used method. */


  /* Utility functions for items */

  //@ code
  cout << "This is true: " << p.f_present("PLACE OF ARTICULATION");
  cout << "This is false: " << p.f_present("MANNER");
  //@ endcode

  /* An attribute can be removed by <function>f_remove</function> */

  //@ code
  p.f_remove("PLACE OF ARTICULATION");
  //@ endcode

	  
  /* Building a linear list relation    */

  //@ code
  EST_Relation phones;
  EST_Item *a;
  
  a = phones.append();
  
  a->set("NAME", "f");
  a->set("TYPE", "consonant");
  
  a = phones.append();
  
  a->set("NAME", "o");
  a->set("TYPE", "vowel");
  
  a = phones.append();
  
  a->set("NAME", "r");
  a->set("TYPE", "consonant");
  //@ endcode
  
	
  //@ code
  a = new EST_Item;
  a->set("NAME", "m");
  a->set("TYPE", "consonant");
  
  phones.append(a);
  
  a = new EST_Item;
  a->set("NAME", "ei");
  a->set("TYPE", "vowel");
  //@ endcode
	
  /* Items can be prepended in exactly the same way: */
  //@ code

  a = phones.prepend();
  
  a->set("NAME", "n");
  a->set("TYPE", "consonant");
  
  a = phones.prepend();
  
  a->set("NAME", "i");
  a->set("TYPE", "vowel");
	
  //@ endcode


  /* Iterating through a linear list relation */

  //@ code
  EST_Item *s;

  for (s = phones.head(); s != 0; s = inext(s))
    cout << s->S("NAME") << endl;
  //@ endcode

  //@ code

  for (s = phones.tail(); s != 0; s = iprev(s))
    cout << s->S("NAME") << endl;

  //@ endcode

  //@ code
  for (s = phones.head(); s; s = inext(s))
    cout << s->S("NAME") << endl;
  //@ endcode
  

  /* Building a tree relation */
  //@{
	
  //@ code
  //@example prog01
  EST_Relation tree;
  EST_Item *r, *np, *vp, *n;
  
  r = tree.append();
  r->set("CAT", "S");
  
  np = append_daughter(r);
  np->set("CAT", "NP");
  
  n =  append_daughter(np);
  n->set("CAT", "PRO");
  
  n =  append_daughter(n);
  n->set("NAME", "John");
  
  vp = append_daughter(r);
  vp->set("CAT", "VP");
  
  n = append_daughter(vp);
  n->set("CAT", "VERB");
  n = append_daughter(n);
  n->set("NAME", "loves");
  
  np = append_daughter(vp);
  np->set("CAT", "NP");
  
  n = append_daughter(np);
  n->set("CAT", "DET");
  n = append_daughter(n);
  n->set("NAME", "the");
  
  n = append_daughter(np);
  n->set("CAT", "NOUN");
  n = append_daughter(n);
  n->set("NAME", "woman");
  
  cout << tree;
  //@ endcode


  /* Iterating through a tree relation */

  //@ code
  n = tree.head();             // initialise iteration variable to head of tree 
  while (n)
    {
      if (daughter1(n) != 0) // if daughter exists, make n its daughter 
        n = daughter1(n);
      else if (inext(n) != 0)//otherwise visit its sisters 
        n = inext(n);
      else                    // if no sisters are left, go back up the tree 
	{                       // until a sister to a parent is found 
	  bool found=FALSE;
	  for (EST_Item *pp = parent(n); pp != 0; pp = parent(pp))
	    if (inext(pp))
	      {
		n = inext(pp);
		found=TRUE;
		break;
	      }
	  if (!found)
	    {
	      n = 0;
	      break;
	    }
	}
      cout << *n;
    }
  //@ endcode

  /* A special set of iterators are available for traversal of the leaf
    * (terminal) nodes of a tree:
    */

  //@ code
  //@ example prog02
  //@ title Leaf iteration

  for (s = first_leaf(tree.head()); s != last_leaf(tree.head()); 
       s = next_leaf(s))
    cout << s->S("NAME") << endl;
  //@ endcode


  /* Building a multi-linear relation */

  /* Iterating through a multi-linear relation */

/* Relations in Utterances */

  //@ code
  EST_Utterance utt;
  
  utt.create_relation("Word");
  utt.create_relation("Syntax");
  //@ endcode

  /* EST_Relations can be accessed though the utterance object either
    * directly or by use of a temporary EST_Relation pointer:
    */

  //@ code
  EST_Relation *word, *syntax;
  
  word = utt.relation("Word");
  syntax = utt.relation("Syntax");
  //@ endcode

  /* The contents of the relation can be filled by the methods described
    * above. 
    */


  /* Adding items into multiple relations */

  //@ code
  //@example prog03
  //@title adding existing items to a new relation
  word = utt.relation("Word");
  syntax = utt.relation("Syntax");
  
  for (s = first_leaf(syntax->head()); s != last_leaf(syntax->head()); 
       s = next_leaf(s))
    word->append(s);
  
  //@ endcode

  /* 
    * Thus the terminal nodes in the syntax relation are now stored as a
    * linear list in the word relation.
    * 
    * Hence
    */

  //@ code
  cout << *utt.relation("Syntax") << "\n";
  //@ endcode

  //@ code
  cout << *utt.relation("Word") << "\n";
  //@ endcode


  /*Changing the relation an item is in as_relation, in relation etc */

  /* Feature functions evaluate functions setting functions */

  exit(0);

}


/** @page ling-example Example code for Linguistic Classes
    @tableofcontents
    @brief Some examples of usage of linguistic classes
    @dontinclude ling_example.cc
    
    @section addingtoestitem Adding basic information to an EST_Item

  An item such as:

\f[
\left [ 
\begin{array}{ll}
\mbox{POS} & \mbox{\emph{Noun}} \\
\mbox{NAME} & \mbox{\emph{example}} \\
\mbox{FOCUS} & \mbox{+} \\ 
\end{array}  \right ]
\f]

  is constructed as follows: (note that
  the attributes are in capitals by linguistic convention only:
  attribute names are case sensitive and can be upper or lower case).

  @skipline //@ code
  @until //@ endcode

  The type of the values in features is a EST_Val class,
  which is a union which can
  store ints, floats, EST_Strings, void pointers, and
  EST_Features. The overloaded function
  facility of C++ means that the EST_Item::set() can be
  used for all of these. 
  

  @section accessingitem Accessing basic information in an Item
   
  When accessing the features, the type must be
  specified. This is done most easily by using of a series of
  functions whose type is coded by a capital letter:

  - EST_Item::F() : return value as a float.
  - EST_Item::I() : return value as an integer.
  - EST_Item::S() : return value as a string.
  - EST_Item::A() : return value as a EST_Features

  @skipline //@ code
  @until //@ endcode
  
  @verbatim
  Output:
    "Noun"
    2.75
    1
  @endverbatim
  
   A optional default value can be given if a result is always desired

  @skipline //@ code
  @until //@ endcode

  @section nestedfeatures Nested feature structures in items
  
  Nested feature structures such as 

\f[
\left [ 
\begin{array}{ll}
\mbox{NAME} & \mbox{\emph{d}} \\
\mbox{PLACE OF ARTICULATION \boxed{1} } & 
     \left [ \begin{array}{ll} 
                  \mbox{CORONAL} & \mbox{\emph{+}} \\
                  \mbox{ANTERIOR} & \mbox{\emph{+}} \\
             \end{array} \right ] \\
\mbox{VOICE} & \mbox{\emph{+}} \\ 
\mbox{CONTINUANT} & \mbox{\emph{--}} \\
\mbox{SONORANT} & \mbox{\emph{--}} \\ 
\end{array}  \right ]
\f]

    can be created in a number of ways:

  @skipline //@ code
  @until //@ endcode

  or by filling the values in an EST_Features object and
  copying it in:

  @skipline //@ code
  @until //@ endcode
	

  Nested features can be accessed by multiple calls to the
  accessing commands:

  @skipline //@ code
  @until //@ endcode

  The first command is EST_Item::A() because PLACE is a
  feature structure, and the second command is
  EST_Item::S() because it returns a string (the
  value or ANTERIOR or CORONAL). A shorthand is provided to
  extract the value in a single statement:

  @skipline //@ code
  @until //@ endcode
	  
  Again, as the last value to be returned is a string
  EST_Item::S() must be used. This shorthand can also be used
  to set the features:

  @skipline //@ code
  @until //@ endcode

  this is the easiest and most commonly used method.

  @section utilityfunctions Utility functions for items

  The presence of a attribute can be checked using
  EST_Item::f_present(), which returns true if the
  attribute is in the item:

  @skipline //@ code
  @until //@ endcode

  An attribute can be removed by EST_Item::f_remove.

  @skipline //@ code
  @until //@ endcode

  @section buildlinearlist Building a linear list relation
  <!--  *** UPDATE *** -->      
  
  It is standard to store the phones for an utterance as a linear list
  in a EST_Relation object. Each phone is represented by one
  EST_Item, whereas the complete list is stored as a
  EST_Relation.

  The easiest way to build a linear list is by using the
  EST_Relation::append(), which when called
  without arguments, makes a new empty EST_Item, adds it onto
  the end of the relation and returns a pointer to it. The
  information relevant to that phone can then be added to the
  returned item.

  @skipline //@ code
  @until //@ endcode
  
  Note that the -> operator is used because the EST_Item a is a
  pointer here. The same pointer variable can be used multiple
  times because every time EST_Relation::append() is
  called it allocates a new item and returns a pointer to it.

  If you already have a EST_Item pointer and want to add it to a
  relation, you can give it as an argument to
  EST_Relation::append(), but this is generally
  inadvisable as it involves some unnecessary copying, and also
  you have to allocate the memory for the next EST_Item pointer
  yourself every time (if you don't you will overwrite the
  previous one):
  
	
  @skipline //@ code
  @until //@ endcode
	
  Items can be prepended in exactly the same way:

  @skipline //@ code
  @until //@ endcode

  @section iteratingrelation Iterating through a linear list relation

  Iteration in lists is performed with EST_Relation::next()
  and EST_Relation::prev(), and an EST_Item,
  used as an iteration pointer.
  
  @skipline //@ code
  @until //@ endcode

  Output:
  @verbatim
  name:i    type:vowel
  name:n    type:consonant
  name:f    type:consonant
  name:o    type:vowel
  name:r    type:consonant
  name:m    type:consonant
  @endverbatim

  @skipline //@ code
  @until //@ endcode

  Output:

  @verbatim
  name:m    type:consonant
  name:r    type:consonant
  name:o    type:vowel
  name:f    type:consonant
  name:n    type:consonant
  name:i    type:vowel
  @endverbatim
	
  EST_Relation::head() and EST_Relation::tail() return EST_Item 
  pointers to the start and end of the list. EST_Relation::next()
  and EST_Relation::prev() returns the next or previous item in the 
  list, and returns `0` when the end or start of the list is
  reached. Hence checking for `0` is a useful termination condition
  of the iteration. Taking advantage of C shorthand allows us to write:

  @skipline //@ code
  @until //@ endcode

  @section buildtreerelation Building a tree relation
  
  <!--  *** UPDATE *** -->
  It is standard to store information such as syntax as a tree
  in a EST_Relation object. Each tree node is represented by one
  EST_Item, whereas the complete tree is stored as a
  EST_Relation.

  The easiest way to build a tree is by using the
  EST_Relation::append_daughter(), which when called
  without arguments, makes a new empty EST_Item, adds it as a
  daughter to an existing item and returns a pointer to it. The
  information relevant to that node can then be added to the
  returned item. The root node of the tree must be added
  directly to the EST_Relation.
  
  @anchor ling-example-example01
  @skipline //@ code
  @until //@ endcode
  
  Output:
  
  @verbatim
(S 
   (NP 
      (N (John))
   )
   (VP 
      (V (loves)) 
      (NP 
         (DET the) 
         (NOUN woman))
   )
)
  @endverbatim


  Obviously, the use of recursive functions in building trees is more
  efficient and would eliminate the need for the large number of
  temporary variables used in the above example.
  
  @section iteratingtreerelation Iterating through a tree relation
  
  Iteration in trees is done with EST_Relation::daughter1()
  EST_Relation::daughter2() EST_Relation::daughtern() and
  EST_Relation::parent(). Pre-order traversal can be achieved
  iteratively as follows:

  @skipline //@ code
  @until //@ endcode

  A special set of iterators are available for traversal of the leaf
  (terminal) nodes of a tree:

  @skipline //@ code
  @until //@ endcode

  @section buildmultilinear Building a multi-linear relation
  This is not yet fully implemented?

  @section iteratingmultilinear Iterating through a multi-linear relation
  This is not yet fully implemented?

  @section relationsinutt Relations in Utterances
  
  The EST_Utterance class is used to store all
  the items and relations relevant to a single utterance. (Here
  utterance is used as a general linguistic entity - it doesn't have to
  relate to a well formed complete linguistic unit such as a sentence or
  phrase). 

  Instead of storing relations separately, they are stored in
  utterances:
  
  @skipline //@ code
  @until //@ endcode

  EST_Relations can be accessed though the utterance object either
  directly or by use of a temporary EST_Relation pointer:

  @skipline //@ code
  @until //@ endcode

  The contents of the relation can be filled by the methods described
  above. 


  @section additemsmultiplerelations Adding items into multiple relations
  
  A major aspect of this system is that an item can be in two relations
  at once, as shown in \ref estling-figure-6-2 "Figure 6-2".

  In the following example, using the syntax relation as already created
  in \ref ling-example-example01 "prog01",
  shows how to put the terminal nodes of this
  tree into a word relation:

  @skipline //@ code
  @until //@ endcode
  
  Thus the terminal nodes in the syntax relation are now stored as a
  linear list in the word relation.
  
  Hence

  @skipline //@ code
  @until //@ endcode

  produces
  
  Output:
  @verbatim
(S 
   (NP 
      (N (John))
   )
   (VP 
      (V (loves)) 
      (NP 
         (DET the) 
         (NOUN woman))
   )
)
  @endverbatim

  whereas

  @skipline //@ code
  @until //@ endcode

  produces
  
  Output
  @verbatim
John
loves
the
woman
  @endverbatim

  @section changingrelationwithitem Changing the relation an item is in

  Even if an item is in more than one relation, it always has the 
  idea of a "current" relation. If the traversal functions 
  (next, previous, parent etc) are called, traversal always occurs 
  with respect to the current relation. An item's current relation 
  can be changed as follows: 

  \code{.cpp}
s = utt.relation("Word")->head(); // set p to first word
s = next(s); // get next word: s = parent(s) would throw an error as there 
             // is no parent to s in the word relation.
s = prev(s); // get previous word 
s = s->as_relation("Syntax"); // change relation.
s = parent(s); // get parent of s in syntax relation
s = daughter1(s); // get first daughter of s: s = next(s) would throw an 
                  // error as there is no next to s in the syntax relation. 
  \endcode

  while s is still the same item, the current relation is now "Syntax".
  The current relation is returned by the EST_Item::relation() function:
  \code{.cpp}
    cout << "Name of current relation: " << s->relation()->name() << endl;
  \endcode
  
  If you aren't sure whether an item is in a relation, you can check 
  with EST_Item::in_relation(). This will return true if an item is in
  the requested relation regardless of what the current relation is.
  \code{.cpp}
     cout << "P is in the syntax relation: " << s->in_relation("Word") << endl;
     cout << "Relations: " << s->relations() << endl; 
  \endcode

  @section featurefunctions Feature functions
  
  evaluate functions

  setting functions

*/
