#ifndef __step_h__
#define __step_h__

#include <iostream>
#include <utility>
#include <functional>
#include <tuple>

#include <math.hpp>
#include <input_variable.hpp>

template < typename lambda, typename ... types >
class Step
{
  // Private members

  lambda func;

  std :: tuple < types ... > args;

  template < typename ... kwargs, std :: size_t ... Idx >
  constexpr auto _func ( std :: tuple < kwargs ... > & tup, std :: index_sequence < Idx ... >) noexcept;

  template < typename ... kwargs >
  constexpr auto _func (std :: tuple < kwargs ... > & tup) noexcept;

  template < std :: size_t ... Idx >
  constexpr auto eval_tuple_impl (std :: index_sequence < Idx ... >) noexcept;

  constexpr auto eval_tuple () noexcept;

public:

  // Constructor

  Step (lambda func, types ... args);

  // eval method

  constexpr auto operator () () noexcept;

  // math operators

  template < typename lambda2, typename ... types2 >
  constexpr auto operator + (Step < lambda2, types2 ... > x) noexcept;
  template < typename lambda2, typename ... types2 >
  constexpr auto operator - (Step < lambda2, types2 ... > x) noexcept;
  template < typename lambda2, typename ... types2 >
  constexpr auto operator / (Step < lambda2, types2 ... > x) noexcept;
  template < typename lambda2, typename ... types2 >
  constexpr auto operator * (Step < lambda2, types2 ... > x) noexcept;

  template < typename type >
  constexpr auto operator + (InputVariable < type > x) noexcept;
  template < typename type >
  constexpr auto operator - (InputVariable < type > x) noexcept;
  template < typename type >
  constexpr auto operator / (InputVariable < type > x) noexcept;
  template < typename type >
  constexpr auto operator * (InputVariable < type > x) noexcept;

  // logical operators

  template < typename lambda2, typename ... types2 >
  constexpr auto operator == (Step < lambda2, types2 ... > x) noexcept;
  template < typename lambda2, typename ... types2 >
  constexpr auto operator != (Step < lambda2, types2 ... > x) noexcept;
  template < typename lambda2, typename ... types2 >
  constexpr auto operator >  (Step < lambda2, types2 ... > x) noexcept;
  template < typename lambda2, typename ... types2 >
  constexpr auto operator <  (Step < lambda2, types2 ... > x) noexcept;

  template < typename type >
  constexpr auto operator == (InputVariable < type > x) noexcept;
  template < typename type >
  constexpr auto operator != (InputVariable < type > x) noexcept;
  template < typename type >
  constexpr auto operator >  (InputVariable < type > x) noexcept;
  template < typename type >
  constexpr auto operator <  (InputVariable < type > x) noexcept;

  // IO operator

  template < typename _lambda, typename ... _types >
  friend std :: ostream & operator << (std :: ostream & os, const Step < _lambda, _types ... > & x);

};


// aliases

namespace math
{

  template < typename ... types >
  constexpr Step < decltype(Add_lambda), types ... > Sum (types ... args) noexcept;

  template < typename ... types >
  constexpr Step < decltype(Sub_lambda), types ... > Sub (types ... args) noexcept;

  template < typename ... types >
  constexpr Step < decltype(Mul_lambda), types ... > Mul (types ... args) noexcept;

  template < typename ... types >
  constexpr Step < decltype(Div_lambda), types ... > Div (types ... args) noexcept;

  template < typename ... types >
  constexpr Step < decltype(Eq_lambda), types ... > Eq (types ... args) noexcept;

  template < typename ... types >
  constexpr Step < decltype(NEq_lambda), types ... > NEq (types ... args) noexcept;

  template < typename ... types >
  constexpr Step < decltype(Greater_lambda), types ... > Greater (types ... args) noexcept;

  template < typename ... types >
  constexpr Step < decltype(Lower_lambda), types ... > Lower (types ... args) noexcept;

} // end namespace


#endif // __step_h__
