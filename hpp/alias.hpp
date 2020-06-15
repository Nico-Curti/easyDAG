#ifndef __aliases_hpp__
#define __aliases_hpp__

#include <alias.h>
#include <math.hpp>

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

#endif // __aliases_hpp__
