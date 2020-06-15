#ifndef __step_h__
#define __step_h__

#include <iostream>
#include <utility>
#include <functional>
#include <tuple>
#include <future>

#include <math.hpp>


template < typename lambda, typename ... types >
class Step
{
  // Private members

  lambda func;

  std :: tuple < types ... > args;

  template < class type >
  static constexpr auto eval_impl (type & arg) noexcept;

  static constexpr auto packing (types & ... arg) noexcept;

  constexpr decltype(auto) eval () noexcept;

  constexpr decltype(auto) evaluate () noexcept; // "alias" of operator ()

public:

  using lambda_func = lambda;

  // Constructor

  Step (lambda & func, types & ... args);

  // setter function

  constexpr void set (types & ... args) noexcept;

  // eval method

  constexpr decltype(auto) operator () () noexcept;

  // getter function

  template < std :: size_t idx >
  static constexpr auto num_variables_impl () noexcept;

  template < std :: size_t idx >
  static constexpr auto num_operations_impl () noexcept;

  constexpr auto arguments () noexcept;
  static constexpr auto num_variables () noexcept;
  static constexpr auto num_operations () noexcept;
  static constexpr auto size () noexcept;

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
  friend std :: ostream & operator << (std :: ostream & os, const Step < _lambda, _types ... > & x);

private:

  // other Private members

  using eval_t = typename std :: result_of < decltype(& Step < lambda, types ... > :: evaluate)( Step < lambda, types ... > ) > :: type;

  // with a shared_future the value is automatically cached
  std :: shared_future < eval_t > value;

};


template < typename type >
constexpr Step < decltype(math :: Input), type > InputVariable (type & var) noexcept;

template < typename type >
constexpr Step < decltype(math :: Input), type > InputVariable () noexcept;


#endif // __step_h__
