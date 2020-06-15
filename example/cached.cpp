/****************** CACHED EXAMPLE *****************/
// Last update: 15/06/2020
//
// In this example we verify the cached values.
// If the DAG has been already evaluated its dependencies
// are not re-computed.
// In this way long computations but also common steps
// do not need to be evaluated several times!
//
/***************************************************/

#include <step.hpp>

#include <numeric>
#include <cassert>
#include <iostream>
#include <algorithm>


int main ()
{
  const int N = 10;

  auto init = [&](const int & N)
              {
                std :: cout << "I'm the initializer" << std :: endl;
                float * x = new float[N];
                return x;
              };
  auto fill = [&](float * x)
              {
                std :: cout << "I'm the filler" << std :: endl;
                std :: fill_n(x, N, 1.f);
                return x;
              };
  auto sum  = [&](float * x)
              {
                std :: cout << "I'm the sum reduction" << std :: endl;
                return std :: accumulate(x, x + N, 0.f);
              };

  auto prod = [&](float * x)
              {
                std :: cout << "I'm the prod reduction" << std :: endl;
                return std :: accumulate(x, x + N, 1.f, std :: multiplies < float >());
              };

  auto a = InputVariable(N);

  Step init_step(init, a);
  Step fill_step(fill, init_step);
  Step sum_step(sum, fill_step);
  Step prod_step(prod, fill_step);

  auto result = sum_step();

  assert ( result == N );

  std :: cout << "Summation result: " << result << std :: endl;

  // Re-calling the same evaluation the lambdas are not recomputed (aka no cout)!

  std :: cout << "Re-called summ value: " << sum_step () << std :: endl;

  // But also if we use common steps they do not need to be re-computed!

  std :: cout << "Product result: " << prod_step() << std :: endl;

  return 0;
}
