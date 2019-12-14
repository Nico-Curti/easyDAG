| **Authors**  | **Project** | **Documentation** | **Build Status** | **Code Quality** | **Coverage** |
|:------------:|:-----------:|:-----------------:|:----------------:|:----------------:|:------------:|
| [**N. Curti**](https://github.com/Nico-Curti) <br/> [**E. Giampieri**](https://github.com/EnricoGiampieri)   |  **easyDAG**  | [![docs](https://img.shields.io/badge/doc-latest-blue.svg?style=plastic)](https://nico-curti.github.io/easyDAG/) | **Linux/MacOS** : [![travis](https://travis-ci.com/Nico-Curti/easyDAG.svg?branch=master)](https://travis-ci.com/Nico-Curti/easyDAG) <br/> **Windows** : [![appveyor](https://ci.appveyor.com/api/projects/status/exx9gbp6blyggdmg?svg=true)](https://ci.appveyor.com/project/Nico-Curti/easydag) | **Codacy** : [![Codacy](https://api.codacy.com/project/badge/Grade/8d261e840f664c5fa9bf3e1c09509085)](https://www.codacy.com/manual/Nico-Curti/easyDAG?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Nico-Curti/easyDAG&amp;utm_campaign=Badge_Grade) <br/> **Codebeat** : [![codebeat](https://codebeat.co/badges/a9b408d3-11c7-4c91-ae2c-3e84b250d9e8)](https://codebeat.co/projects/github-com-nico-curti-easydag-master) | *miss* |

[![GitHub pull-requests](https://img.shields.io/github/issues-pr/Nico-Curti/easyDAG.svg?style=plastic)](https://github.com/Nico-Curti/easyDAG/pulls)
[![GitHub issues](https://img.shields.io/github/issues/Nico-Curti/easyDAG.svg?style=plastic)](https://github.com/Nico-Curti/easyDAG/issues)

[![GitHub stars](https://img.shields.io/github/stars/Nico-Curti/easyDAG.svg?label=Stars&style=social)](https://github.com/Nico-Curti/easyDAG/stargazers)
[![GitHub watchers](https://img.shields.io/github/watchers/Nico-Curti/easyDAG.svg?label=Watch&style=social)](https://github.com/Nico-Curti/easyDAG/watchers)

# easy Direct Acyclic Graph Scheduler

C++ version of the original [easyDAG](https://github.com/eDIMESLab/easyDAG) project in Python.

* [Theory](#theory)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
* [Usage](#usage)
* [Contribution](#contribution)
* [References](#references)
* [Authors](#authors)
* [License](#license)
* [Acknowledgments](#acknowledgments)
* [Citation](#citation)

## Theory

**TODO**

## Prerequisites

The `easyDAG` project is written in `C++` using a large amount of **c++17** features.
The package installation can be performed via [`CMake`](https://github.com/Nico-Curti/easyDAG/blob/master/CMakeLists.txt).

## Installation

Follow the instruction about your needs.

A complete list of instructions "for beginners" is also provided for both [cpp](https://github.com/Nico-Curti/easyDAG/blob/master/docs/cpp_install.md).

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

```c++
#include <step.hpp>
#include <iostream>

int main ()
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

  std :: cout << "(a * d) + (b * c) = " << sum_1() << std :: endl;
  // (a * d) + (b * c) = 8.f

  return 0;
}
```


## Contribution

Any contribution is more than welcome :heart:. Just fill an [issue](https://github.com/Nico-Curti/easyDAG/blob/master/ISSUE_TEMPLATE.md) or a [pull request](https://github.com/Nico-Curti/easyDAG/blob/master/PULL_REQUEST_TEMPLATE.md) and we will check ASAP!

See [here](https://github.com/Nico-Curti/easyDAG/blob/master/CONTRIBUTING.md) for further informations about how to contribute with this project.

## References

* [easyDAG](https://github.com/eDIMESLab/easyDAG): easyDAG Python version.


## Authors

* **Nico Curti** [git](https://github.com/Nico-Curti), [unibo](https://www.unibo.it/sitoweb/nico.curti2)
* **Enrico Giampieri** [git](https://github.com/EnricoGiampieri), [unibo](https://www.unibo.it/sitoweb/enrico.giampieri)

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
