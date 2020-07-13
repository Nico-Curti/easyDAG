#include <linear_chain.h>
#include <task.hpp>

template < int N, class Func, class T, typename std :: enable_if < (N > 0) > :: type * >
auto make_chain (Func & fill_func, T step)
{
  auto temp = make_chain < N - 1 >(fill_func, step);
  return make_task(fill_func, temp());
}


template < int N, class Func, class T, typename std :: enable_if < (N <= 0) > :: type * >
auto make_chain (Func & fill_func, T step)
{
  return make_task(fill_func, step);
}

template < std :: size_t length >
void linear_chain_task ()
{
  std :: size_t counter = -1;

  auto fill = [](const std :: size_t & cnt)
              {
                return cnt + 1;
              };


  auto var = make_task(math :: Input, counter);
  auto fill_task = make_chain < length >(fill, var);

  // in release the asserts are turned off
  if ( fill_task() != length )
  {
    std :: cerr << "Error easyDAG: " << fill_task() << " vs " << length << std :: endl;
    std :: exit(1);
  }
}
