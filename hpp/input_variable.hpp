#ifndef __inputvar_hpp__
#define __inputvar_hpp__

#include <input_variable.h>
#include <math.hpp>

template < typename type >
InputVariable < type > :: InputVariable ()
{
  this->var = nullptr;
}

template < typename type >
InputVariable < type > :: InputVariable (type & var)
{
  this->var = &var;
}


template < typename type >
InputVariable < type > :: InputVariable (const InputVariable & x)
{
  this->var = x.var;
}

template < typename type >
void InputVariable < type > :: set (type & var)
{
  this->var = &var;
}

template < typename type >
type InputVariable < type > :: operator () () const
{
  return *this->var;
}


template < typename type > template < typename type2 >
auto InputVariable < type > :: operator + (InputVariable < type2 > x)
{
  return Step < decltype(math :: Add_lambda), InputVariable < type >, InputVariable < type2 > > (math :: Add_lambda, *this, x);
}

template < typename type > template < typename type2 >
auto InputVariable < type > :: operator - (InputVariable < type2 > x)
{
  return Step < decltype(math :: Sub_lambda), InputVariable < type >, InputVariable < type2 > > (math :: Sub_lambda, *this, x);
}

template < typename type > template < typename type2 >
auto InputVariable < type > :: operator / (InputVariable < type2 > x)
{
  return Step < decltype(math :: Div_lambda), InputVariable < type >, InputVariable < type2 > > (math :: Div_lambda, *this, x);
}

template < typename type > template < typename type2 >
auto InputVariable < type > :: operator * (InputVariable < type2 > x)
{
  return Step < decltype(math :: Mul_lambda), InputVariable < type >, InputVariable < type2 > > (math :: Mul_lambda, *this, x);
}

template < typename type > template < typename type2 >
auto InputVariable < type > :: operator == (InputVariable < type2 > x)
{
  return Step < decltype(math :: Eq_lambda), InputVariable < type >, InputVariable < type2 > > (math :: Eq_lambda, *this, x);
}

template < typename type > template < typename type2 >
auto InputVariable < type > :: operator != (InputVariable < type2 > x)
{
  return Step < decltype(math :: NEq_lambda), InputVariable < type >, InputVariable < type2 > > (math :: NEq_lambda, *this, x);
}

template < typename type > template < typename type2 >
auto InputVariable < type > :: operator < (InputVariable < type2 > x)
{
  return Step < decltype(math :: Greater_lambda), InputVariable < type >, InputVariable < type2 > > (math :: Greater_lambda, *this, x);
}

template < typename type > template < typename type2 >
auto InputVariable < type > :: operator > (InputVariable < type2 > x)
{
  return Step < decltype(math :: Lower_lambda), InputVariable < type >, InputVariable < type2 > > (math :: Lower_lambda, *this, x);
}

// cas with steps

template < typename type > template < typename lambda, typename ... types >
auto InputVariable < type > :: operator + (Step < lambda, types ... > x)
{
  return Step < decltype(math :: Add_lambda), InputVariable < type >, Step < lambda, types ... > > (math :: Add_lambda, *this, x);
}

template < typename type > template < typename lambda, typename ... types >
auto InputVariable < type > :: operator - (Step < lambda, types ... > x)
{
  return Step < decltype(math :: Sub_lambda), InputVariable < type >, Step < lambda, types ... > > (math :: Sub_lambda, *this, x);
}

template < typename type > template < typename lambda, typename ... types >
auto InputVariable < type > :: operator / (Step < lambda, types ... > x)
{
  return Step < decltype(math :: Div_lambda), InputVariable < type >, Step < lambda, types ... > > (math :: Div_lambda, *this, x);
}

template < typename type > template < typename lambda, typename ... types >
auto InputVariable < type > :: operator * (Step < lambda, types ... > x)
{
  return Step < decltype(math :: Mul_lambda), InputVariable < type >, Step < lambda, types ... > > (math :: Mul_lambda, *this, x);
}

template < typename type > template < typename lambda, typename ... types >
auto InputVariable < type > :: operator == (Step < lambda, types ... > x)
{
  return Step < decltype(math :: Eq_lambda), InputVariable < type >, Step < lambda, types ... > >  (math :: Eq_lambda, *this, x);
}

template < typename type > template < typename lambda, typename ... types >
auto InputVariable < type > :: operator != (Step < lambda, types ... > x)
{
  return Step < decltype(math :: NEq_lambda), InputVariable < type >, Step < lambda, types ... > > (math :: NEq_lambda, *this, x);
}

template < typename type > template < typename lambda, typename ... types >
auto InputVariable < type > :: operator < (Step < lambda, types ... > x)
{
  return Step < decltype(math :: Greater_lambda), InputVariable < type >, Step < lambda, types ... > > (math :: Greater_lambda, *this, x);
}

template < typename type > template < typename lambda, typename ... types >
auto InputVariable < type > :: operator > (Step < lambda, types ... > x)
{
  return Step < decltype(math :: Lower_lambda), InputVariable < type >, Step < lambda, types ... > > (math :: Lower_lambda, *this, x);
}

template < typename type >
std :: ostream & operator << (std :: ostream & os, const InputVariable < type > & x)
{
  os << x();
  return os;
}

#endif // __inputvar_hpp__
