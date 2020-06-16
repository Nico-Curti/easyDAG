#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <sstream>

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

TEST_CASE ( "Test operation_name", "[name_op]" )
{
  float x1 = 1.f;
  float x2 = 2.f;

  float y1 = 3.f;
  float y2 = 4.f;

  auto a = InputVariable(x1);
  auto b = InputVariable(x2);
  auto c = InputVariable(y1);
  auto d = InputVariable(y2);

  a.set_name(a);
  b.set_name(b);
  c.set_name(c);
  d.set_name(d);

  Step add_1(math :: Add_lambda, a, b);
  add_1.set_name(add_1);

  Step add_2(math :: Add_lambda, c, d, a);
  add_2.set_name(add_2);

  Step mul_1(math :: Mul_lambda, add_1, add_2);
  mul_1.set_name(mul_1);

  REQUIRE ( mul_1.get_name() == "mul_1" );
  REQUIRE ( add_1.get_name() == "add_1" );
  REQUIRE ( a.get_name()     == "a" );
  REQUIRE ( b.get_name()     == "b" );
}

TEST_CASE ( "Test operation_cout", "[cout_op]" )
{
  float x1 = 1.f;
  float x2 = 2.f;

  float y1 = 3.f;
  float y2 = 4.f;

  auto a = InputVariable(x1);
  auto b = InputVariable(x2);
  auto c = InputVariable(y1);
  auto d = InputVariable(y2);

  a.set_name(a);
  b.set_name(b);
  c.set_name(c);
  d.set_name(d);

  Step add_1(math :: Add_lambda, a, b);
  add_1.set_name(add_1);

  Step add_2(math :: Add_lambda, c, d, a);
  add_2.set_name(add_2);

  Step mul_1(math :: Mul_lambda, add_1, add_2);
  mul_1.set_name(mul_1);

  std :: stringstream os;
  os << mul_1;

  REQUIRE ( os.str() == "mul_1 ( add_2 ( a ( 1 ) + d ( 4 ) + c ( 3 ) ) * add_1 ( b ( 2 ) + a ( 1 ) ) )" );
}

TEST_CASE ( "Test operation_cout_no_symbol", "[cout_op_no_symbol]" )
{
  float x1 = 1.f;
  float x2 = 2.f;

  float y1 = 3.f;
  float y2 = 4.f;

  auto a = InputVariable(x1);
  auto b = InputVariable(x2);
  auto c = InputVariable(y1);
  auto d = InputVariable(y2);

  a.set_name(a);
  b.set_name(b);
  c.set_name(c);
  d.set_name(d);

  auto add_lambda = [](auto x1, auto x2){return x1 + x2;};
  auto mul_lambda = [](auto x1, auto x2){return x1 * x2;};

  Step add_1(add_lambda, a, b);
  add_1.set_name(add_1);

  Step add_2(add_lambda, c, d);
  add_2.set_name(add_2);

  Step mul_1(mul_lambda, add_1, add_2);
  mul_1.set_name(mul_1);

  std :: stringstream os;
  os << mul_1;

  REQUIRE ( os.str() == "mul_1 ( add_2 ( d ( 4 )   c ( 3 ) )   add_1 ( b ( 2 )   a ( 1 ) ) )" );
}

TEST_CASE ( "Test operation_graph", "[graph_op]" )
{
  float x1 = 1.f;
  float x2 = 2.f;

  float y1 = 3.f;
  float y2 = 4.f;

  auto a = InputVariable(x1);
  auto b = InputVariable(x2);
  auto c = InputVariable(y1);
  auto d = InputVariable(y2);

  a.set_name(a);
  b.set_name(b);
  c.set_name(c);
  d.set_name(d);

  Step add_1(math :: Add_lambda, a, b);
  add_1.set_name(add_1);

  Step add_2(math :: Add_lambda, c, d, a);
  add_2.set_name(add_2);

  Step mul_1(math :: Mul_lambda, add_1, add_2);
  mul_1.set_name(mul_1);

  std :: stringstream os;
  mul_1.graph(os, "pipeline");

  std :: string true_pipe = "digraph pipeline {\n\
  mul_1[shape=box, style=filled,color=\".7 .3 1.0\"]\n\
  mul_1 -> add_2\n\
  add_2[shape=box, style=filled,color=\".7 .3 1.0\"]\n\
  add_2 -> a\n\
  add_2 -> d\n\
  add_2 -> c\n\
  mul_1 -> add_1\n\
  add_1[shape=box, style=filled,color=\".7 .3 1.0\"]\n\
  add_1 -> b\n\
  add_1 -> a\n\
}\n";

  REQUIRE ( os.str() == true_pipe );
}
