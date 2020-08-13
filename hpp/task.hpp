#ifndef __task_hpp__
#define __task_hpp__

#include <task.h>

template < typename lambda, typename ... types >
Task < lambda, types ... > :: Task (lambda & func, types & ... args) : Step < lambda, types ... >(func, args ...)
{
}

template < typename lambda, typename ... types >
constexpr void Task < lambda, types ... > :: set (types & ... args) noexcept
{
  this->args = std :: tuple < types ... >(args ... );
}

template < typename lambda, typename ... types >
constexpr decltype(auto) Task < lambda, types ... > :: operator () () noexcept
{
  if (this->is_valuable())
    return this->value.get();
  else
  {
    std :: cerr << "The current task is not valuable yet" << std :: endl;
    std :: exit(1);
    return this->value.get();
  }
}

template < typename lambda, typename ... types > template < std :: size_t idx >
constexpr void Task < lambda, types ... > :: eval_impl () noexcept
{
  if constexpr (idx + 1 < sizeof ... (types))
    this->eval_impl < idx + 1 > ();

  using idx_t = utils :: nth_type_of < idx, types ... >;

  if constexpr ( utils :: is_step < idx_t > :: value ) // it is a step
    return std :: get < idx >(this->args).eval ();

  //else if constexpr ( utils :: is_variable < idx_t > :: value ) // it is a variable
  //  return;
}

template < typename lambda, typename ... types >
constexpr void Task < lambda, types ... > :: eval () noexcept
{
  this->eval_impl < 0 >();
  this->value = std :: async ( std :: launch :: async, & Step < lambda, types ... > :: operator (), this );
}

template < typename lambda, typename ... types >
constexpr bool Task < lambda, types ... > :: is_valuable () noexcept
{
  return this->value.valid();
}

template < typename lambda, typename ... types > template < std :: size_t indent, std :: size_t idx >
constexpr void Task < lambda, types ... > :: graph_impl (std :: ostream & os) noexcept
{
  if constexpr (idx + 1 < sizeof ... (types))
    graph_impl < indent, idx + 1 > (os);

  using idx_t = utils :: nth_type_of < idx, types ... >;

  if constexpr ( utils :: is_step < idx_t > :: value ) // it is a step
    std :: get < idx >(this->args).template graph < indent + 2 >(os);

  else if constexpr ( utils :: is_variable < idx_t > :: value ) // it is a variable
    os << std :: string(indent, ' ') << std :: get < idx >(this->args).get_name() << " [variable]" << std :: endl;
}

template < typename lambda, typename ... types > template < std :: size_t indent >
constexpr void Task < lambda, types ... > :: graph (std :: ostream & os) noexcept
{
  auto cnt = utils :: OperationCount < Step < lambda, types ... > >();
  os << std :: string(indent, ' ') << this->_name << " [" << cnt.num_variables << " # variables, " << cnt.num_operations << " # operations]" << std :: endl;

  this->graph_impl < indent + 2, 0 >(os);
}

template < typename lambda, typename ... types >
constexpr Task < lambda, types ... > make_task (lambda & func, types ... args) noexcept
{
  return Task < lambda, types ... >(func, args ...);
}


#endif // __task_hpp__
