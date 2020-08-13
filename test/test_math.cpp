#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <easyDAG.hpp>


TEST_CASE ( "Test get variable", "[get]" )
{
  float x = 3.14f;
  float y = 42.f;

  auto a = InputVariable(x);
  auto b = InputVariable < decltype(y) > ();

  b.set(y);

  REQUIRE ( a() == x );
  REQUIRE ( b() == y );
}


TEST_CASE ( "Test set variable", "[set]" )
{
  float x = 3.14f;
  float y = 42.f;

  auto a = InputVariable(x);
  REQUIRE (a() == x);

  a.set(y);
  REQUIRE ( a() == y );
}


TEST_CASE ( "Test simple step", "[step]" )
{
  auto lambda = [](const float & var){return var * 2.f;};

  float x = 3.14f;

  Task Double(lambda, x);
  Double.eval();

  REQUIRE ( Double() == x * 2.f );
}

TEST_CASE ( "Test not valuable step", "[step]" )
{
  auto lambda = [](const float & var){return var * 2.f;};

  float x = 3.14f;

  Task Double(lambda, x);

  REQUIRE ( Double.is_valuable() == false );
}

TEST_CASE ( "Test add step", "[add]" )
{
  float x = 3.14f;
  float y = 42.f;

  auto a = InputVariable(x);
  auto b = InputVariable(y);

  Task add(math :: Add_lambda, a, b);
  add.eval();

  REQUIRE ( add() == 45.14f );
}

TEST_CASE ( "Test add step set", "[add_set]" )
{
  float x = 3.14f;
  float y = 42.f;

  auto a = InputVariable < decltype(x) >();
  auto b = InputVariable < decltype(y) >();

  a.set(x);
  b.set(y);

  Task add(math :: Add_lambda, a, b);
  add.eval();

  REQUIRE ( a()   == x );
  REQUIRE ( b()   == y );
  REQUIRE ( add() == 45.14f );

  // set do not modify the add
  x *= 2.f;
  y *= 2.f;
  a.set(x);
  b.set(y);

  REQUIRE ( a()   == x );
  REQUIRE ( b()   == y );
  REQUIRE ( add() == 45.14f );
}

TEST_CASE ( "Test add & mul step", "[add_mul]" )
{
  float x1 = 1.f;
  float x2 = 2.f;

  float y1 = 3.f;
  float y2 = 4.f;

  auto a = InputVariable(x1);
  auto b = InputVariable(x2);
  auto c = InputVariable(y1);
  auto d = InputVariable(y2);

  Task add_1(math :: Add_lambda, a, b);
  Task add_2(math :: Add_lambda, c, d);
  Task mul_1(math :: Mul_lambda, add_1, add_2);
  mul_1.eval();

  REQUIRE ( mul_1() == 21.f );
}


TEST_CASE ( "Test add & mul step num_variables", "[add_mul_num_variables]" )
{
  float x1 = 1.f;
  float x2 = 2.f;

  float y1 = 3.f;
  float y2 = 4.f;

  auto a = InputVariable(x1);
  auto b = InputVariable(x2);
  auto c = InputVariable(y1);
  auto d = InputVariable(y2);

  Task add_1(math :: Add_lambda, a, b);
  Task add_2(math :: Add_lambda, c, d);
  Task mul_1(math :: Mul_lambda, add_1, add_2);

  REQUIRE ( utils :: num_variables < decltype(add_1) > :: value == 2 );
  REQUIRE ( utils :: num_variables < decltype(add_2) > :: value == 2 );
  REQUIRE ( utils :: num_variables < decltype(mul_1) > :: value == 4 );

  REQUIRE ( utils :: num_operations < decltype(add_1) > :: value == 1 );
  REQUIRE ( utils :: num_operations < decltype(add_2) > :: value == 1 );
  REQUIRE ( utils :: num_operations < decltype(mul_1) > :: value == 3 );

  REQUIRE ( utils :: dag_size < decltype(add_1) > :: value == 3 );
  REQUIRE ( utils :: dag_size < decltype(add_2) > :: value == 3 );
  REQUIRE ( utils :: dag_size < decltype(mul_1) > :: value == 7 );
}


TEST_CASE ( "Test CAS add & mul step", "[cas_add_mul]" )
{
  float x1 = 1.f;
  double x2 = 2.;

  float y1 = 2.f;
  float y2 = 4.f;

  auto a = InputVariable(x1);
  auto b = InputVariable(x2);
  auto c = InputVariable(y1);
  auto d = InputVariable(y2);

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

  auto a = InputVariable(x1);
  auto b = InputVariable(x2);
  auto c = InputVariable(y1);
  auto d = InputVariable(y2);

  auto sum_1 = (a * d) + (b * c);

  REQUIRE ( sum_1() == 8.f );
}


TEST_CASE ( "Test CAS add & mul operators", "[cas_operators]" )
{
  float x1 = 1.f;
  double x2 = 2.;

  float y1 = 2.f;
  float y2 = 4.f;

  auto a = InputVariable(x1);
  auto b = InputVariable(x2);
  auto c = InputVariable(y1);
  auto d = InputVariable(y2);

  auto sum_1 = a + d + b + c;

  REQUIRE ( sum_1() == 9.f );
}


TEST_CASE ( "Test step alias", "[alias]" )
{
  float x1 = 1.f;
  double x2 = 2.;

  float y1 = 2.f;
  float y2 = 4.f;

  auto a = InputVariable(x1);
  auto b = InputVariable(x2);
  auto c = InputVariable(y1);
  auto d = InputVariable(y2);

  auto sum_1 = math :: Sum(a, d, b, c);

  REQUIRE ( sum_1() == 9.f );
}
