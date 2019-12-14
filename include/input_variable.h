#ifndef __inputvar_h__
#define __inputvar_h__

#include <iostream>

// forward declaration

template < typename lambda, typename ... types >
class Step;

template < typename type >
class InputVariable
{
  // Private members

  type * var;

public:

  // Constructor

  InputVariable ();
  InputVariable (type & var);

  // Copy Constructors

  InputVariable (const InputVariable & x);

  // eval method

  void set (type & var);

  type operator () () const;

  // math operators

  template < typename type2 >
  auto operator + (InputVariable < type2 > x);
  template < typename type2 >
  auto operator - (InputVariable < type2 > x);
  template < typename type2 >
  auto operator / (InputVariable < type2 > x);
  template < typename type2 >
  auto operator * (InputVariable < type2 > x);

  template < typename lambda, typename ... types >
  auto operator + (Step < lambda, types ... > x);
  template < typename lambda, typename ... types >
  auto operator - (Step < lambda, types ... > x);
  template < typename lambda, typename ... types >
  auto operator / (Step < lambda, types ... > x);
  template < typename lambda, typename ... types >
  auto operator * (Step < lambda, types ... > x);

  // logical operators

  template < typename type2 >
  auto operator == (InputVariable < type2 > x);
  template < typename type2 >
  auto operator != (InputVariable < type2 > x);
  template < typename type2 >
  auto operator >  (InputVariable < type2 > x);
  template < typename type2 >
  auto operator <  (InputVariable < type2 > x);

  template < typename lambda, typename ... types >
  auto operator == (Step < lambda, types ... > x);
  template < typename lambda, typename ... types >
  auto operator != (Step < lambda, types ... > x);
  template < typename lambda, typename ... types >
  auto operator >  (Step < lambda, types ... > x);
  template < typename lambda, typename ... types >
  auto operator <  (Step < lambda, types ... > x);

  // IO operator

  template < typename _type >
  friend std :: ostream & operator << (std :: ostream & os, const InputVariable < _type > & x);
};

#endif // __inputvar_h__
