#ifndef __timeit_hpp__
#define __timeit_hpp__

#include <timeit.h>

template < int Num, int Nrep >
timeit < Num, Nrep > :: timeit () : _min_time (std :: numeric_limits < double > :: infinity ()), _speedup (0.)
{
  _times = std :: make_unique < double[] >(Nrep);
}

template < int Num, int Nrep >
double timeit < Num, Nrep > :: speedup ()
{
  return _speedup;
}

template < int Num, int Nrep >
template < int N, typename lambda, typename std :: enable_if < N != 0 > :: type * >
double timeit < Num, Nrep > :: mean_time (const double & sum_time, lambda f)
{
  auto start_time = what_time_is_it_now();

  std :: forward < decltype(f) > (f) ();

  return mean_time < N - 1, lambda >(sum_time + elapsed_time(start_time), f);
}

template < int Num, int Nrep >
template < int N, typename lambda, typename std :: enable_if < N == 0 > :: type * >
double timeit < Num, Nrep > :: mean_time (const double & sum_time, lambda f)
{
  auto start_time = what_time_is_it_now();

  std :: forward < decltype(f) > (f) ();

  return sum_time + elapsed_time(start_time);
}


template < int Num, int Nrep >
template < typename lambda >
double timeit < Num, Nrep > :: evaluate (lambda f)
{
  _speedup = 0.;
  _min_time = std :: numeric_limits < double > :: infinity();

// #ifdef _OPENMP
// #pragma omp parallel for reduction (min : _min_time)
// #endif
  for (int i = 0; i < Nrep; ++i)
  {
    double times = mean_time < Num, lambda >(0., f) / Num;
    _times[i] = times;

    _min_time = times < _min_time ? times : _min_time;
  }

  return _min_time;
}

template < int Num, int Nrep >
template < typename lambda_1, typename lambda_2 >
double timeit < Num, Nrep > :: compare (lambda_1 f, lambda_2 g)
{
  double t1 = evaluate < lambda_1 >(f);
  double t2 = evaluate < lambda_2 >(g);

  _speedup = t2 == 0. ? 0. : t1 / t2;

  return _speedup;
}

#ifdef _OPENMP

  template < int Num, int Nrep >
  double timeit < Num, Nrep > :: what_time_is_it_now ()
  {
    return omp_get_wtime();
  }

#elif defined _MPI

  template < int Num, int Nrep >
  boost :: mpi :: timer timeit  < Num, Nrep > :: what_time_is_it_now ()
  {
    return boost :: mpi :: timer();
  }

#else

  template < int Num, int Nrep >
  std :: chrono :: time_point < std :: chrono :: high_resolution_clock > timeit < Num, Nrep > :: what_time_is_it_now ()
  {
    return std :: chrono :: high_resolution_clock :: now ();
  }

#endif

template < int Num, int Nrep >
template < typename Time >
double timeit < Num, Nrep > :: elapsed_time (const Time & start_time)
{
#ifdef _OPENMP

  return omp_get_wtime() - start_time;

#elif defined _MPI

  return start_time.elapsed();

#else

  return static_cast < double > (std :: chrono :: duration_cast < std :: chrono :: microseconds > (std :: chrono :: high_resolution_clock :: now () - start_time).count() ) * 1e-6; // seconds

#endif
}


#endif // __timeit_hpp__
