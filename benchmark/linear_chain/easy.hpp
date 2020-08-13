#include <linear_chain.h>
#include <easyDAG.hpp>


template < std :: size_t length >
void linear_chain_task ()
{
  std :: size_t counter = 0;

  auto fill = [&](const std :: size_t & cnt)
              {
                ++counter;
                return cnt + 1;
              };


  auto var = InputVariable(counter); // it must be a step otherwise a inputvariable-task is not valuable
  NTask < length, decltype(fill), decltype(var) > fill_task(fill, var);

  fill_task.eval();
  fill_task();

  // in release the asserts are turned off
  if ( counter != length )
  {
    std :: cerr << "Error easyDAG: " << counter << " vs " << length << std :: endl;
    std :: exit(1);
  }
}
