#ifndef __timeit_h__
#define __timeit_h__

#include <iostream>
#include <algorithm>
#include <climits>
#include <memory>

#ifdef _OPENMP

  #include <omp.h>             // omp_get_num_threads, timeit function

#elif defined _MPI

#include <boost/mpi/timer.hpp> // boost :: mpi :: timer()

#else

  #include <chrono>            // timeit function

#endif


template < int Nrep, int Num >
class timeit
{

  std :: unique_ptr < double[] > _times;
  double _min_time;
  double _speedup;

public:

  // Constructor

  timeit ();


  // Public Methods

  double speedup ();

  template < typename lambda >
  double evaluate (lambda f);


  template < typename lambda_1, typename lambda_2 >
  double compare (lambda_1 f, lambda_2 g);


private:

#ifdef _OPENMP

  double what_time_is_it_now ();

#elif defined _MPI

  boost :: mpi :: timer what_time_is_it_now ();

#else

  std :: chrono :: time_point < std :: chrono :: high_resolution_clock > what_time_is_it_now ();

#endif

  template < typename Time >
  double elapsed_time (const Time & start_time);

  template < int N, typename lambda, typename std :: enable_if < N != 0 > :: type * = nullptr >
  double mean_time (const double & sum_time, lambda f);
  template < int N, typename lambda, typename std :: enable_if < N == 0 > :: type * = nullptr >
  double mean_time (const double & sum_time, lambda f);

};


#endif // __timeit_h__
