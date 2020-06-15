#ifndef __aliases_h__
#define __aliases_h__

#include <step.h>

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

#endif // __aliases_h__
