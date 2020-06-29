#ifndef __step_h__
#define __step_h__

#include <tuple>
#include <string>
#include <utility>
#include <iostream>
#include <functional>
#include <type_traits>

// forward declaration
template < typename lambda, typename ... types >
class Step;

#include <math.hpp>
#include <utils.h>

template < typename lambda, typename ... types >
class Step
{

  // Protected members

protected:

  lambda func;

  std :: tuple < types ... > args;

  std :: string _name;

  // Private members
  
private:

  template < class type >
  static constexpr auto eval_impl (type & arg) noexcept;

  static constexpr auto packing (types & ... arg) noexcept;

  constexpr decltype(auto) eval () noexcept; // "alias" of operator ()

  template < std :: size_t idx = 0 >
  constexpr void dump_impl (std :: ostream & os) noexcept;

public:

  using lambda_func = lambda;

  // Constructor

  Step (lambda & func, types & ... args);

  // setter function

  constexpr void set (types & ... args) noexcept;

  #define set_name(var) name(#var)

  constexpr void name (const std :: string & n) noexcept;

  // eval method

  constexpr decltype(auto) operator () () noexcept;

  // getter function

  constexpr auto arguments () noexcept;

  std :: string get_name ();

  // math operators

  template < typename type2 >
  constexpr auto operator + (type2 x) noexcept;
  template < typename type2 >
  constexpr auto operator - (type2 x) noexcept;
  template < typename type2 >
  constexpr auto operator / (type2 x) noexcept;
  template < typename type2 >
  constexpr auto operator * (type2 x) noexcept;

  // logical operators

  template < typename type2 >
  constexpr auto operator == (type2 x) noexcept;
  template < typename type2 >
  constexpr auto operator != (type2 x) noexcept;
  template < typename type2 >
  constexpr auto operator >  (type2 x) noexcept;
  template < typename type2 >
  constexpr auto operator <  (type2 x) noexcept;

  // IO operator

  template < typename _lambda, typename ... _types >
  friend std :: ostream & operator << (std :: ostream & os, Step < _lambda, _types ... > x);

  constexpr void dump (std :: ostream & os) noexcept;
  constexpr void graphviz (std :: ostream & os, const std :: string & graph_name) noexcept;

};


// This is the CTAD workaround for std <= 14
template < typename lambda, typename ... types >
constexpr Step < lambda, types ... > make_step (lambda & func, types & ... args) noexcept;

template < typename type >
constexpr Step < decltype(math :: Input), type > InputVariable (type & var) noexcept;

template < typename type >
constexpr Step < decltype(math :: Input), type > InputVariable () noexcept;


#endif // __step_h__
