#include <linear_chain.h>
#include <easy.hpp>
#include <timeit.hpp>

#ifndef NREP
  #define NREP 10
#endif

#ifndef NUM
  #define NUM 10
#endif

#define size 100


int main ()
{

  std :: size_t num_threads = 4;

  timeit < NREP, NUM > timer;

  double time_omp = timer.evaluate([&](){linear_chain_omp(size, num_threads);});


  double time_easy = timer.evaluate([&](){linear_chain_task < size >();});

  std :: cout << "OMP: " << time_omp << std :: endl;
  std :: cout << "easyDAG: " << time_easy << std :: endl;

  return 0;
}
