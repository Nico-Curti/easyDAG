#ifndef __binary_tree_h__
#define __binary_tree_h__

#include <iostream>
#include <atomic>

template < int N, class L, class R, typename std :: enable_if < (N > 0) > :: type * = nullptr >
auto make_tree (L left, R right);
template < int N, class L, class R, typename std :: enable_if < (N <= 0) > :: type * = nullptr >
auto make_tree (L left, R right);

void binary_tree_omp (const std :: size_t & num_layers, const unsigned & num_threads);

#endif // __binary_tree_h__
