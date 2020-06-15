#ifndef __utils_hpp__
#define __utils_hpp__

#include <utils.h>

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

#endif // __utils_hpp__
