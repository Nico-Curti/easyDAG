#include <linear_chain.h>
#include <omp.h>

void linear_chain_omp (const std :: size_t & length, const unsigned & num_threads)
{
  std :: size_t counter = 0;
  std :: size_t * D  = new std :: size_t [length];

  #pragma omp parallel num_threads (num_threads)
  {
    #pragma omp single
    {
      for (std :: size_t i = 0; i < length; ++i)
      {

        if ( i == 0)
        {
          #pragma omp task firstprivate (i) depend (out:D[i])
          {
            ++counter;
          }
        }
        else
        {
          #pragma omp task firstprivate (i) depend (out:D[i]) depend (in:D[i-1])
          {
            ++counter;
          }
        }
      }
    }
  }

  delete[] D;

  // in release the asserts are turned off
  if ( counter != length )
  {
    std :: cerr << "Error OMP: " << counter << " vs " << length << std :: endl;
    std :: exit(1);
  }
}

