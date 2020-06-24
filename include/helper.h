#ifndef __helper_h__
#define __helper_h__

#include <tuple>
#include <vector>
#include <type_traits>

template < std :: size_t idx, char symbol, class Tp, typename std :: enable_if < idx == 0 > :: type * = nullptr >
void print ( std :: ostream & os, Tp & t );

template < std :: size_t idx, char symbol, class Tp, typename std :: enable_if < idx != 0 > :: type * = nullptr >
void print ( std :: ostream & os, Tp & t );

template < class T >
std :: ostream & operator << (std :: ostream & os, const std :: vector < T > & x);

#endif // __helper_h__
