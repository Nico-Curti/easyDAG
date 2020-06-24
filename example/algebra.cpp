/***************** ALGEBRA EXAMPLE *****************/
// Last update: 15/06/2020
//
// In this example we show how you can use easyDAG to
// perform a simple math operation.
// The DAG is automatically evaluated using the template
// recursion of the Step object.
// The result evaluation is performed asynchronously
// using future variables (in this case is useless
// this kind of optimization!).
// A full list of default lambda math-functions is
// provided in the math.hpp file.
//
/***************************************************/

#include <step.hpp>

#include <cassert>
#include <iostream>


int main ()
{
  float x1 = 1.f;
  float x2 = 2.f;

  float y1 = 3.f;
  float y2 = 4.f;

  auto a = InputVariable(x1);                     //                       ____ a
  auto b = InputVariable(x2);                     //                      |
  auto c = InputVariable(y1);                     //            ___ add_1 +
  auto d = InputVariable(y2);                     //           |          |____ b
                                                  //           |
  Step add_1(math :: Add_lambda, a, b);           // result __ x           ____ c
  Step add_2(math :: Add_lambda, c, d);           //           |          |
  Step mul_1(math :: Mul_lambda, add_1, add_2);   //           |___ add_2 +
                                                  //                      |____ d
  std :: cout << mul_1 << std :: endl;            //

  auto result = mul_1 ();
  assert ( result == 21.f );

  std :: cout << result << std :: endl;

  return 0;
}
