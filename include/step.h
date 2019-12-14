#ifndef __step_h__
#define __step_h__

#include <iostream>
#include <utility>
#include <functional>
#include <tuple>

#include <math.hpp>
#include <input_variable.hpp>


namespace helper
{
  template < int ... Is >
  struct index {};

  template < int N, int ... Is >
  struct gen_seq : gen_seq < N - 1, N - 1, Is ... > {};

  template < int ... Is >
  struct gen_seq < 0, Is ... > : index < Is ... > {};
}


template < typename lambda, typename ... types >
class Step
{
  // Private members

  lambda func;

  std :: tuple < types ... > args;

  template < typename ... kwargs, int ... Is >
  auto _func ( std :: tuple < kwargs ... > & tup, helper :: index < Is ... >);

  template < typename ... kwargs >
  auto _func (std :: tuple < kwargs ... > & tup);

  template < std :: size_t ... Idx >
  constexpr auto eval_tuple_impl (std :: index_sequence < Idx ... >) noexcept;

  constexpr auto eval_tuple () noexcept;

public:

  // Constructor

  Step (lambda func, types ... args);

  // eval method

  auto operator () ();

  // math operators

  template < typename lambda2, typename ... types2 >
  auto operator + (Step < lambda2, types2 ... > x);
  template < typename lambda2, typename ... types2 >
  auto operator - (Step < lambda2, types2 ... > x);
  template < typename lambda2, typename ... types2 >
  auto operator / (Step < lambda2, types2 ... > x);
  template < typename lambda2, typename ... types2 >
  auto operator * (Step < lambda2, types2 ... > x);

  template < typename type >
  auto operator + (InputVariable < type > x);
  template < typename type >
  auto operator - (InputVariable < type > x);
  template < typename type >
  auto operator / (InputVariable < type > x);
  template < typename type >
  auto operator * (InputVariable < type > x);

  // logical operators

  template < typename lambda2, typename ... types2 >
  auto operator == (Step < lambda2, types2 ... > x);
  template < typename lambda2, typename ... types2 >
  auto operator != (Step < lambda2, types2 ... > x);
  template < typename lambda2, typename ... types2 >
  auto operator >  (Step < lambda2, types2 ... > x);
  template < typename lambda2, typename ... types2 >
  auto operator <  (Step < lambda2, types2 ... > x);

  template < typename type >
  auto operator == (InputVariable < type > x);
  template < typename type >
  auto operator != (InputVariable < type > x);
  template < typename type >
  auto operator >  (InputVariable < type > x);
  template < typename type >
  auto operator <  (InputVariable < type > x);

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

} // end namespace


#endif // __step_h__
