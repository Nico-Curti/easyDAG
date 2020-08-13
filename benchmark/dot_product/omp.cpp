#include <dot_product.h>
#include <algorithm>
#include <numeric>

void dot_product_omp (const std :: size_t & length, const unsigned & num_threads)
{
  float * x  = new float [length];
  float * y  = new float [length];
  float dot = 0.f;

  std :: fill_n(x, length, 1.f);
  std :: fill_n(y, length, 1.f);

  #pragma omp parallel num_threads (num_threads)
  {
    #pragma omp single
    {
      for (std :: size_t i = 0; i < length; ++i)
      {

        if ( i == 0)
        {
          #pragma omp task firstprivate (i) depend (out:x[i])
          {
            dot += x[i] * y[i];
          }
        }
        else
        {
          #pragma omp task firstprivate (i) depend (out:x[i]) depend (in:x[i-1])
          {
            dot += x[i] * y[i];
          }
        }
      }
    }
  }

  delete[] x;
  delete[] y;

  // in release the asserts are turned off
  if ( dot != length )
  {
    std :: cerr << "Error OMP: " << dot << " vs " << length << std :: endl;
    std :: exit(1);
  }
}
