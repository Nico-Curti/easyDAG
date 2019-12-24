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

  static constexpr char symbol ()
  {
    return ' ';
  }

} Input;

struct
{
  template < typename ... types >
  auto operator () (types ... args)
  {
    return (args + ...);
  }

  static constexpr char symbol ()
  {
    return '+';
  }

} Add_lambda;

struct
{
  template < typename ... types >
  auto operator () (types ... args)
  {
    return (args - ...);
  }

  static constexpr char symbol ()
  {
    return '-';
  }

} Sub_lambda;

struct
{
  template < typename ... types >
  auto operator () (types ... args)
  {
    return (args * ...);
  }

  static constexpr char symbol ()
  {
    return '*';
  }

} Mul_lambda;

struct
{
  template < typename ... types >
  auto operator () (types ... args)
  {
    return (args / ...);
  }

  static constexpr char symbol ()
  {
    return '/';
  }

} Div_lambda;

struct
{
  template < typename ... types >
  auto operator () (types ... args)
  {
    return (args == ...);
  }

} Eq_lambda;

struct
{
  template < typename ... types >
  auto operator () (types ... args)
  {
    return (args != ...);
  }

} NEq_lambda;

struct
{
  template < typename ... types >
  auto operator () (types ... args)
  {
    return (args > ...);
  }

  static constexpr char symbol ()
  {
    return '>';
  }

} Greater_lambda;

struct
{
  template < typename ... types >
  auto operator () (types ... args)
  {
    return (args < ...);
  }

  static constexpr char symbol ()
  {
    return '<';
  }

} Lower_lambda;


} // end namespace


#endif // __math_hpp__
