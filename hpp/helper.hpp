#ifndef __helper_hpp__
#define __helper_hpp__

#include <helper.h>

template < std :: size_t I, char symbol, typename ... Tp >
void print ( std :: ostream & os, std :: tuple < Tp ... > & t )
{
  if constexpr (I > 0)
  {
    os << std :: get < I >(t) << " " << symbol << " ";
    print < I - 1, symbol, Tp ... >(os, t);
  }
  else
    os << std :: get < I >(t) << " ";
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
