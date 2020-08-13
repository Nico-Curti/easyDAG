#ifndef __Ntask_hpp__
#define __Ntask_hpp__

#include <ntask.h>

template < std :: size_t N, typename lambda, typename ... types >
NTask < N, lambda, types ... > :: NTask (lambda & func, types & ... args) : Step < decltype(math :: Get), res_tuple_type > (math :: Get, res),
                                                                            tasks (detail :: make_n_tuple < N - 1, Task < lambda, types ... >, lambda, types ... >(func, args ...))
{
}

template < std :: size_t N, typename lambda, typename ... types > template < std :: size_t n >
constexpr void NTask < N, lambda, types ... > :: eval_impl () noexcept
{
  if constexpr (n > 0)
    this->eval_impl < n - 1 >();

  std :: get < n >(this->tasks).eval();
}

template < std :: size_t N, typename lambda, typename ... types >
constexpr void NTask < N, lambda, types ... > :: eval () noexcept
{
  this->eval_impl < N - 1 >();
}

template < std :: size_t N, typename lambda, typename ... types > template < std :: size_t n >
constexpr decltype(auto) NTask < N, lambda, types ... > :: get_impl () noexcept
{
  if constexpr (n < N - 1)
    return std :: tuple_cat(std :: make_tuple(std :: get < n >(this->tasks)()), this->get_impl < n + 1 >());
  else
    return std :: make_tuple(std :: get < n >(this->tasks)());
}


template < std :: size_t N, typename lambda, typename ... types >
constexpr decltype(auto) NTask < N, lambda, types ... > :: operator () () noexcept
{
  this->res = this->get_impl < 0 >();
  return this->res;
}


#endif // __Ntask_hpp__
