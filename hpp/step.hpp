#ifndef __step_hpp__
#define __step_hpp__

#include <step.h>
#include <math.hpp>
// #include cachedecorator

template < typename lambda, typename ... types >
Step < lambda, types ... > :: Step (lambda func, types ... args) : func (std :: forward < lambda >(func)), args (std :: forward < types >(args) ... )
{
}

template < typename lambda, typename ... types > template < typename ... kwargs, std :: size_t ... Idx >
constexpr auto Step < lambda, types ... > :: _func ( std :: tuple < kwargs ... > & tup, std :: index_sequence < Idx ... >) noexcept
{
  return this->func(std :: get < Idx >(tup) ... );
}

template < typename lambda, typename ... types > template < typename ... kwargs >
constexpr auto Step < lambda, types ... > :: _func (std :: tuple < kwargs ... > & tup) noexcept
{
  return this->_func(tup, std :: index_sequence_for < kwargs ... > {} );
}


template < typename lambda, typename ... types > template < std :: size_t ... Idx >
constexpr auto Step < lambda, types ... > :: eval_tuple_impl (std :: index_sequence < Idx ... >) noexcept
{
  return std :: tuple { [&]()
                        {
                          if constexpr (std :: is_invocable < decltype(std :: get < Idx >(this->args)) > :: value)
                          {
                            // if constexpr (std :: is_same_v < std :: remove_cv_t < std :: remove_reference_t < decltype(std :: get < Idx > (this->args)) > >, InputVariable < decltype(std :: get < Idx > (this->args)()) > >)
                            // {
                            //   return std :: get < Idx > (this->args)();
                            // }
                            // else
                            // {
                            //   return CacheDecorator(std :: get < Idx > (this->args))(std :: get < Idx > (this->args));
                            // }
                            return std :: get < Idx > (this->args)();
                          }
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
constexpr auto Step < lambda, types ... > :: operator () () noexcept
{
  auto kwargs = this->eval_tuple();
  return this->_func(kwargs);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
constexpr auto Step < lambda, types ... > :: operator + (Step < lambda2, types2 ... > x) noexcept
{
  return Step < decltype(math :: Add_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Add_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
constexpr auto Step < lambda, types ... > :: operator - (Step < lambda2, types2 ... > x) noexcept
{
  return Step < decltype(math :: Sub_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Sub_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
constexpr auto Step < lambda, types ... > :: operator * (Step < lambda2, types2 ... > x) noexcept
{
  return Step < decltype(math :: Mul_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Mul_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
constexpr auto Step < lambda, types ... > :: operator / (Step < lambda2, types2 ... > x) noexcept
{
  return Step < decltype(math :: Div_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Div_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
constexpr auto Step < lambda, types ... > :: operator == (Step < lambda2, types2 ... > x) noexcept
{
  return Step < decltype(math :: Eq_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Eq_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
constexpr auto Step < lambda, types ... > :: operator != (Step < lambda2, types2 ... > x) noexcept
{
  return Step < decltype(math :: NEq_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: NEq_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
constexpr auto Step < lambda, types ... > :: operator < (Step < lambda2, types2 ... > x) noexcept
{
  return Step < decltype(math :: Lower_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Lower_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename lambda2, typename ... types2 >
constexpr auto Step < lambda, types ... > :: operator > (Step < lambda2, types2 ... > x) noexcept
{
  return Step < decltype(math :: Greater_lambda), Step < lambda, types ... >, Step < lambda2, types2 ... > > (math :: Greater_lambda, *this, x);
}

// cas with inputvariable


template < typename lambda, typename ... types > template < typename type >
constexpr auto Step < lambda, types ... > :: operator + (InputVariable < type > x) noexcept
{
  return Step < decltype(math :: Add_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: Add_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
constexpr auto Step < lambda, types ... > :: operator - (InputVariable < type > x) noexcept
{
  return Step < decltype(math :: Sub_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: Sub_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
constexpr auto Step < lambda, types ... > :: operator * (InputVariable < type > x) noexcept
{
  return Step < decltype(math :: Mul_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: Mul_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
constexpr auto Step < lambda, types ... > :: operator / (InputVariable < type > x) noexcept
{
  return Step < decltype(math :: Div_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: Div_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
constexpr auto Step < lambda, types ... > :: operator == (InputVariable < type > x) noexcept
{
  return Step < decltype(math :: Eq_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: Eq_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
constexpr auto Step < lambda, types ... > :: operator != (InputVariable < type > x) noexcept
{
  return Step < decltype(math :: NEq_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: NEq_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
constexpr auto Step < lambda, types ... > :: operator < (InputVariable < type > x) noexcept
{
  return Step < decltype(math :: Lower_lambda), Step < lambda, types ... >, InputVariable < type > > (math :: Lower_lambda, *this, x);
}

template < typename lambda, typename ... types > template < typename type >
constexpr auto Step < lambda, types ... > :: operator > (InputVariable < type > x) noexcept
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

  template < typename ... types >
  constexpr Step < decltype(Mul_lambda), types ... > Mul (types ... args) noexcept
  {
    return Step < decltype(Mul_lambda), types ... >(Mul_lambda, args ...);
  }

  template < typename ... types >
  constexpr Step < decltype(Div_lambda), types ... > Div (types ... args) noexcept
  {
    return Step < decltype(Div_lambda), types ... >(Div_lambda, args ...);
  }

  template < typename ... types >
  constexpr Step < decltype(Eq_lambda), types ... > Eq (types ... args) noexcept
  {
    return Step < decltype(Eq_lambda), types ... >(Eq_lambda, args ...);
  }

  template < typename ... types >
  constexpr Step < decltype(NEq_lambda), types ... > NEq (types ... args) noexcept
  {
    return Step < decltype(NEq_lambda), types ... >(NEq_lambda, args ...);
  }

  template < typename ... types >
  constexpr Step < decltype(Greater_lambda), types ... > Greater (types ... args) noexcept
  {
    return Step < decltype(Greater_lambda), types ... >(Greater_lambda, args ...);
  }

  template < typename ... types >
  constexpr Step < decltype(Lower_lambda), types ... > Lower (types ... args) noexcept
  {
    return Step < decltype(Lower_lambda), types ... >(Lower_lambda, args ...);
  }

} // end namespace




#endif // __step_hpp__
