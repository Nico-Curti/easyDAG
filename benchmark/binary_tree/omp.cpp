#include <binary_tree.h>
#include <omp.h>

void binary_tree_omp (const std :: size_t & num_layers, const unsigned & num_threads)
{
  std :: atomic < std :: size_t > counter {0};

  std :: size_t N = 1 << num_layers;
  std :: size_t *D = new std :: size_t [N];

  #pragma omp parallel num_threads (num_threads)
  {
    #pragma omp single
    {
      for (std :: size_t i = 1; i < N; ++i)
      {
        std :: size_t p = i / 2;
        std :: size_t l = i * 2;
        std :: size_t r = l + 1;

        if (l < N && r < N)
        {
          #pragma omp task firstprivate (i) depend (out:D[l], D[r]) depend (in:D[p])
          {
            counter.fetch_add(1, std :: memory_order_relaxed);
          }
        }
        else
        {
          #pragma omp task firstprivate (i) depend (in:D[p])
          {
            counter.fetch_add(1, std :: memory_order_relaxed);
          }
        }
      }
    }
  }

  // in release the asserts are turned off
  if ( counter + 1 != N )
  {
    std :: cerr << "Error OMP: " << counter + 1 << " vs " << N << std :: endl;
    std :: exit(1);
  }

  delete [] D;
}

