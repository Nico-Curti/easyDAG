#ifndef __linear_chain_h__
#define __linear_chain_h__

#include <iostream>

template < int N, class Func, class T, typename std :: enable_if < (N > 0) > :: type * = nullptr >
auto make_chain (Func & fill_func, T step);
template < int N, class Func, class T, typename std :: enable_if < (N <= 0) > :: type * = nullptr >
auto make_chain (Func & fill_func, T step);

template < std :: size_t length >
void linear_chain_task ();

void linear_chain_omp (const std :: size_t & length, const unsigned & num_threads);



#endif // __linear_chain_h__
