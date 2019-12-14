#ifndef __step_hpp__
#define __step_hpp__

#include <step.h>
#include <math.hpp>

template < typename lambda, typename ... types >
Step < lambda, types ... > :: Step (lambda func, types ... args) : func (std :: forward < lambda >(func)), args (std :: forward < types >(args) ... )
{
}

template < typename lambda, typename ... types > template < typename ... kwargs, int ... Is >
auto Step < lambda, types ... > :: _func ( std :: tuple < kwargs ... > & tup, helper :: index < Is ... >)
{
  return this->func(std :: get < Is >(tup) ... );
}

template < typename lambda, typename ... types > template < typename ... kwargs >
auto Step < lambda, types ... > :: _func (std :: tuple < kwargs ... > & tup)
{
  return this->_func(tup, helper :: gen_seq < sizeof ... (kwargs) > {} );
}


template < typename lambda, typename ... types > template < std :: size_t ... Idx >
constexpr auto Step < lambda, types ... > :: eval_tuple_impl (std :: index_sequence < Idx ... >) noexcept
{
  return std :: tuple { [&]()
                        {
                          if constexpr (std :: is_invocable < decltype(std :: get < Idx >(this->args)) > :: value)
                            return std :: get < Idx > (this->args)();
                          else
                            return std :: get < Idx > (this->args);
                         }() ...
                      };
}

template < typename lambda, typename ... types >
constexpr auto Step < lambda, types ... > :: eval_tuple () noexcept
{
  return eval_tuple_impl (std :: index_sequence_for < types ... > {} );
}

template < typename lambda, typename ... types >
auto Step < lambda, types ... > :: operator () ()
{
  auto kwargs = this->eval_tuple();
  return this->_func(kwargs);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
auto Step < lambda, types ... > :: operator + (Step < lambda2, types2 ... > x)
{
  return Step < decltype(math :: Add_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Add_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
auto Step < lambda, types ... > :: operator - (Step < lambda2, types2 ... > x)
{
  return Step < decltype(math :: Sub_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Sub_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
auto Step < lambda, types ... > :: operator * (Step < lambda2, types2 ... > x)
{
  return Step < decltype(math :: Mul_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Mul_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
auto Step < lambda, types ... > :: operator / (Step < lambda2, types2 ... > x)
{
  return Step < decltype(math :: Div_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Div_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
auto Step < lambda, types ... > :: operator == (Step < lambda2, types2 ... > x)
{
  return Step < decltype(math :: Eq_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Eq_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
auto Step < lambda, types ... > :: operator != (Step < lambda2, types2 ... > x)
{
  return Step < decltype(math :: NEq_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: NEq_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
auto Step < lambda, types ... > :: operator < (Step < lambda2, types2 ... > x)
{
  return Step < decltype(math :: Lower_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Lower_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
auto Step < lambda, types ... > :: operator > (Step < lambda2, types2 ... > x)
{
  return Step < decltype(math :: Greater_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Greater_lambda, *this, x);
}

// cas with inputvariable


template < typename lambda, typename ... types > template < typename type >
auto Step < lambda, types ... > :: operator + (InputVariable < type > x)
{
  return Step < decltype(math :: Add_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: Add_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
auto Step < lambda, types ... > :: operator - (InputVariable < type > x)
{
  return Step < decltype(math :: Sub_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: Sub_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
auto Step < lambda, types ... > :: operator * (InputVariable < type > x)
{
  return Step < decltype(math :: Mul_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: Mul_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
auto Step < lambda, types ... > :: operator / (InputVariable < type > x)
{
  return Step < decltype(math :: Div_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: Div_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
auto Step < lambda, types ... > :: operator == (InputVariable < type > x)
{
  return Step < decltype(math :: Eq_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: Eq_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
auto Step < lambda, types ... > :: operator != (InputVariable < type > x)
{
  return Step < decltype(math :: NEq_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: NEq_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
auto Step < lambda, types ... > :: operator < (InputVariable < type > x)
{
  return Step < decltype(math :: Lower_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: Lower_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
auto Step < lambda, types ... > :: operator > (InputVariable < type > x)
{
  return Step < decltype(math :: Greater_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: Greater_lambda, *this, x);
}

// aliases

namespace math
{

  template < typename ... types >
  constexpr Step < decltype(Add_lambda), types ... > Sum (types ... args) noexcept
  {
    return Step < decltype(Add_lambda), types ... >(Add_lambda, args ...);
  }

  template < typename ... types >
  constexpr Step < decltype(Sub_lambda), types ... > Sub (types ... args) noexcept
  {
    return Step < decltype(Sub_lambda), types ... >(Sub_lambda, args ...);
  }

} // end namespace




#endif // __step_hpp__
