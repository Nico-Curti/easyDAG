#include <dot_product.h>
#include <easyDAG.hpp>
#include <numeric>


template < typename T, size_t ... Is >
auto sum_components_impl (T const & t, std :: index_sequence < Is ... >)
{
  return (std :: get < Is >(t) + ...);
}


template < std :: size_t size >
void dot_product_task ()
{
  std :: size_t length = size;
  std :: size_t idx = -1;

  float * x = new float[length];
  float * y = new float[length];

  std :: fill_n(x, size, 1.f);
  std :: fill_n(y, size, 1.f);

  auto dot = [&](float * x, float * y)
             {
               ++idx;
               return x[idx] * y[idx];
             };

  NTask < size, decltype(dot), decltype(x), decltype(y) > prod (dot, x, y);

  using tuple_type = typename decltype(prod) :: res_tuple_type;

  auto acc = [](const tuple_type & x)
             {
               return sum_components_impl(x, std :: make_index_sequence < size > {});
             };

  Task sum = make_task(acc, prod);

  sum.eval();

  // in release the asserts are turned off
  if ( sum() != size )
  {
    std :: cerr << "Error easyDAG: " << sum() << " vs " << size << std :: endl;
    std :: exit(1);
  }

}
