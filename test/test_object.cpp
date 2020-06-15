#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <step.hpp>
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

  Step init_step_1(init, a);
  Step init_step_2(init, a);

  Step fill_step_1(fill, init_step_1);
  Step fill_step_2(fill, init_step_2);

  Step concatenate(concat, fill_step_1, fill_step_2);

  Step reduction(reduce, concatenate);

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

  Step init_step(init, a);
  Step fill_step(fill, init_step);
  Step sum_step(sum, fill_step);

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

  Step init_step(init, a);
  Step fill_step(fill, init_step);
  Step sum_step(sum, fill_step);

  auto res = sum_step();

  REQUIRE ( res == N );
}
