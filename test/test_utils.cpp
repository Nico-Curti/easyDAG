#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <step.hpp>


TEST_CASE ( "Test is_type", "[is_type]" )
{
  float x = 2.f;
  int y = 2;
  auto a = InputVariable(x);
  auto b = InputVariable < decltype(y) > ();

  auto sum1 = a + b;

  REQUIRE ( utils :: is_variable < decltype(x)    >() == true);
  REQUIRE ( utils :: is_variable < decltype(a)    >() == true);
  REQUIRE ( utils :: is_variable < decltype(b)    >() == true);
  REQUIRE ( utils :: is_variable < decltype(sum1) >() == false);
  REQUIRE ( utils :: is_step     < decltype(x)    >() == false);
  REQUIRE ( utils :: is_step     < decltype(a)    >() == false);
  REQUIRE ( utils :: is_step     < decltype(b)    >() == false);
  REQUIRE ( utils :: is_step     < decltype(sum1) >() == true);

}

TEST_CASE ( "Test operation_counting", "[count_op]" )
{
  float x1  = 10.f;
  double x2 = 2.;

  float y1 = 3.f;
  float y2 = 4.f;

  auto a = InputVariable(x1);
  auto b = InputVariable(x2);
  auto c = InputVariable(y1);
  auto d = InputVariable(y2);

  auto sum_1 = (a * b) + (c + d) + x1;

  auto cnt = utils :: OperationCount < decltype(sum_1) >();

  REQUIRE ( cnt.num_variables  == 5 );
  REQUIRE ( cnt.num_operations == 4 );
  REQUIRE ( cnt.num_nodes      == 9 );
}
