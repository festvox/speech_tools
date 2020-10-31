/*************************************************************************/
/*                                                                       */
/*                Centre for Speech Technology Research                  */
/*                     University of Edinburgh, UK                       */
/*                         Copyright (c) 1998                            */
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
/*                       Author :  Alan W Black                          */
/*                       Date   :  February 1998                         */
/* --------------------------------------------------------------------- */
/*                                                                       */
/*  General class for representing linguistic information within a       */
/*  EST_Relation.  This consists of two parts, the relation specific     */
/*  part and the information content part.  The information content      */
/*  part may be shared between multiple EST_Items.                       */
/*                                                                       */
/*  This is typically used to represent things like words, phones but    */
/*  more abstract entities like NPs and nodes in metrical trees.         */
/*                                                                       */
/*************************************************************************/
#ifndef __EST_ITEM_H__
#define __EST_ITEM_H__

#include "EST_String.h"
#include "EST_Features.h"
#include "ling_class/EST_Item_Content.h"

typedef EST_Val (*EST_Item_featfunc)(EST_Item *s);
extern val_type val_type_featfunc;
EST_Item_featfunc featfunc(const EST_Val &v);
EST_Val est_val(const EST_Item_featfunc f);

class EST_Relation;
class ling_class_init;


/** @class EST_Item
    @ingroup estlingclasses

A class for containing individual linguistic objects such as
words or phones.

These contain two types of information. This first is specific to the
\ref EST_Relation we are viewing this ling item from, the second part
consists of a set of features.  These features may be shared by
instances of this ling item in different EST_Relation
within the same EST_Utterance.

The shared part of an EST_Item is
represented by the class EST_Item_Content.  It should not normally be
accessed by the general users as reverse links from the contents to
each of the EST_Items it is part of are held ensure the
integrity of the structures.  Changing these without maintain the
appropriate links is unlikely to be stable.

We believe this structure is the most efficient for the most natural
use we envisage.  Traversal of the items ....

*/
class EST_Item 
{
  private:
    EST_Item_Content *p_contents;
    EST_Relation *p_relation;
    // In general (when we need it)
    // EST_TKVL <EST_String, EST_Item *> arcs;
    // but specifically
    EST_Item *n;
    EST_Item *p;
    EST_Item *u;
    EST_Item *d;

    void unref_contents();
    void ref_contents();
    void copy(const EST_Item &s);

    // Internal manipulation functions 
    // Get the daughters of node, removing reference to them
    EST_Item *grab_daughters(void);
    /* Get the contents, removing reference to them, this doesn't
        delete the contents if this item is the only reference */
    EST_Item_Content *grab_contents(void);

protected:
  static void class_init(void);

  public:
    /**@name Constructor Functions */
    ///@{
    /// Default constructor
    EST_Item();
    /// Copy constructor only makes reference to contents 
    EST_Item(const EST_Item &item);
    /// Includes reference to relation 
    EST_Item(EST_Relation *rel);
    /// Most common form of construction
    EST_Item(EST_Relation *rel, EST_Item *si);
    /// Deletes it and references to it in its contents
    ~EST_Item();
    ///@}


    /**@name Feature access functions. 
       These functions are wrap-around functions to the basic access
       functions in the \ref EST_Features  class.  In all these
       functions, if the optional argument `m` is set to 1, an
       error is thrown if the feature does not exist*/

    ///@{
    /** return the value of the feature `name` 
	cast as a float */
    float F(const EST_String &name) const {return f(name).Float();}

    /** return the value of the feature `name` cast 
	as a float, returning `def` if not found.*/
    float F(const EST_String &name,float def) const 
	{return f(name,def).Float();}

    /** return the value of the feature `name` 
	cast as a EST_String */
    const EST_String S(const EST_String &name) const {return f(name).string();}

    /** return the value of the feature `name` 
	cast as a EST_String,
	returning `def` if not found.
    */
    const EST_String S(const EST_String &name, const EST_String &def) const
       {return f(name, def).string();}

    /** return the value of the feature `name` 
	cast as a int */
    int I(const EST_String &name) const {return f(name).Int();}

    /** return the value of the feature `name` cast as a int 
	returning `def` if not found.*/
    int I(const EST_String &name, int def) const
       {return f(name, def).Int();}

    /** return the value of the feature `name` 
	cast as a EST_Features */
    EST_Features &A(const EST_String &name) const {return *feats(f(name));}

    /** return the value of the feature `name` 
	cast as a EST_Features,
	returning `def` if not found.
    */
    EST_Features &A(const EST_String &name,EST_Features &def) const
       {EST_Features *ff = new EST_Features(def);
        return *feats(f(name, est_val(ff)));}
    ///@}

    /**@name Feature setting functions.
       A separate function is provided for each permissible value type
    */
    ///@{
    /** set feature `name` to `val` */
    void set(const EST_String &name, int ival)
         { EST_Val pv(ival);features().set_path(name, pv); }

    /** set feature `name` to `val` */
    void set(const EST_String &name, float fval)
         { EST_Val pv(fval); features().set_path(name,pv); }

    /** set feature `name` to `val` */
    void set(const EST_String &name, double fval)
         { EST_Val pv((float)fval);features().set_path(name,pv); }

    /** set feature `name` to `val` */
    void set(const EST_String &name, const EST_String &sval)
         { EST_Val pv(sval);features().set_path(name,pv); }

    /** set feature `name` to `val` */
    void set(const EST_String &name, const char *cval)
         { EST_Val pv(cval);features().set_path(name,pv); }

    /** set feature `name` to `val`, 
	a function registered in
        the feature function list. */
    void set_function(const EST_String &name, const EST_String &funcname)
 	 { features().set_function(name,funcname); }

    /** set feature `name` to `f`, 
	a set of features, which is copied into the object.
    */
    void set(const EST_String &name, EST_Features &f)
         { EST_Features *ff = new EST_Features(f);
	   features().set_path(name, est_val(ff)); }

    /** set feature `name` to `f`, 
	whose type is EST_Val.
    */
    void set_val(const EST_String &name, const EST_Val &sval)
         { features().set_path(name,sval); }
    ///@}

    /**@name Utility feature functions
    */
    ///@{
    /** remove feature `name` */
    void f_remove(const EST_String &name)
    { features().remove(name); }
    
    /** find all the attributes whose values are functions, and
        replace them with their evaluation. */
    void evaluate_features();

    /** true if feature is present, false otherwise */
    int f_present(const EST_String &name) const
    {
        if (p_contents)
            return features().present(name);
        else
            return false; }

    // Number of items (including this) until no next item.
    int length() const;
    ///@}

    // get contents from item
    EST_Item_Content *contents() const { return p_contents;}
    // used by tree manipulation functions
    void set_contents(EST_Item_Content *li);

    // These should be deleted.
    // The item's name 
    const EST_String name() const
    { return f("name",0).string(); }

    // Set item's name
    void set_name(const EST_String &name) const
    { p_contents->set_name(name); }

    // Shouldn't normally be needed, except for iteration
    EST_Features &features() const { return p_contents->f; }

    const EST_Val f(const EST_String &name) const
    { 
	EST_Val v;
        for (v=p_contents->f.val_path(name);
             v.type() == val_type_featfunc && featfunc(v) != NULL;
             v=(featfunc(v))((EST_Item *)(void *)this));
        if (v.type() == val_type_featfunc)
            EST_error("NULL %s function",(const char *)name);
	return v;
    }

#if 0
    const EST_Val &f(const EST_String &name, const EST_Val &def) const
    { 
	if (this == 0) 
	    return def;
        else
        {
	    const EST_Val *v; 
	    for (v=&(p_contents->f.val_path(name, def));
		 v->type() == val_type_featfunc && featfunc(*v) != NULL;
		 v=&(featfunc(*v))((EST_Item *)(void *)this));
	    if (v->type() == val_type_featfunc)
		v = &def;
	    return *v;
	}
    }
#endif

    const EST_Val f(const EST_String &name, const EST_Val &def) const
    { 
        EST_Val v; 
        for (v=p_contents->f.val_path(name, def);
             v.type() == val_type_featfunc && featfunc(v) != NULL;
             v=(featfunc(v))((EST_Item *)(void *)this));
        if (v.type() == val_type_featfunc)
            v = def;
        return v;
    }

    /**@name Cross relational access */
    ///@{

    /// View item from another relation (const char *) method
    EST_Item *as_relation(const char *relname) const
    { return p_contents->Relation(relname); }

    /// true if this item is in named relation
    int in_relation(const EST_String &relname) const
    { return p_contents->in_relation(relname); }

    /// Access to the relation links
    EST_TKVL<EST_String, EST_Val> &relations() {return p_contents->relations;}

    /// The relation name of this particular item
    const EST_String &relation_name() const;

    /// The relation of this particular item
    EST_Relation *relation(void) const
       { return p_relation; }

    /// True if li is the same item ignoring its relation viewpoint
      int same_item(const EST_Item *li) const
      { return contents() && li->contents() && (contents() == li->contents()); }
    ///@}

    // The remaining functions should not be accessed, they are should be
    // regarded as private member functions

    // Splice together a broken list.

    static void splice(EST_Item *a, EST_Item *b)
	{ if(a !=NULL) a->n = b; if (b != NULL) b->p=a; }

    // Internal traversal - not recommended - use relation traversal functions
    // As these functions must be safe to NULL arguments they now (gcc6)
    // cannot refer to this, so alway require an explicit pointer to the object
    // These four are the only ones that require access to private fields
    friend EST_Item *inext(const EST_Item *i);
    friend EST_Item *iprev(const EST_Item *i);
    friend EST_Item *idown(const EST_Item *i);
    friend EST_Item *iup(const EST_Item *i);

    // Insert a new item after this, with li's contents
    EST_Item *insert_after(EST_Item *li=0);
    // Insert a new item before this, with li's contents
    EST_Item *insert_before(EST_Item *li=0);
    // Insert a new item below this, with li's contents (see tree methods)
    EST_Item *insert_below(EST_Item *li=0);
    // Insert a new item above this, with li's contents (see tree methods)
    EST_Item *insert_above(EST_Item *li=0);

    // Append a new daughter to this, with li's contents
    EST_Item *append_daughter(EST_Item *li=0);
    // Prepend a new daughter to this, with li's contents
    EST_Item *prepend_daughter(EST_Item *li=0);
    // Insert a new parent above this, with li's contents
    EST_Item *insert_parent(EST_Item *li=0);

    // Delete this item and all its occurrences in other relations
    void unref_all();

    // Verification, double links are consistent (used after reading in)
    int verify() const;
	
    friend int i_same_item(const EST_Item *l1,const EST_Item *l2);
    friend int move_item(EST_Item *from, EST_Item *to);
    friend int merge_item(EST_Item *from, EST_Item *to);
    friend int move_sub_tree(EST_Item *from, EST_Item *to);
    friend int exchange_sub_trees(EST_Item *from,EST_Item *to);

    EST_Item &operator=(const EST_Item &s);
    friend std::ostream& operator << (std::ostream &s, const EST_Item &a);
    friend bool operator !=(const EST_Item &a, const EST_Item &b)
    { return !i_same_item(&a,&b); }
    friend bool operator ==(const EST_Item &a, const EST_Item &b)
    { return i_same_item(&a,&b); }

    friend class EST_Relation;
    friend class ling_class_init;
};

inline int i_same_item(const EST_Item *l1,const EST_Item *l2)
{
  return l1->contents() && l2->contents() && 
    (l1->contents() == l2->contents()); 
}


inline EST_Item *as(const EST_Item *n,const char *relname)
{  if (n != 0) return n->as_relation(relname);
    return 0;}

EST_Item *inext(const EST_Item *i);
EST_Item *iprev(const EST_Item *i);
EST_Item *idown(const EST_Item *i);
EST_Item *iup(const EST_Item *i);

EST_Item *last(const EST_Item *x);
EST_Item *first(const EST_Item *x);
EST_Item *top(const EST_Item *x);
EST_Item *bottom(const EST_Item *x);

EST_Item *next_item(const EST_Item *node);
EST_Item *first_leaf(const EST_Item *node);
EST_Item *next_leaf(const EST_Item *node);
EST_Item *last_leaf(const EST_Item *node);

// Relation structure functions
#include "ling_class/EST_Relation_list.h"
#include "ling_class/EST_Relation_tree.h"
#include "ling_class/EST_Relation_mls.h"

void remove_item(EST_Item *l, const char *relname);

void copy_node_tree(EST_Item *from, EST_Item *to);
void copy_node_tree_contents(EST_Item *from, EST_Item *to);

void evaluate(EST_Item *a,EST_Features &f);

#include "ling_class/EST_FeatureFunctionPackage.h"

// Feature function support
void EST_register_feature_function_package(const char *name, void (*init_fn)(EST_FeatureFunctionPackage &p));

void register_featfunc(const EST_String &name, const EST_Item_featfunc func);
EST_Item_featfunc get_featfunc(const EST_String &name,int must=0);
EST_String get_featname(const EST_Item_featfunc func);

#define	EST_register_feature_functions(PACKAGE) \
  do { \
     extern void register_ ## PACKAGE ## _feature_functions(EST_FeatureFunctionPackage &p); \
     EST_register_feature_function_package( #PACKAGE , register_ ## PACKAGE ## _feature_functions); \
     } while(0)


#endif
