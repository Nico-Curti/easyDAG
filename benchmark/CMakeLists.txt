
find_package (OpenMP REQUIRED)

if (OPENMP_FOUND)
  message (STATUS "OpenMP found")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  if (APPLE)
    list (APPEND linked_libs OpenMP::OpenMP_CXX)
  endif ()
endif ()

set (BENCHMARK_SRC_DIR ${CMAKE_SOURCE_DIR}/benchmark/timeit/src      CACHE PATH "Path where find cpp files"                 )
set (BENCHMARK_INC_DIR ${CMAKE_SOURCE_DIR}/benchmark/timeit/include  CACHE PATH "Path where find header files"              )
set (BENCHMARK_HPP_DIR ${CMAKE_SOURCE_DIR}/benchmark/timeit/hpp      CACHE PATH "Path where find hpp files"                 )
set (BENCHMARK_OUT_DIR ${CMAKE_SOURCE_DIR}/benchmark/bin             CACHE PATH "Path where outputs will be installed" FORCE)

add_custom_target(benchmarks)

# Linear chain benchmark

add_executable(linear_chain ${CMAKE_SOURCE_DIR}/benchmark/linear_chain/main.cpp
                            ${CMAKE_SOURCE_DIR}/benchmark/linear_chain/omp.cpp
                            ${CMAKE_SOURCE_DIR}/benchmark/linear_chain/easy.hpp)
target_include_directories(linear_chain PRIVATE ${BENCHMARK_INC_DIR})
target_include_directories(linear_chain PRIVATE ${BENCHMARK_HPP_DIR})
target_include_directories(linear_chain PRIVATE ${CMAKE_SOURCE_DIR}/benchmark/linear_chain)
target_include_directories(linear_chain PRIVATE ${CMAKE_SOURCE_DIR}/benchmark/linear_chain/include)
target_link_libraries(linear_chain ${linked_libs})


# Binary tree summation benchmark

add_executable(binary_tree ${CMAKE_SOURCE_DIR}/benchmark/binary_tree/main.cpp
                           ${CMAKE_SOURCE_DIR}/benchmark/binary_tree/omp.cpp
                           ${CMAKE_SOURCE_DIR}/benchmark/binary_tree/easy.hpp)
target_include_directories(binary_tree PRIVATE ${BENCHMARK_INC_DIR})
target_include_directories(binary_tree PRIVATE ${BENCHMARK_HPP_DIR})
target_include_directories(binary_tree PRIVATE ${CMAKE_SOURCE_DIR}/benchmark/binary_tree)
target_include_directories(binary_tree PRIVATE ${CMAKE_SOURCE_DIR}/benchmark/binary_tree/include)
target_link_libraries(binary_tree ${linked_libs})


# Math dot product benchmark

add_executable(dot_product ${CMAKE_SOURCE_DIR}/benchmark/dot_product/main.cpp
                           ${CMAKE_SOURCE_DIR}/benchmark/dot_product/omp.cpp
                           ${CMAKE_SOURCE_DIR}/benchmark/dot_product/easy.hpp)
target_include_directories(dot_product PRIVATE ${BENCHMARK_INC_DIR})
target_include_directories(dot_product PRIVATE ${BENCHMARK_HPP_DIR})
target_include_directories(dot_product PRIVATE ${CMAKE_SOURCE_DIR}/benchmark/dot_product)
target_include_directories(dot_product PRIVATE ${CMAKE_SOURCE_DIR}/benchmark/dot_product/include)
target_link_libraries(dot_product ${linked_libs})

add_dependencies(benchmarks linear_chain binary_tree dot_product)

install (TARGETS linear_chain   DESTINATION ${BENCHMARK_OUT_DIR})
install (TARGETS binary_tree    DESTINATION ${BENCHMARK_OUT_DIR})
