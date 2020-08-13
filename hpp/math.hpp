#ifndef __math_hpp__
#define __math_hpp__

namespace math
{

struct
{
  template < typename type >
  type operator () (type first)
  {
    return first;
  }

  static constexpr char symbol ()
  {
    return ' ';
  }

} Input;

struct
{
  template < typename type >
  type operator () (type first)
  {
    return first;
  }

  template < typename type, typename ... types >
  auto operator () (type arg, types ... args)
  {
    return arg + operator()(args ...);
  }

  static constexpr char symbol ()
  {
    return '+';
  }

} Add_lambda;

struct
{
  template < typename type >
  type operator () (type first)
  {
    return first;
  }

  template < typename type, typename ... types >
  auto operator () (type arg, types ... args)
  {
    return arg - operator()(args ...);
  }

  static constexpr char symbol ()
  {
    return '-';
  }

} Sub_lambda;

struct
{
  template < typename type >
  type operator () (type first)
  {
    return first;
  }

  template < typename type, typename ... types >
  auto operator () (type arg, types ... args)
  {
    return arg * operator()(args ...);
  }

  static constexpr char symbol ()
  {
    return '*';
  }

} Mul_lambda;

struct
{
  template < typename type >
  type operator () (type first)
  {
    return first;
  }

  template < typename type, typename ... types >
  auto operator () (type arg, types ... args)
  {
    return arg / operator()(args ...);
  }

  static constexpr char symbol ()
  {
    return '/';
  }

} Div_lambda;

struct
{
  template < typename type >
  auto operator () (type args)
  {
    return args;
  }

  template < typename type, typename ... types >
  auto operator () (type arg, types ... args)
  {
    return arg == operator()(args ...);
  }

} Eq_lambda;

struct
{
  template < typename type >
  type operator () (type first)
  {
    return first;
  }

  template < typename type, typename ... types >
  auto operator () (type arg, types ... args)
  {
    return arg != operator()(args ...);
  }

} NEq_lambda;

struct
{
  template < typename type >
  auto operator () (type args)
  {
    return args;
  }

  template < typename type, typename ... types >
  auto operator () (type first, types ... args)
  {
    return first > operator()(args ...);
  }

  static constexpr char symbol ()
  {
    return '>';
  }

} Greater_lambda;

struct
{
  template < typename type >
  auto operator () (type args)
  {
    return args;
  }

  template < typename type, typename ... types >
  auto operator () (type first, types ... args)
  {
    return first < operator()(args ...);
  }

  static constexpr char symbol ()
  {
    return '<';
  }

} Lower_lambda;

struct
{
  template < typename type >
  type operator () (type first)
  {
    return first;
  }

} Get;

} // end namespace


#endif // __math_hpp__
