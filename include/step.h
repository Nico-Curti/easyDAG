#ifndef __step_h__
#define __step_h__

#include <iostream>
#include <utility>
#include <functional>
#include <tuple>

#include <math.hpp>

namespace details
{

template < class, template < class ... > class, class ... >
struct is_instance : public std :: false_type {};

template < class T, template < class ... > class U, class ... V >
struct is_instance < U < T, V ... >, U > : public std :: true_type {};

}


template < typename lambda, typename ... types >
class Step
{
  // Private members
  lambda func;

  std :: tuple < types ... > args;

  template < std :: size_t Idx >
  constexpr auto eval_impl () noexcept;

public:

  using lambda_func = lambda;

  // Constructor

  Step (lambda func, types & ... args);

  // setter function

  constexpr void set (types & ... args) noexcept;

  // eval method

  constexpr auto operator () () noexcept;

  // getter function

  template < std :: size_t Idx >
  static constexpr auto num_variables_impl () noexcept;

  template < std :: size_t Idx >
  static constexpr auto num_operations_impl () noexcept;

  constexpr auto arguments () noexcept;
  static constexpr auto num_variables () noexcept;
  static constexpr auto num_operations () noexcept;
  static constexpr auto size () noexcept;
  constexpr auto eval () noexcept;

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

//  using return_t = typename std :: result_of < decltype(&Step < lambda, types ... > :: eval)(Step < lambda, types ... >) > :: type;
//
//  return_t _eval;

};

template < std :: size_t I = 0, char symbol, typename ... Tp >
void print ( std :: tuple < Tp ... > & t);

template < typename type >
constexpr Step < decltype(math :: Input), type > InputVariable (type & var) noexcept;

template < typename type >
constexpr Step < decltype(math :: Input), type > InputVariable () noexcept;


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


namespace utils
{
  template < int N, typename ... Ts > using NthTypeOf = typename std :: tuple_element < N, std :: tuple < Ts ... > > :: type;

  template < class U >
  constexpr bool is_step () noexcept;

  template < class U >
  constexpr bool is_variable () noexcept;

  template < typename lambda, typename ... types >
  struct OperationCount {};

  template < typename lambda, typename ... types >
  struct OperationCount < Step < lambda, types ... > >
  {
    static constexpr int num_nodes = Step < lambda, types ... > :: size();
    static constexpr int num_operations = Step < lambda, types ... > :: num_operations();
    static constexpr int num_variables = Step < lambda, types ... > :: num_variables();
    // static constexpr int num_cached = 0;
  };

}

#endif // __step_h__
