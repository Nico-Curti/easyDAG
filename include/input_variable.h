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

  constexpr type operator () () noexcept;

  // math operators

  template < typename type2 >
  constexpr auto operator + (InputVariable < type2 > x) noexcept;
  template < typename type2 >
  constexpr auto operator - (InputVariable < type2 > x) noexcept;
  template < typename type2 >
  constexpr auto operator / (InputVariable < type2 > x) noexcept;
  template < typename type2 >
  constexpr auto operator * (InputVariable < type2 > x) noexcept;

  template < typename lambda, typename ... types >
  constexpr auto operator + (Step < lambda, types ... > x) noexcept;
  template < typename lambda, typename ... types >
  constexpr auto operator - (Step < lambda, types ... > x) noexcept;
  template < typename lambda, typename ... types >
  constexpr auto operator / (Step < lambda, types ... > x) noexcept;
  template < typename lambda, typename ... types >
  constexpr auto operator * (Step < lambda, types ... > x) noexcept;

  // logical operators

  template < typename type2 >
  constexpr auto operator == (InputVariable < type2 > x) noexcept;
  template < typename type2 >
  constexpr auto operator != (InputVariable < type2 > x) noexcept;
  template < typename type2 >
  constexpr auto operator >  (InputVariable < type2 > x) noexcept;
  template < typename type2 >
  constexpr auto operator <  (InputVariable < type2 > x) noexcept;

  template < typename lambda, typename ... types >
  constexpr auto operator == (Step < lambda, types ... > x) noexcept;
  template < typename lambda, typename ... types >
  constexpr auto operator != (Step < lambda, types ... > x) noexcept;
  template < typename lambda, typename ... types >
  constexpr auto operator >  (Step < lambda, types ... > x) noexcept;
  template < typename lambda, typename ... types >
  constexpr auto operator <  (Step < lambda, types ... > x) noexcept;

  // IO operator

  template < typename _type >
  friend std :: ostream & operator << (std :: ostream & os, const InputVariable < _type > & x);
};

#endif // __inputvar_h__
