#include <dot_product.h>
#include <easy.hpp>
#include <timeit.hpp>

#ifndef NREP
  #define NREP 10
#endif

#ifndef NUM
  #define NUM 10
#endif


int main ()
{

  std :: size_t num_threads = 4;
  constexpr std :: size_t size = 100;

  timeit < NREP, NUM > timer;

  double time_omp = timer.evaluate([&](){dot_product_omp(size, num_threads);});


  double time_easy = timer.evaluate([&](){dot_product_task < size >();});

  std :: cout << "OMP: " << time_omp << std :: endl;
  std :: cout << "easyDAG: " << time_easy << std :: endl;

  return 0;
}
