/***************** GRAPHVIZ EXAMPLE ***************/
// Last update: 29/06/2020
//
// In this example we show how you can use easyDAG to
// visualize your DAG scheme using DOT.
// We set a name to each step (the default value is
// just "Task").
// In the example we create two vectors starting
// from just a dimension size; we fill the two
// vectors; we concatenate them and we apply a
// sum reduction.
// The DAG is written in the stdout in the DOT
// format so if you want to visualize the png
// you can re-direct the stdout to a file and
// use the command:
// $> dot -Tpng graph.dot > output.png
//
/***************************************************/

#include <task.hpp>

#include <numeric>
#include <cassert>
#include <iostream>
#include <algorithm>


int main ()
{
  const int N = 10;
  const std :: string pipeline_name = "pipeline";

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

  auto size = InputVariable(N);
  size.set_name(size);

  Task init_x(init, size);
  Task init_y(init, size);

  init_x.set_name(init_x);
  init_y.set_name(init_y);

  Task fill_x(fill, init_x);
  Task fill_y(fill, init_y);

  fill_x.set_name(fill_x);
  fill_y.set_name(fill_y);

  Task concatenate(concat, fill_x, fill_y);
  concatenate.set_name(concatenate);

  Task reduction(reduce, concatenate);
  reduction.set_name(reduction);

  reduction.graphviz(std :: cout, pipeline_name);

  assert ( reduction() == N * 2 );

  return 0;
}
