#ifndef __cache_h__
#define __cache_h__

#include <functional>
#include <map>

template < typename lambda, typename ... types >
class CacheDecorator
{

  // Private members

  using return_t = typename std :: result_of < Step < lambda, types ... > () > :: type;

  std :: map < Step < lambda, types ... >, return_t > map;

public:

  // Constructor

  CacheDecorator (Step < lambda, types ... > x);

  // Operator

  auto operator () (Step < lambda, types ... > x);

};

#endif // __cache_h__
