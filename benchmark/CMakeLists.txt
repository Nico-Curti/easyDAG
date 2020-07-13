
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

add_custom_target(bench_linear_chain)
add_executable(linear_chain ${CMAKE_SOURCE_DIR}/benchmark/linear_chain/main.cpp
                            ${CMAKE_SOURCE_DIR}/benchmark/linear_chain/omp.cpp
                            ${CMAKE_SOURCE_DIR}/benchmark/linear_chain/easy.hpp)
target_include_directories(linear_chain PRIVATE ${BENCHMARK_INC_DIR})
target_include_directories(linear_chain PRIVATE ${BENCHMARK_HPP_DIR})
target_include_directories(linear_chain PRIVATE ${CMAKE_SOURCE_DIR}/benchmark/linear_chain)
target_include_directories(linear_chain PRIVATE ${CMAKE_SOURCE_DIR}/benchmark/linear_chain/include)
target_link_libraries(linear_chain ${linked_libs})


add_custom_target(bench_binary_tree)
add_executable(binary_tree ${CMAKE_SOURCE_DIR}/benchmark/binary_tree/main.cpp
                           ${CMAKE_SOURCE_DIR}/benchmark/binary_tree/omp.cpp
                           ${CMAKE_SOURCE_DIR}/benchmark/binary_tree/easy.hpp)
target_include_directories(binary_tree PRIVATE ${BENCHMARK_INC_DIR})
target_include_directories(binary_tree PRIVATE ${BENCHMARK_HPP_DIR})
target_include_directories(binary_tree PRIVATE ${CMAKE_SOURCE_DIR}/benchmark/binary_tree)
target_include_directories(binary_tree PRIVATE ${CMAKE_SOURCE_DIR}/benchmark/binary_tree/include)
target_link_libraries(binary_tree ${linked_libs})



install (TARGETS linear_chain   DESTINATION ${BENCHMARK_OUT_DIR})
install (TARGETS binary_tree    DESTINATION ${BENCHMARK_OUT_DIR})
