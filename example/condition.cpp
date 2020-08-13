/***************** CONDITION EXAMPLE ***************/
// Last update: 13/08/2020
//
// In this example we use a condition to update the
// DAG variables.
// Loop are not allowed in a DAG scheme so we have
// to use a standard while loop along the steps,
// updating the sensible variables during the iterations.
//
// Pay attention! Step variables are not copyable, so
// it you need to update deep dependencies you have to
// re-create the step.
//
/***************************************************/

#include <easyDAG.hpp>

#include <cassert>
#include <iostream>


int main ()
{
  int cnt = 0;
  auto counter = InputVariable (cnt);

  auto increment = [](int counter)
                   {
                     std :: cout << "I'm the incrementer" << std :: endl;
                     return counter + 1;
                   };

  auto condition = [](int counter)
                   {
                     if ( counter == 5 )
                     {
                       std :: cout << "condition reached" << std :: endl;
                       return 1;
                     }

                     std :: cout << "loop again (counter = " << counter << ")" << std :: endl;
                     return 0;
                   };

  Task increment_step(increment, counter);
  Task check_step(condition, counter);

  // evaluate the check step
  check_step.eval();

  while ( ! check_step () )
  {
    // evaluate the incremental step
    increment_step.eval();
    cnt = increment_step();

    // update the DAG with the new value of counter
    counter.set(cnt);
    increment_step.set(counter);
    check_step.set(counter);

    // evaluate the check step for future use
    check_step.eval();
  }

  return 0;
}
