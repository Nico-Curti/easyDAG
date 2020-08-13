#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <easyDAG.hpp>
#include <vector>
#include <algorithm>
#include <numeric>

TEST_CASE ( "Test vector concat-reduce", "[vector]" )
{
  const int N = 10;

  auto init = [](const int & N) -> std :: vector < float >
              {
                std :: vector < float > x(N);
                return x;
              };

  auto fill = [](std :: vector < float > x) -> std :: vector < float >
              {
                std :: fill(x.begin(), x.end(), 1.f);
                return x;
              };

  auto concat = [](std :: vector < float > x, std :: vector < float > y)
                {
                  std :: vector < float > res(x.size() + y.size());
                  std :: copy_n(x.begin(), x.size(), res.begin());
                  std :: copy_n(y.begin(), y.size(), res.begin() + x.size());
                  return res;
                };

  auto reduce = [](std :: vector < float > res)
                  {
                    return std :: accumulate(res.begin(), res.end(), 0.f);
                  };

  auto a = InputVariable(N);

  Task init_step_1(init, a);
  Task init_step_2(init, a);

  Task fill_step_1(fill, init_step_1);
  Task fill_step_2(fill, init_step_2);

  Task concatenate(concat, fill_step_1, fill_step_2);

  Task reduction(reduce, concatenate);
  reduction.eval();

  REQUIRE ( reduction() == N * 2 );
}


TEST_CASE ( "Test vector init-reduce", "[vector-init]" )
{
  const int N = 10;
  std :: vector < float > x;

  auto init = [](const int & N) -> std :: vector < float >
              {
                std :: vector < float > x(N);
                return x;
              };
  auto fill = [](std :: vector < float > x) -> std :: vector < float >
              {
                std :: fill(x.begin(), x.end(), 1.f);
                return x;
              };
  auto sum  = [](const std :: vector < float > & x)
              {
                return std :: accumulate(x.begin(), x.end(), 0.f);
              };

  auto a = InputVariable(N);

  Task init_step(init, a);
  Task fill_step(fill, init_step);
  Task sum_step(sum, fill_step);
  sum_step.eval();

  auto res = sum_step();

  REQUIRE ( res == N );
}


TEST_CASE ( "Test pointer init-reduce", "[pointer-init]" )
{
  const int N = 10;

  auto init = [&](const int & N)
              {
                float * x = new float[N];
                return x;
              };
  auto fill = [&](float * x)
              {
                std :: fill_n(x, N, 1.f);
                return x;
              };
  auto sum  = [&](float * x)
              {
                return std :: accumulate(x, x + N, 0.f);
              };

  auto a = InputVariable(N);

  Task init_step(init, a);
  Task fill_step(fill, init_step);
  Task sum_step(sum, fill_step);
  sum_step.eval();

  auto res = sum_step();

  REQUIRE ( res == N );
}


TEST_CASE ( "Test n-task dot", "[n-task-dot]" )
{
  constexpr std :: size_t length = 5;
  std :: size_t idx = -1;

  float * x = new float[length];
  float * y = new float[length];

  std :: iota(x, x + length, 1.f);
  std :: iota(y, y + length, 1.f);

  auto dot = [&](float * x, float * y)
             {
               ++idx;
               return x[idx] * y[idx];
             };

  NTask < length, decltype(dot), decltype(x), decltype(y) > prod (dot, x, y);

  using tuple_type = typename decltype(prod) :: res_tuple_type;

  prod.eval();
  auto res = prod();

  static_assert(std :: is_same_v < tuple_type, std :: tuple < float, float, float, float, float > >, "It is a 5-float-tuple");

  REQUIRE ( std :: get < 0 >(res) == 1.f );
  REQUIRE ( std :: get < 1 >(res) == 4.f );
  REQUIRE ( std :: get < 2 >(res) == 9.f );
  REQUIRE ( std :: get < 3 >(res) == 16.f );
  REQUIRE ( std :: get < 4 >(res) == 25.f );
}
