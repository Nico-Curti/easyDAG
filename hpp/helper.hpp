#ifndef __helper_hpp__
#define __helper_hpp__

#include <helper.h>

template < std :: size_t idx, char symbol, class Tp, typename std :: enable_if < idx == 0 > :: type * = nullptr >
void print ( std :: ostream & os, Tp & t )
{
  os << std :: get < 0 >(t) << ' ';
}

template < std :: size_t idx, char symbol, class Tp, typename std :: enable_if < idx != 0 > :: type * = nullptr >
void print ( std :: ostream & os, Tp & t )
{
  os << std :: get < idx >(t) << ' ' << symbol << ' ';
  print < idx - 1, symbol > (os, t);
}

template < class T >
std :: ostream & operator << (std :: ostream & os, const std :: vector < T > & x)
{
  for ( std :: size_t i = 0; i < x.size() - 1; ++i )
    os << x[i] << ", ";

  os << x[x.size() - 1] << std :: endl;

  return os;
}

#endif // __helper_hpp__
