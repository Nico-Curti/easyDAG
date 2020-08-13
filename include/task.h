#ifndef __task_h__
#define __task_h__

#include <step.hpp>

#include <future>
#include <utility>

// class specialization with async tasks
template < typename lambda, typename ... types >
class Task : public Step < lambda, types ... >
{

  // Private members

protected:

  // Protected members

  using eval_t = typename std :: result_of < decltype(& Step < lambda, types ... > :: operator ())( Step < lambda, types ... > ) > :: type;

  template < std :: size_t idx >
  constexpr void eval_impl () noexcept;

  template < std :: size_t indent, std :: size_t idx >
  constexpr void graph_impl (std :: ostream & os) noexcept;

  // with a shared_future the value is automatically cached
  std :: shared_future < eval_t > value;

public:

  // Constructor

  Task (lambda & func, types & ... args);

  // setter function

  constexpr void set (types & ... args) noexcept;

  // eval method

  constexpr decltype(auto) operator () () noexcept;
  constexpr void eval () noexcept;

  constexpr bool is_valuable () noexcept;

  // IO operator

  template < std :: size_t indent = 0 >
  constexpr void graph (std :: ostream & os) noexcept;

};

// This is the CTAD workaround for std <= 14
template < typename lambda, typename ... types >
constexpr Task < lambda, types ... > make_task (lambda & func, types ... args) noexcept;

#endif // __task_h__
