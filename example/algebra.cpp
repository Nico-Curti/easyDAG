/***************** ALGEBRA EXAMPLE *****************/
// Last update: 13/08/2020
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

#include <easyDAG.hpp>

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
  Task add_1(math :: Add_lambda, a, b);           // result __ x           ____ c
  Task add_2(math :: Add_lambda, c, d);           //           |          |
  Task mul(math :: Mul_lambda, add_1, add_2);     //           |___ add_2 +
                                                  //                      |____ d
  std :: cout << mul << std :: endl;              //

  mul.eval();

  auto result = mul ();
  assert ( result == 21.f );

  std :: cout << result << std :: endl;

  return 0;
}
