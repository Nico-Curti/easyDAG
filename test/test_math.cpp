#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <step.hpp>


TEST_CASE ( "Test get variable", "[get]" )
{
  float x = 3.14f;
  float y = 42.f;

  InputVariable a(x);
  InputVariable < decltype(y) > b;

  b.set(y);

  REQUIRE ( a() == x );
  REQUIRE ( b() == y );
}


TEST_CASE ( "Test set variable", "[set]" )
{
  float x = 3.14f;
  float y = 42.f;

  InputVariable a(x);
  REQUIRE (a() == x);

  a.set(y);
  REQUIRE ( a() == y );
}


TEST_CASE ( "Test simple step", "[step]" )
{
  auto lambda = [](const float & var){return var * 2.f;};
  float x = 3.14f;

  Step Double(lambda, x);

  REQUIRE ( Double() == x * 2.f );
}


TEST_CASE ( "Test add step", "[add]" )
{
  float x = 3.14f;
  float y = 42.f;

  InputVariable a(x);
  InputVariable b(y);

  Step add(math :: Add_lambda, a, b);

  REQUIRE ( add() == 45.14f );
}


TEST_CASE ( "Test add & mul step", "[add_mul]" )
{
  float x1 = 1.f;
  float x2 = 2.f;

  float y1 = 3.f;
  float y2 = 4.f;

  InputVariable a(x1);
  InputVariable b(x2);
  InputVariable c(y1);
  InputVariable d(y2);

  auto add_lambda = [](const auto & x, const auto & y) {return x + y;};
  auto mul_lambda = [](const auto & x, const auto & y) {return x * y;};

  Step add_1(add_lambda, a, b);
  Step add_2(add_lambda, c, d);
  Step mul_1(mul_lambda, add_1, add_2);

  REQUIRE ( mul_1() == 21.f );
}


TEST_CASE ( "Test CAS add & mul step", "[cas_add_mul]" )
{
  float x1 = 1.f;
  double x2 = 2.;

  float y1 = 2.f;
  float y2 = 4.f;

  InputVariable a(x1);
  InputVariable b(x2);
  InputVariable c(y1);
  InputVariable d(y2);

  auto mul_1 = a * d;
  auto mul_2 = b * c;
  auto sum_1 = mul_1 + mul_2;

  REQUIRE ( sum_1() == 8.f );
}


TEST_CASE ( "Test CAS add & mul operator", "[cas_operator]" )
{
  float x1 = 1.f;
  double x2 = 2.;

  float y1 = 2.f;
  float y2 = 4.f;

  InputVariable a(x1);
  InputVariable b(x2);
  InputVariable c(y1);
  InputVariable d(y2);

  auto sum_1 = (a * d) + (b * c);

  REQUIRE ( sum_1() == 8.f );
}


TEST_CASE ( "Test CAS add & mul operators", "[cas_operators]" )
{
  float x1 = 1.f;
  double x2 = 2.;

  float y1 = 2.f;
  float y2 = 4.f;

  InputVariable a(x1);
  InputVariable b(x2);
  InputVariable c(y1);
  InputVariable d(y2);

  auto sum_1 = a + d + b + c;

  REQUIRE ( sum_1() == 9.f );
}


TEST_CASE ( "Test step alias", "[alias]" )
{
  float x1 = 1.f;
  double x2 = 2.;

  float y1 = 2.f;
  float y2 = 4.f;

  InputVariable a(x1);
  InputVariable b(x2);
  InputVariable c(y1);
  InputVariable d(y2);

  auto sum_1 = math :: Sum(a, d, b, c);

  REQUIRE ( sum_1() == 9.f );
}
