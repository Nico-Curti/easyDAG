#ifndef __cache_hpp__
#define __cache_hpp__

#include <cache.h>

template < typename lambda, typename ... types >
CacheDecorator < lambda, types ... > :: CacheDecorator (Step < lambda, types ... > x)
{
  this->map[x] = x();
}

template < typename lambda, typename ... types >
auto CacheDecorator < lambda, types ... > :: operator () (Step < lambda, types ... > x)
{
  auto search = this->map.find(x);

  if ( search != this->map.end() )
    return search->second;

  auto result = x();
  this->map[x] = result;

  return result;
}

#endif // __cache_hpp__
