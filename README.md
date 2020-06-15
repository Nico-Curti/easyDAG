| **Authors**  | **Project** | **Build Status** | **Code Quality** |
|:------------:|:-----------:|:----------------:|:----------------:|
| [**N. Curti**](https://github.com/Nico-Curti) <br/> [**E. Giampieri**](https://github.com/EnricoGiampieri)   |  **easyDAG**  | **Linux/MacOS** : [![travis](https://travis-ci.com/Nico-Curti/easyDAG.svg?branch=master)](https://travis-ci.com/Nico-Curti/easyDAG) <br/> **Windows** : [![appveyor](https://ci.appveyor.com/api/projects/status/exx9gbp6blyggdmg?svg=true)](https://ci.appveyor.com/project/Nico-Curti/easydag) | **Codacy** : [![Codacy](https://api.codacy.com/project/badge/Grade/8d261e840f664c5fa9bf3e1c09509085)](https://www.codacy.com/manual/Nico-Curti/easyDAG?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Nico-Curti/easyDAG&amp;utm_campaign=Badge_Grade) |

![easyDAG CI](https://github.com/Nico-Curti/easyDAG/workflows/easyDAG%20CI/badge.svg)

[![GitHub pull-requests](https://img.shields.io/github/issues-pr/Nico-Curti/easyDAG.svg?style=plastic)](https://github.com/Nico-Curti/easyDAG/pulls)
[![GitHub issues](https://img.shields.io/github/issues/Nico-Curti/easyDAG.svg?style=plastic)](https://github.com/Nico-Curti/easyDAG/issues)

[![GitHub stars](https://img.shields.io/github/stars/Nico-Curti/easyDAG.svg?label=Stars&style=social)](https://github.com/Nico-Curti/easyDAG/stargazers)
[![GitHub watchers](https://img.shields.io/github/watchers/Nico-Curti/easyDAG.svg?label=Watch&style=social)](https://github.com/Nico-Curti/easyDAG/watchers)

![gcc version](https://img.shields.io/badge/gcc-%207.*%20|%208.*%20|%209.*-yellow.svg)

![clang version](https://img.shields.io/badge/clang-5.*%20|%206.*%20|%207.*%20|-red.svg)

![msvc version](https://img.shields.io/badge/msvc-vs2017%20x86%20|%20vs2017%20x64-blue.svg)

# easy Direct Acyclic Graph Scheduler

Modern C++ parallel scheduler. This project is the optimization and extension of the original [easyDAG](https://github.com/eDIMESLab/easyDAG) project in Python.

* [Prerequisites](#prerequisites)
* [Installation](#installation)
* [Usage](#usage)
* [Testing](#testing)
* [Contribution](#contribution)
* [References](#references)
* [Authors](#authors)
* [License](#license)
* [Acknowledgments](#acknowledgments)
* [Citation](#citation)

## Prerequisites

The `easyDAG` project is written in `C++` using a large amount of **c++17** features.
The package installation can be performed via [`CMake`](https://github.com/Nico-Curti/easyDAG/blob/master/CMakeLists.txt).

## Installation

1) Follow your system prerequisites (below)

2) Clone the `easyDAG` package from this repository, or download a stable release

```bash
git clone https://github.com/Nico-Curti/easyDAG.git
cd easyDAG
```

3) `easyDAG` could be built with CMake and Make or with the *build* scripts in the project.
Example:

**Unix OS:**
```bash
./build.sh
```

**Windows OS:**
```Powershell
PS \>                 ./build.ps1
```

### Ubuntu

1) Define a work folder, which we will call WORKSPACE in this tutorial: this could be a "Code" folder in our home, a "c++" folder on our desktop, whatever you want. Create it if you don't already have, using your favorite method (mkdir in bash, or from the graphical interface of your distribution). We will now define an environment variable to tell the system where our folder is. Please note down the full path of this folder, which will look like `/home/$(whoami)/code/`

```bash
echo -e "\n export WORKSPACE=/full/path/to/my/folder \n" >> ~/.bashrc
source ~/.bashrc
```

2) Open a Bash terminal and type the following commands to install all the prerequisites.

```bash
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install -y gcc-8 g++-8

wget --no-check-certificate https://cmake.org/files/v3.13/cmake-3.13.1-Linux-x86_64.tar.gz
tar -xzf cmake-3.13.1-Linux-x86_64.tar.gz
export PATH=$PWD/cmake-3.13.1-Linux-x86_64/bin:$PATH

sudo apt-get install -y make git dos2unix ninja-build
git config --global core.autocrlf input
git clone https://github.com/physycom/sysconfig
```

3) Build the project with CMake:

```bash
cd $WORKSPACE
git clone https://github.com/Nico-Curti/easyDAG
cd easyDAG

mkdir -p build
cd build

cmake ..
make -j
cmake --build . --target install
cd ..
```

### macOS

1) If not already installed, install the XCode Command Line Tools, typing this command in a terminal:

```bash
xcode-select --install
```

2) If not already installed, install Homebrew following the [official guide](https://brew.sh/index_it.html).

3) Open the terminal and type these commands

```bash
brew update
brew upgrade
brew install gcc@8
brew install cmake make git ninja
```

4) Define a work folder, which we will call WORKSPACE in this tutorial: this could be a "Code" folder in our home, a "c++" folder on our desktop, whatever you want. Create it if you don't already have, using your favorite method (mkdir in bash, or from the graphical interface in Finder). We will now define an environment variable to tell the system where our folder is. Please note down the full path of this folder, which will look like /home/$(whoami)/code/

5) Open a Terminal and type the following command (replace /full/path/to/my/folder with the previous path noted down)

```bash
echo -e "\n export WORKSPACE=/full/path/to/my/folder \n" >> ~/.bash_profile
source ~/.bash_profile
```

6) Build the project with CMake (enable or disable OMP with the define **-DOMP**:

```bash
cd $WORKSPACE
git clone https://github.com/Nico-Curti/easyDAG
cd easyDAG

mkdir -p build
cd build

cmake ..
make -j
cmake --build . --target install
cd ..
```

### Windows (7+)

1) Install Visual Studio 2017 from the [official website](https://www.visualstudio.com/)

2) Open your Powershell with Administrator privileges, type the following command and confirm it:

```PowerShell
PS \>                 Set-ExecutionPolicy unrestricted
```

3) If not already installed, please install chocolatey using the [official guide](http://chocolatey.org)

4) If you are not sure about having them updated, or even installed, please install `git`, `cmake` and an updated `Powershell`. To do so, open your Powershell with Administrator privileges and type

```PowerShell
PS \>                 cinst -y git cmake powershell
```

5) Restart the PC if required by chocolatey after the latest step

6) Install PGI 18.10 from the [official website](https://www.pgroup.com/products/community.htm) (the community edition is enough and is free; NOTE: install included MS-MPI, but avoid JRE and Cygwin)

7) Activate license for PGI 18.10 Community Edition (rename the file `%PROGRAMFILES%\PGI\license.dat-COMMUNITY-18.10` to `%PROGRAMFILES%\PGI\license.dat`) if necessary, otherwise enable a Professional License if available

8) Define a work folder, which we will call `WORKSPACE` in this tutorial: this could be a "Code" folder in our home, a "cpp" folder on our desktop, whatever you want. Create it if you don't already have, using your favorite method (mkdir in Powershell, or from the graphical interface in explorer). We will now define an environment variable to tell the system where our folder is. Please note down its full path. Open a Powershell (as a standard user) and type

```PowerShell
PS \>                 rundll32 sysdm.cpl,EditEnvironmentVariables
```

9) In the upper part of the window that pops-up, we have to create a new environment variable, with name `WORKSPACE` and value the full path noted down before.
If it not already in the `PATH` (this is possible only if you did it before), we also need to modify the "Path" variable adding the following string (on Windows 10 you need to add a new line to insert it, on Windows 7/8 it is necessary to append it using a `;` as a separator between other records):

```cmd
                      %PROGRAMFILES%\CMake\bin
```

10) If `vcpkg` is not installed, please follow the next procedure, otherwise please jump to #12

```PowerShell
PS \>                 cd $env:WORKSPACE
PS Code>              git clone https://github.com/Microsoft/vcpkg.git
PS Code>              cd vcpkg
PS Code\vcpkg>        .\bootstrap-vcpkg.bat
```

11) Open a Powershell with Administrator privileges and type

```PowerShell
PS \>                 cd $env:WORKSPACE
PS Code>              cd vcpkg
PS Code\vcpkg>        .\vcpkg integrate install
```

12) Open a Powershell and build `easyDAG` using the `build.ps1` script

```PowerShell
PS \>                 cd $env:WORKSPACE
PS Code>              git clone https://github.com/Nico-Curti/easyDAG
PS Code>              cd easyDAG
PS Code\easyDAG>      .\build.ps1
```

### CMake C++ installation

We recommend the use of `CMake` for the installation since it is the most automated way to reach your needs.
First of all make sure you have a sufficient version of `CMake` installed (3.9 minimum version required).
If you are working on a machine without root privileges and you need to upgrade your `CMake` version a valid solution to overcome your problems is provided [here](https://github.com/Nico-Curti/Shut).

With a valid `CMake` version installed first of all clone the project as:

```bash
git clone https://github.com/Nico-Curti/easyDAG
cd easyDAG
```

The you can build the `easyDAG` package with

```bash
mkdir -p build
cd build && cmake .. && cmake --build . --target install
```

or more easily

```bash
./build.sh
```

if you are working on a Windows machine the right script to call is the [`build.ps1`](https://Nico-Curti/easyDAG/blob/master/build.ps1).

## Usage

The following [algebra.cpp](https://github.com/Nico-Curti/easyDAG/blob/master/example/algebra.cpp) example shows the basic APIs of **easyDAG**


<img align="right" src="img/algebra.png" width="30%">

```c++
#include <step.hpp>
#include <iostream>

int main ()
{
  float x1 = 1.f;
  double x2 = 2.;

  float y1 = 2.f;
  float y2 = 4.f;
                               //                     ___ a
  InputVariable a(x1);         //                   |
  InputVariable b(x2);         //          __ mul_1 *
  InputVariable c(y1);         //        |          |____ b
  InputVariable d(y2);         //        |
                               // sum __ +
  auto mul_1 = a * d;          //        |           ____ c
  auto mul_2 = b * c;          //        |          |
  auto sum = mul_1 + mul_2;    //        ____ mul_2 *
                               //                   |____ d

  std :: cout << "(a * d) + (b * c) = " << sum() << std :: endl;
  // (a * d) + (b * c) = 8.f

  auto equation = (a * d) + (b * c);
  assert (equation() == sum());

  return 0;
}
```

The DAG is automatically evaluated using the template recursion of the Step object.

The result evaluation is performed asynchronously using future variables (in this case is useless this kind of optimization!).

A full list of default lambda math-functions is provided in the [math.hpp](https://github.com/Nico-Curti/easyDAG/blob/master/hpp/math.hpp) file.

### View Graph

In the [graph.cpp](https://github.com/Nico-Curti/easyDAG/blob/master/example/graph.cpp) example we show how you can use easyDAG to visualize your DAG scheme using DOT.

```cpp
const int N = 10;
const std :: string pipeline_name = "pipeline";

auto init = [](const int & N)
            {
              std :: vector < float > x(N);
              return x;
            };

auto fill = [](std :: vector < float > x)
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

Step init_x(init, size);
Step init_y(init, size);

init_x.set_name(init_x);
init_y.set_name(init_y);

Step fill_x(fill, init_x);
Step fill_y(fill, init_y);

fill_x.set_name(fill_x);
fill_y.set_name(fill_y);

Step concatenate(concat, fill_x, fill_y);
concatenate.set_name(concatenate);

Step reduction(reduce, concatenate);
reduction.set_name(reduction);

reduction.graph(std :: cout, pipeline_name);
```

We set a name to each step (the default value is just `Step`).

<img align="right" src="img/reduction.png" width="30%">

The work-flow can be summarized as:

* we create two vectors starting from just a dimension size;
* we fill the two vectors with some values;
* we concatenate them;
* we apply a sum reduction.

The DAG is written in the stdout in the DOT format so if you want to visualize the png you can re-direct the stdout to a file and use the command:

```bash
dot -Tpng graph.dot > reduction.png
```

**Note:** The default settings highlight computational step as boxes while variables as circle nodes.

### Cached values

In the [cached.cpp](https://github.com/Nico-Curti/easyDAG/blob/master/example/cached.cpp) example we proof the usage of cached values into the DAG evaluation.

<img align="right" src="img/cached.png" width="30%">

```cpp
const int N = 10;

auto init = [&](const int & N)
            {
              std :: cout << "I'm the initializer" << std :: endl;
              float * x = new float[N];
              return x;
            };
auto fill = [&](float * x)
            {
              std :: cout << "I'm the filler" << std :: endl;
              std :: fill_n(x, N, 1.f);
              return x;
            };
auto sum  = [&](float * x)
            {
              std :: cout << "I'm the sum reduction" << std :: endl;
              return std :: accumulate(x, x + N, 0.f);
            };

auto prod = [&](float * x)
            {
              std :: cout << "I'm the prod reduction" << std :: endl;
              return std :: accumulate(x, x + N, 1.f, std :: multiplies < float >());
            };

auto a = InputVariable(N);

Step init_step(init, a);
Step fill_step(fill, init_step);
Step sum_step(sum, fill_step);
Step prod_step(prod, fill_step);

auto result = sum_step();
std :: cout << "Summation result: " << result << std :: endl;

// Re-calling the same evaluation the lambdas are not recomputed (aka no cout)!
std :: cout << "Re-called summ value: " << sum_step () << std :: endl;

// But also if we use common steps they do not need to be re-computed!
std :: cout << "Product result: " << prod_step() << std :: endl;
```

If the DAG has been already evaluated its dependencies are not re-computed.

In this way long computations but also common steps do not need to be evaluated several times!

### Useful API

The [helper.h](https://github.com/Nico-Curti/easyDAG/blob/master/include/helper.h) and [utils.h](https://github.com/Nico-Curti/easyDAG/blob/master/include/utils.h) scripts include some useful APIs to manage `Step` variables.

First of all you can check the type of the current variable with

```cpp
float x = 2.f;
int y = 2;
auto a = InputVariable(x);
auto b = InputVariable < decltype(y) > ();

auto sum1 = a + b;

static_assert ( utils :: is_variable < decltype(x)    >() == true,  "It is a variable");
static_assert ( utils :: is_variable < decltype(a)    >() == true,  "It is a variable");
static_assert ( utils :: is_variable < decltype(b)    >() == true,  "It is a variable");
static_assert ( utils :: is_variable < decltype(sum1) >() == false, "It is not a variable");
static_assert ( utils :: is_step     < decltype(x)    >() == false, "It is not a step");
static_assert ( utils :: is_step     < decltype(a)    >() == false, "It is not a step");
static_assert ( utils :: is_step     < decltype(b)    >() == false, "It is not a step");
static_assert ( utils :: is_step     < decltype(sum1) >() == true,  "It is a step");
```

In this way you can check at **compile time** the variable types.

If you have already build a DAG you can be interested about the number of operations involved in the computation.

To this purpose the `utils :: OperationCount` can summarize you these kind of information. For example:

```cpp
float x1  = 10.f;
double x2 = 2.;

float y1 = 3.f;
float y2 = 4.f;

auto a = InputVariable(x1);
auto b = InputVariable(x2);
auto c = InputVariable(y1);
auto d = InputVariable(y2);

auto sum = (a * b) + (c + d) + x1;

auto cnt = utils :: OperationCount < decltype(sum) >();

std :: cout << "The current DAG has " << cnt.num_variables  << " variables" << std :: endl;
std :: cout << "The current DAG has " << cnt.num_operations << " operations" << std :: endl;
std :: cout << "The current DAG has " << cnt.num_nodes      << " nodes" << std :: endl;

// The current DAG has 5 variables
// The current DAG has 4 operations
// The current DAG has 9 nodes
```

## Testing

`easyDAG` uses CMake to build a full list of tests. You can disable tests setting the `-DBUILD_TEST=OFF` during the building.
All the test are performed using the [`Catch2`](https://github.com/catchorg/Catch2/) (v2.11.0) library.

The test scripts can be found [here](https://github.com/Nico-Curti/easyDAG/blob/master/test).

## Contribution

Any contribution is more than welcome :heart:. Just fill an [issue](https://github.com/Nico-Curti/easyDAG/blob/master/ISSUE_TEMPLATE.md) or a [pull request](https://github.com/Nico-Curti/easyDAG/blob/master/PULL_REQUEST_TEMPLATE.md) and we will check ASAP!

See [here](https://github.com/Nico-Curti/easyDAG/blob/master/CONTRIBUTING.md) for further informations about how to contribute with this project.

## References

* [easyDAG](https://github.com/eDIMESLab/easyDAG): easyDAG Python version.

## Authors

* <img src="https://avatars0.githubusercontent.com/u/24650975?s=400&v=4" width="25px"> **Nico Curti** [git](https://github.com/Nico-Curti), [unibo](https://www.unibo.it/sitoweb/nico.curti2)

* <img src="https://avatars2.githubusercontent.com/u/1419337?s=400&v=4" width="25px;"/> **Enrico Giampieri** [git](https://github.com/EnricoGiampieri)

See also the list of [contributors](https://github.com/Nico-Curti/easyDAG/contributors) [![GitHub contributors](https://img.shields.io/github/contributors/Nico-Curti/easyDAG.svg?style=plastic)](https://github.com/Nico-Curti/easyDAG/graphs/contributors/) who participated in this project.

## License

The `easyDAG` package is licensed under the MIT "Expat" License. [![License](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/Nico-Curti/easyDAG/blob/master/LICENSE.md)

## Acknowledgments

Thanks goes to all contributors of this project.

## Citation

If you have found `easyDAG` helpful in your research, please consider citing this project repository

```tex
@misc{easyDAG,
  author = {Curti, Nico and Giampieri, Enrico},
  title = {Easy DAG in C++},
  year = {2019},
  publisher = {GitHub},
  howpublished = {\url{https://github.com/Nico-Curti/easyDAG}},
}
```
