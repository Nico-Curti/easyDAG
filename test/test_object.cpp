#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <step.hpp>
#include <vector>
#include <algorithm>
#include <numeric>

TEST_CASE ( "Test vector concat-reduce", "[vector]" )
{
  std :: vector < float > x1(10);
  std :: vector < float > x2(10);

  std :: iota(x1.begin(), x1.end(), 0.f);
  std :: iota(x2.begin(), x2.end(), 0.f);

  auto concat = [](const std :: vector < float > & x, const std :: vector < float > & y)
                {
                  std :: vector < float > res(x.size() + y.size());
                  std :: copy_n(x.begin(), x.size(), res.begin());
                  std :: copy_n(y.begin(), y.size(), res.begin() + x.size());
                  return res;
                };

  auto reduce = [](const std :: vector < float > & res)
                  {
                    return std :: accumulate(res.begin(), res.end(), 0.f);
                  };

  auto a = InputVariable(x1);
  auto b = InputVariable(x2);

  Step concatenate(concat, a, b);
  Step reduction(reduce, concatenate);

  REQUIRE ( reduction() == 90.f );
}
