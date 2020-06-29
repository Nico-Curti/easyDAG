/***************** CONDITION EXAMPLE ***************/
// Last update: 29/06/2020
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

#include <task.hpp>

#include <cassert>
#include <iostream>


int main ()
{
  int cnt = 0;

  // this is a blank DAG variable
  auto counter = InputVariable < int >();

  // now you can fill the variable with cnt
  counter.set(cnt);

  auto increment = [&](int counter)
                   {
                     std :: cout << "I'm the incrementer" << std :: endl;
                     ++ cnt;
                     counter = cnt; // just to avoid the compiler warning
                     return counter;
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

  auto result = [](bool check, int counter)
                {
                  if ( check )
                    std :: cout << "Counter equal to " << counter << std :: endl;
                };

  Task increment_step(increment, counter);
  Task check_step(condition, counter);

  while ( ! check_step () )
  {
    // you cannot use set if there are other steps! (a step is not copyable)
    Task result_step(result, check_step, counter);

    // evaluate the step
    result_step();

    // update the DAG with the new value of counter
    counter.set(cnt);

    // now we need to update the two steps which depend to counter
    // and (moreover) re-run their execution.
    // You can obtain both functionality using the set member function
    increment_step.set(counter);
    check_step.set(counter);
  }

  return 0;
}
