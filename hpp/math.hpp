#ifndef __math_hpp__
#define __math_hpp__

namespace math
{

struct
{
  template < typename type >
  auto operator () (type first)
  {
    return first;
  }

  template < typename type, typename ... types >
  auto operator () (type first, types ... args)
  {
    return first + operator()(args...);
  }

} Add_lambda;

struct
{
  template < typename type >
  auto operator () (type first)
  {
    return first;
  }

  template < typename type, typename ... types >
  auto operator () (type first, types ... args)
  {
    return first - operator()(args...);
  }

} Sub_lambda;

struct
{
  template < typename type >
  auto operator () (type first)
  {
    return first;
  }

  template < typename type, typename ... types >
  auto operator () (type first, types ... args)
  {
    return first * operator()(args...);
  }

} Mul_lambda;

struct
{
  template < typename type >
  auto operator () (type first)
  {
    return first;
  }

  template < typename type, typename ... types >
  auto operator () (type first, types ... args)
  {
    return first / operator()(args...);
  }

} Div_lambda;

struct
{
  template < typename type >
  auto operator () (type first)
  {
    return first;
  }

  template < typename type, typename ... types >
  auto operator () (type first, types ... args)
  {
    return first == operator()(args...);
  }

} Eq_lambda;

struct
{
  template < typename type >
  auto operator () (type first)
  {
    return first;
  }

  template < typename type, typename ... types >
  auto operator () (type first, types ... args)
  {
    return first != operator()(args...);
  }

} NEq_lambda;

struct
{
  template < typename type >
  auto operator () (type first)
  {
    return first;
  }

  template < typename type, typename ... types >
  auto operator () (type first, types ... args)
  {
    return first > operator()(args...);
  }

} Greater_lambda;

struct
{
  template < typename type >
  auto operator () (type first)
  {
    return first;
  }

  template < typename type, typename ... types >
  auto operator () (type first, types ... args)
  {
    return first < operator()(args...);
  }

} Lower_lambda;


} // end namespace


#endif // __math_hpp__
