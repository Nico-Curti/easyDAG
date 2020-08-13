#ifndef __step_hpp__
#define __step_hpp__

#include <step.h>

#include <alias.hpp>
#include <helper.hpp>
#include <utils.h>


template < typename lambda, typename ... types >
Step < lambda, types ... > :: Step (lambda & func, types & ... args) : func (std :: forward < lambda >(func)), args (std :: tie(args ...)), _name ("Task")
{
}

template < typename lambda, typename ... types >
std :: string Step < lambda, types ... > :: get_name ()
{
  return this->_name;
}

template < typename lambda, typename ... types > template < class type >
constexpr auto Step < lambda, types ... > :: eval_impl (type & arg) noexcept
{
  using current_type = std :: remove_reference_t < type >;

  // it is a step or it is a derived class of step
  if constexpr ( utils :: is_step_instance < current_type, :: Step > :: value )
    return arg();
  // it is a variable
  else
    return arg;
}

template < typename lambda, typename ... types >
constexpr auto Step < lambda, types ... > :: packing (types  & ... arg) noexcept
{
  return std :: make_tuple (eval_impl(arg) ...);
}

template < typename lambda, typename ... types >
constexpr decltype(auto) Step < lambda, types ... > :: eval () noexcept
{
  return std :: apply(this->func, std :: apply(packing, this->args));
}

template < typename lambda, typename ... types >
constexpr decltype(auto) Step < lambda, types ... > :: operator () () noexcept
{
  return this->eval();
}

template < typename lambda, typename ... types >
constexpr auto Step < lambda, types ... > :: arguments () noexcept
{
  return this->args;
}

template < typename lambda, typename ... types >
constexpr void Step < lambda, types ... > :: set (types & ... args) noexcept
{
  this->args = std :: tuple < types ... >(args ... );
}

template < typename lambda, typename ... types >
constexpr void Step < lambda, types ... > :: name (const std :: string & n) noexcept
{
  this->_name = n;
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator + (T x) noexcept
{
  return Step < decltype(math :: Add_lambda), Step < lambda, types ... >, T > (math :: Add_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator - (T x) noexcept
{
  return Step < decltype(math :: Sub_lambda), Step < lambda, types ... >, T > (math :: Sub_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator * (T x) noexcept
{
  return Step < decltype(math :: Mul_lambda), Step < lambda, types ... >, T > (math :: Mul_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator / (T x) noexcept
{
  return Step < decltype(math :: Div_lambda), Step < lambda, types ... >, T > (math :: Div_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator == (T x) noexcept
{
  return Step < decltype(math :: Eq_lambda), Step < lambda, types ... >, T > (math :: Eq_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator != (T x) noexcept
{
  return Step < decltype(math :: NEq_lambda), Step < lambda, types ... >, T > (math :: NEq_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator < (T x) noexcept
{
  return Step < decltype(math :: Lower_lambda), Step < lambda, types ... >, T > (math :: Lower_lambda, *this, x);
}

template < typename lambda, typename ... types > template < class T >
constexpr auto Step < lambda, types ... > :: operator > (T x) noexcept
{
  return Step < decltype(math :: Greater_lambda), Step < lambda, types ... >, T > (math :: Greater_lambda, *this, x);
}


template < typename lambda, typename ... types >
std :: ostream & operator << (std :: ostream & os, Step < lambda, types ... > x)
{
  auto kwargs = x.arguments();
  os << x.get_name() << " ( ";

  if constexpr ( utils :: has_symbol < lambda > :: value )
    print < std :: tuple_size < decltype(kwargs) > :: value - 1, lambda :: symbol() > (os, kwargs);
  else
    print < std :: tuple_size < decltype(kwargs) > :: value - 1, ',' > (os, kwargs);

  os << ")";
  return os;
}

template < typename lambda, typename ... types > template < class Func, std :: size_t idx, class ... Args >
constexpr decltype(auto) Step < lambda, types ... > :: traverse_impl (Func & func, Args && ... args) noexcept
{
  if constexpr (idx + 1 < sizeof ... (types))
    this->traverse_impl < Func, idx + 1 > (func, args ...);

  using idx_t = utils :: nth_type_of < idx, types ... >;

  if constexpr ( utils :: is_step < idx_t > :: value ) // it is a step
    return std :: get < idx >(this->args).traverse (func, args ...);

  else if constexpr ( utils :: is_variable < idx_t > :: value ) // it is a variable
    return func (std :: get < idx >(this->args), args ...);
}

template < typename lambda, typename ... types > template < class Func, class ... Args >
constexpr decltype(auto) Step < lambda, types ... > :: traverse (Func & func, Args && ... args) noexcept
{
  return this->traverse_impl < Func, 0 >(func, args ...);
}

template < typename lambda, typename ... types > template < std :: size_t idx >
constexpr void Step < lambda, types ... > :: dump_impl (std :: ostream & os) noexcept
{
  if constexpr (idx + 1 < sizeof ... (types))
    dump_impl < idx + 1 > (os);

  using idx_t = utils :: nth_type_of < idx, types ... >;

  if constexpr ( utils :: is_step < idx_t > :: value ) // it is a step
  {
    os << "  " << this->get_name() << " -> " << std :: get < idx >(this->args).get_name() << std :: endl;
    std :: get < idx >(this->args).dump(os);
  }
  else if constexpr ( utils :: is_variable < idx_t > :: value ) // it is a variable
    os << "  " << this->get_name() << " -> " << std :: get < idx >(this->args).get_name() << std :: endl;
}

template < typename lambda, typename ... types >
constexpr void Step < lambda, types ... > :: dump (std :: ostream & os) noexcept
{
  os << "  " << this->get_name() << "[shape=box, style=filled,color=\".7 .3 1.0\"]" << std :: endl;
  this->dump_impl < 0 >(os);
}

template < typename lambda, typename ... types >
constexpr void Step < lambda, types ... > :: graphviz (std :: ostream & os, const std :: string & graph_name) noexcept
{
  os << "digraph " << graph_name << " {" << std :: endl;

  this->dump (os);

  os << "}" << std :: endl;
}

template < typename lambda, typename ... types >
constexpr Step < lambda, types ... > make_step (lambda & func, types ... args) noexcept
{
  return Step < lambda, types ... >(func, args ...);
}

template < typename type >
constexpr Step < decltype(math :: Input), type > InputVariable (type & var) noexcept
{
  return Step < decltype(math :: Input), type >(math :: Input, var);
}

template < typename type >
constexpr Step < decltype(math :: Input), type > InputVariable () noexcept
{
  type dummy = type();
  return Step < decltype(math :: Input), type >(math :: Input, dummy);
}

#endif // __step_hpp__
