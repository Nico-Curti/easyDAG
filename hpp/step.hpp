#ifndef __step_hpp__
#define __step_hpp__

#include <step.h>

#include <alias.hpp>
#include <helper.hpp>
#include <utils.hpp>


template < typename lambda, typename ... types >
Step < lambda, types ... > :: Step (lambda & func, types & ... args) : func (std :: forward < lambda >(func)), args (std :: tie(args ...)), value ( std :: async ( std :: launch :: async, & Step < lambda, types ... > :: evaluate, this ) ), _name ("Step")
{
}

template < typename lambda, typename ... types > template < std :: size_t idx >
constexpr auto Step < lambda, types ... > :: num_variables_impl () noexcept
{
  if constexpr (idx < sizeof ... (types))
  {
    using idx_t = utils :: nth_type_of < idx, types ... >;
    if constexpr (details :: is_instance < idx_t, Step > :: value)
      return idx_t :: num_variables() + num_variables_impl < idx + 1 >();

    return num_operations_impl < idx + 1 >() + 1;
  }
  else
    return 0;
}

template < typename lambda, typename ... types >
constexpr auto Step < lambda, types ... > :: num_variables () noexcept
{
  return num_variables_impl < 0 > ();
}

template < typename lambda, typename ... types > template < std :: size_t idx >
constexpr auto Step < lambda, types ... > :: num_operations_impl () noexcept
{
  if constexpr (idx < sizeof ... (types))
  {
    using idx_t = utils :: nth_type_of < idx, types ... >;
    if constexpr (utils :: is_step < idx_t >())
      return idx_t :: num_operations() + num_operations_impl < idx + 1 >();

    return num_operations_impl < idx + 1 >();
  }
  else
    return 0;

}

template < typename lambda, typename ... types >
constexpr auto Step < lambda, types ... > :: num_operations () noexcept
{
  return num_operations_impl < 0 > () + 1;
}

template < typename lambda, typename ... types >
constexpr auto Step < lambda, types ... > :: size () noexcept
{
  return num_variables() + num_operations();
}

template < typename lambda, typename ... types >
constexpr std :: string Step < lambda, types ... > :: get_name () noexcept
{
  return this->_name;
}

template < typename lambda, typename ... types > template < class type >
constexpr auto Step < lambda, types ... > :: eval_impl (type & arg) noexcept
{
  if constexpr ( details :: is_instance < std :: remove_reference_t < type > , Step > :: value )
    return arg();
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
  return std :: apply(packing, this->args);
}

template < typename lambda, typename ... types >
constexpr decltype(auto) Step < lambda, types ... > :: evaluate () noexcept
{
  return std :: apply(this->func, this->eval());
}

template < typename lambda, typename ... types >
constexpr decltype(auto) Step < lambda, types ... > :: operator () () noexcept
{
  return this->value.get();
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
  this->value = std :: async ( std :: launch :: async, & Step < lambda, types ... > :: evaluate, this );
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

  if constexpr ( details :: has_symbol < lambda > :: value )
    print < std :: tuple_size < decltype(kwargs) > :: value - 1, lambda :: symbol() > (os, kwargs);
  else
    print < std :: tuple_size < decltype(kwargs) > :: value - 1, ' ' > (os, kwargs);

  os << ")";
  return os;
}

template < typename lambda, typename ... types > template < std :: size_t idx >
constexpr void Step < lambda, types ... > :: dump_impl (std :: ostream & os) noexcept
{
  if constexpr (idx + 1 < sizeof ... (types))
  {
    using idx_t = utils :: nth_type_of < idx + 1, types ... >;

    os << std :: get < idx >(this->args).get_name() << std :: endl;
    os << "  " << this->get_name() << " -> ";

    dump_impl < idx + 1 > (os);

    if constexpr ( utils :: is_step < idx_t >() ) // it is a step
    {
      std :: get < idx >(this->args).dump(os);
      os << std :: endl;
    }
  }

  else
  {
    using idx_t = utils :: nth_type_of < idx, types ... >;

    if constexpr ( utils :: is_step < idx_t >() ) // it is a step
    {
      os << std :: get < idx >(this->args).get_name() << std :: endl;

      std :: get < idx >(this->args).dump(os);
      os << std :: endl;
    }
    else if constexpr ( utils :: is_variable < idx_t >() ) // it is a variable
      os << std :: get < idx >(this->args).get_name();
  }

}

template < typename lambda, typename ... types >
constexpr void Step < lambda, types ... > :: dump (std :: ostream & os) noexcept
{
  os << "  " << this->get_name() << "[shape=box, style=filled,color=\".7 .3 1.0\"]" << std :: endl;
  os << "  " << this->get_name() << " -> ";
  this->dump_impl < 0 >(os);
}

template < typename lambda, typename ... types >
constexpr void Step < lambda, types ... > :: graph (std :: ostream & os, const std :: string & graph_name) noexcept
{
  os << "digraph " << graph_name << " {" << std :: endl;

  this->dump (os);

  os << "}" << std :: endl;
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
