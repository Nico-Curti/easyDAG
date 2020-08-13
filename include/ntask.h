#ifndef __Ntask_h__
#define __Ntask_h__

#include <task.hpp>

template < std :: size_t N, typename lambda, typename ... types >
class NTask : public Step < decltype(math :: Get), typename detail :: generate_tuple_type < std :: remove_cv_t < std :: remove_reference_t < typename std :: result_of < decltype(& Task < lambda, types ... > :: operator ())( Task < lambda, types ... > ) > :: type > >, N > :: type >
{

public:

  // Public types just as utilities

  using tuple_type = typename detail :: generate_tuple_type < Task < lambda, types ... >, N > :: type;
  using res_type = typename std :: result_of < decltype(& Task < lambda, types ... > :: operator ())( Task < lambda, types ... > ) > :: type;
  using res_tuple_type = typename detail :: generate_tuple_type < std :: remove_cv_t < std :: remove_reference_t < res_type > >, N > :: type;


private:

  // Private members

  tuple_type tasks;
  res_tuple_type res;

  template < std :: size_t n >
  constexpr decltype(auto) get_impl () noexcept;

  template < std :: size_t n >
  constexpr void eval_impl () noexcept;

public:

  // Constructor

  NTask (lambda & func, types & ... args);

  // eval method

  constexpr void eval () noexcept;
  constexpr decltype(auto) operator () () noexcept;

};

#endif // __Ntask_h__
