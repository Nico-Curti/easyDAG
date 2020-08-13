/***************** TIMER EXAMPLE ******************/
// Last update: 13/08/2020
//
// In this example we show how you can use easyDAG to
// inherit from the Task class obtaining an object able
// to monitor the evaluation time of each step
//
/***************************************************/

#include <easyDAG.hpp>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>

// class inheritance for time evaluation
template < typename lambda, typename ... types >
class Monitor : public Task < lambda, types ...>
{
  std :: chrono :: system_clock :: time_point tic;
  std :: chrono :: system_clock :: time_point toc;

  using Task < lambda, types ... > :: operator();
  using Task < lambda, types ... > :: set;

  decltype(auto) print_time (const std :: chrono :: system_clock :: time_point & t)
  {
    std :: time_t now = std :: chrono :: system_clock :: to_time_t(t);
    std :: tm tm = * std :: gmtime(&now); //GMT (UTC)
    // std :: tm tm = * std :: localtime(&now); //Locale time-zone, usually UTC by default.
    std :: stringstream ss;
    ss << std :: put_time( &tm, "%Y-%m-%d %H:%M:%S" );
    return ss.str();
  }

public:

  // Constructor

  Monitor (lambda & func, types & ... args) : Task < lambda, types ... >(func, args ...),
                                              tic ( std :: chrono :: system_clock :: now () ), toc ( std :: chrono :: system_clock :: now () )
  {
  }

  constexpr decltype(auto) operator () () noexcept
  {
    auto res = Task < lambda, types ... > :: operator ()();
    toc = std :: chrono :: system_clock :: now ();
    return res;
  }

  constexpr void set (types & ... args) noexcept
  {
    tic = std :: chrono :: system_clock :: now ();
    Task < lambda, types ... > :: set (args ...);
  }

  template < class TimeT = std :: chrono :: milliseconds >
  constexpr decltype(auto) elapsed () noexcept
  {
    return std :: chrono :: duration_cast < TimeT >(toc - tic).count();
  }

  template < std :: size_t indent = 0 >
  constexpr void graph (std :: ostream & os) noexcept
  {
    auto cnt = utils :: OperationCount < Monitor < lambda, types ... > >();
    os << std :: string(indent, ' ') << this->_name << " [" << cnt.num_variables << " # variables, " << cnt.num_operations << " # operations, "
       << "start_time: " << print_time(tic) << ", "
       << "end_time: " << print_time(toc)
       << "]" << std :: endl;

    Task < lambda, types ... > :: template graph_impl < indent + 2, 0 > (os);
  }

};






int main ()
{
  float x1 = 1.f;
  float x2 = 2.f;

  float y1 = 3.f;
  float y2 = 4.f;

  auto add_lambda = [](const auto & x, const auto & y)
                    {
                      std :: this_thread :: sleep_for(std :: chrono :: seconds(2));
                      return x + y;
                    };
  auto mul_lambda = [](const auto & x, const auto & y)
                    {
                      std :: this_thread :: sleep_for(std :: chrono :: seconds(2));
                      return x * y;
                    };

  auto a = InputVariable(x1);
  a.set_name(a);
  auto b = InputVariable(x2);
  b.set_name(b);
  auto c = InputVariable(y1);
  c.set_name(c);
  auto d = InputVariable(y2);
  d.set_name(d);

  Monitor add_1(add_lambda, a, b);
  add_1.set_name(add_1);
  Monitor add_2(add_lambda, c, d);
  add_2.set_name(add_2);
  Monitor mul(mul_lambda, add_1, add_2);
  mul.set_name(mul);

  mul.eval();

  std :: cout << "Result: " << mul() << std :: endl;
  std :: cout << "Elapsed time: " << mul.elapsed() << " ms" << std :: endl;

  mul.graph (std :: cout);
}
