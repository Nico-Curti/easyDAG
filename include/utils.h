#ifndef __utils_h__
#define __utils_h__

#include <step.h>

namespace utils
{

  template < int N, typename ... types > using nth_type_of = typename std :: tuple_element < N, std :: tuple < types ... > > :: type;

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

#endif // __utils_h__
