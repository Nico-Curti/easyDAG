#ifndef __helper_h__
#define __helper_h__

#include <vector>
#include <tuple>

namespace details
{

  template < class, template < class ... > class, class ... >
  struct is_instance : public std :: false_type {};

  template < class T, template < class ... > class U, class ... V >
  struct is_instance < U < T, V ... >, U > : public std :: true_type {};

}

template < std :: size_t I = 0, char symbol, typename ... Tp >
void print ( std :: tuple < Tp ... > & t);

template < class T >
std :: ostream & operator << (std :: ostream & os, const std :: vector < T > & x);

#endif // __helper_h__
