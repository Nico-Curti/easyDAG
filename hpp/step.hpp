#ifndef __step_hpp__
#define __step_hpp__

#include <step.h>
#include <math.hpp>
// #include cachedecorator

template < typename lambda, typename ... types >
Step < lambda, types ... > :: Step (lambda func, types & ... args) : func (std :: forward < lambda >(func)), args (std :: tie(args ...))//, _eval (Step < lambda, types ... > :: return_t())
{
}

template < typename lambda, typename ... types > template < std :: size_t Idx >
constexpr auto Step < lambda, types ... > :: num_variables_impl () noexcept
{
  if constexpr (Idx < sizeof ... (types))
  {
    using IdxType = utils :: NthTypeOf < Idx, types ... >;
    if constexpr (details :: is_instance < IdxType, Step > :: value)
      return IdxType :: num_variables() + num_variables_impl < Idx + 1 >();

    return num_operations_impl < Idx + 1 >() + 1;
  }
  else
    return 0;
}

template < typename lambda, typename ... types >
constexpr auto Step < lambda, types ... > :: num_variables () noexcept
{
  return num_variables_impl < 0 > ();
}

template < typename lambda, typename ... types > template < std :: size_t Idx >
constexpr auto Step < lambda, types ... > :: num_operations_impl () noexcept
{
  if constexpr (Idx < sizeof ... (types))
  {
    using IdxType = utils :: NthTypeOf < Idx, types ... >;
    if constexpr (utils :: is_step < IdxType >())
      return IdxType :: num_operations() + num_operations_impl < Idx + 1 >();

    return num_operations_impl < Idx + 1 >();
  }
  else
    return 0;

}

template < typename lambda, typename ... types >
constexpr auto Step < lambda, types ... > :: num_operations () noexcept
{
  return num_operations_impl < 0 > () + 1;
}

template < typename lambda, typename ... types >
constexpr auto Step < lambda, types ... > :: size () noexcept
{
  return num_variables() + num_operations();
}

template < typename lambda, typename ... types > template < std :: size_t Idx >
constexpr auto Step < lambda, types ... > :: eval_impl () noexcept
{
  using IdxType = utils :: NthTypeOf < Idx, types ... >;
  if constexpr (details :: is_instance < IdxType, Step > :: value)
  {
    if constexpr (Idx + 1 < sizeof ... (types))
      return this->func(std :: get < Idx >(this->args).eval(), eval_impl < Idx + 1 >());
    else
      return std :: get < Idx >(this->args).eval();
  }
  else
    return std :: get < Idx >(this->args);
}

template < typename lambda, typename ... types >
constexpr auto Step < lambda, types ... > :: eval () noexcept
{
  return eval_impl < 0 >();
}

template < typename lambda, typename ... types >
constexpr auto Step < lambda, types ... > :: operator () () noexcept
{
  return this->func(eval_impl < 0 >());
}

template < typename lambda, typename ... types >
constexpr auto Step < lambda, types ... > :: arguments () noexcept
{
  return this->args;
}

template < typename lambda, typename ... types >
constexpr void Step < lambda, types ... > :: set (types & ... args) noexcept
{
  this->args = std :: tuple < types ... >(args ... );
  //if ( this->_eval != return_t() )
  //  this->_eval = this->eval ();
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator + (T x) noexcept
{
  return Step < decltype(math :: Add_lambda), Step < lambda, types ... >, T > (math :: Add_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator - (T x) noexcept
{
  return Step < decltype(math :: Sub_lambda), Step < lambda, types ... >, T > (math :: Sub_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator * (T x) noexcept
{
  return Step < decltype(math :: Mul_lambda), Step < lambda, types ... >, T > (math :: Mul_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator / (T x) noexcept
{
  return Step < decltype(math :: Div_lambda), Step < lambda, types ... >, T > (math :: Div_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator == (T x) noexcept
{
  return Step < decltype(math :: Eq_lambda), Step < lambda, types ... >, T > (math :: Eq_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator != (T x) noexcept
{
  return Step < decltype(math :: NEq_lambda), Step < lambda, types ... >, T > (math :: NEq_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator < (T x) noexcept
{
  return Step < decltype(math :: Lower_lambda), Step < lambda, types ... >, T > (math :: Lower_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator > (T x) noexcept
{
  return Step < decltype(math :: Greater_lambda), Step < lambda, types ... >, T > (math :: Greater_lambda, *this, x);
}

template < std :: size_t I, char symbol, typename ... Tp >
void print ( std :: tuple < Tp ... > & t)
{
  if constexpr (I > 0)
  {
    std :: cout << std :: get < I >(t) << " " << symbol << " ";
    print < I - 1, symbol, Tp ... >(t);
  }
  else
    std :: cout << std :: get < I >(t) << " ";
}

template < typename lambda, typename ... types >
std :: ostream & operator << (std :: ostream & os, const Step < lambda, types ... > & x)
{
  auto kwargs = x.arguments();
  os << "Step ( ";
  print < std :: tuple_size < decltype(kwargs) > :: value - 1, lambda :: symbol() > (kwargs);
  os << ")";
  return os;
}

template < typename type >
constexpr Step < decltype(math :: Input), type > InputVariable (type & var) noexcept
{
  return Step < decltype(math :: Input), type >(math :: Input, var);
}

template < typename type >
constexpr Step < decltype(math :: Input), type > InputVariable () noexcept
{
  type dummy = type();
  return Step < decltype(math :: Input), type >(math :: Input, dummy);
}

// aliases

namespace math
{

  template < typename ... types >
  constexpr Step < decltype(Add_lambda), types ... > Sum (types ... args) noexcept
  {
    return Step < decltype(Add_lambda), types ... >(Add_lambda, args ...);
  }

  template < typename ... types >
  constexpr Step < decltype(Sub_lambda), types ... > Sub (types ... args) noexcept
  {
    return Step < decltype(Sub_lambda), types ... >(Sub_lambda, args ...);
  }

  template < typename ... types >
  constexpr Step < decltype(Mul_lambda), types ... > Mul (types ... args) noexcept
  {
    return Step < decltype(Mul_lambda), types ... >(Mul_lambda, args ...);
  }

  template < typename ... types >
  constexpr Step < decltype(Div_lambda), types ... > Div (types ... args) noexcept
  {
    return Step < decltype(Div_lambda), types ... >(Div_lambda, args ...);
  }

  template < typename ... types >
  constexpr Step < decltype(Eq_lambda), types ... > Eq (types ... args) noexcept
  {
    return Step < decltype(Eq_lambda), types ... >(Eq_lambda, args ...);
  }

  template < typename ... types >
  constexpr Step < decltype(NEq_lambda), types ... > NEq (types ... args) noexcept
  {
    return Step < decltype(NEq_lambda), types ... >(NEq_lambda, args ...);
  }

  template < typename ... types >
  constexpr Step < decltype(Greater_lambda), types ... > Greater (types ... args) noexcept
  {
    return Step < decltype(Greater_lambda), types ... >(Greater_lambda, args ...);
  }

  template < typename ... types >
  constexpr Step < decltype(Lower_lambda), types ... > Lower (types ... args) noexcept
  {
    return Step < decltype(Lower_lambda), types ... >(Lower_lambda, args ...);
  }

} // end namespace


namespace utils
{

template < class U >
constexpr bool is_step () noexcept
{
  if constexpr (details :: is_instance < U, Step > :: value)
    return !std :: is_same_v < typename U :: lambda_func, decltype(math :: Input) >;

  return false;
}

template < class U >
constexpr bool is_variable () noexcept
{
  if constexpr (is_step < U >())
    return std :: is_same_v < typename U :: lambda_func, decltype(math :: Input) >;

  return true;
}

} // end namespace


#endif // __step_hpp__
