#include <binary_tree.h>
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
  constexpr std :: size_t size = 12;

  timeit < NREP, NUM > timer;

  double time_omp = timer.evaluate([&](){binary_tree_omp(size, num_threads);});


  double time_easy = timer.evaluate([&](){binary_tree_task < size >();});

  std :: cout << "OMP: " << time_omp << std :: endl;
  std :: cout << "easyDAG: " << time_easy << std :: endl;

  return 0;
}
