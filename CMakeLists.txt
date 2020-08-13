cmake_minimum_required (VERSION 3.9)

# DAG Version
set (DAG_MAJOR    1)
set (DAG_MINOR    0)
set (DAG_REVISION 0)
set (DAG_VERSION ${DAG_MAJOR}.${DAG_MINOR}.${DAG_REVISION})

project (DAG LANGUAGES CXX VERSION ${DAG_VERSION} DESCRIPTION "Easy DAG in C++")

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions (-DMAJOR=${DAG_MAJOR} -DMINOR=${DAG_MINOR} -DREVISION=${DAG_REVISION})

#################################################################
#                         COMPILE OPTIONS                       #
#################################################################

option (BUILD_TEST      "Enable tests build           support" ON)
option (BUILD_BENCHMARK "Enable benchmark build       support" OFF)

#################################################################
#                         SETTING VARIABLES                     #
#################################################################

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/" ${CMAKE_MODULE_PATH})

if ( NOT APPLE )
  set (CMAKE_SKIP_BUILD_RPATH             FALSE )
  set (CMAKE_BUILD_WITH_INSTALL_RPATH     FALSE )
  set (CMAKE_INSTALL_RPATH_USE_LINK_PATH  TRUE  )
endif()

# make sure that the default is a RELEASE
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if ( CMAKE_COMPILER_IS_GNUCXX )
  add_compile_options (-Wall -Wextra -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -Wno-narrowing -Wpedantic)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    string (REGEX REPLACE "-O[0123]" "-Og" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG" )
    set (CMAKE_CXX_FLAGS_RELEASE "")
  elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    string (REGEX REPLACE "-O3" "-Ofast" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG" )
    set (CMAKE_CXX_FLAGS_DEBUG "")
  endif()
  #list (APPEND linked_libs stdc++fs)
endif()

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  add_compile_options(-Wno-deprecated -Wno-writable-strings)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    string (REGEX REPLACE "-O0" "-Og" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG" )
  elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    string (REGEX REPLACE "-O3" "-Ofast" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG" )
  endif()
  #list (APPEND linked_libs stdc++fs)
endif()

if (MSVC)
  set (CMAKE_CXX_FLAGS "/wd4013 /wd4018 /wd4028 /wd4047 /wd4068 /wd4090 /wd4101 /wd4113 /wd4133 /wd4190 /wd4244 /wd4267 /wd4305 /wd4477 /wd4996 /wd4819 /fp:fast ${CMAKE_CXX_FLAGS}")
  string (REGEX REPLACE "/O2" "/Ox" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
  add_definitions (-D_CRT_RAND_S)
  add_definitions (-DNOMINMAX)
  add_definitions (-D_USE_MATH_DEFINES)
  add_definitions (-D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
  set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if (COMPILER_SUPPORTS_MARCH_NATIVE)

  if (MSVC)

  else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
  endif ()

endif()


#################################################################
#                         PARSE OPTIONS                         #
#################################################################

message (STATUS "Looking for pthread library")
set (CMAKE_THREAD_PREFER_PTHREAD ON)
find_package (Threads REQUIRED)
list (APPEND linked_libs Threads::Threads )

#################################################################
#                         SETTING DIRECTORIES                   #
#################################################################

set(SRC_DIR  ${CMAKE_SOURCE_DIR}/src                                 CACHE PATH "Path where find cpp files"                        )
set(INC_DIR  ${CMAKE_SOURCE_DIR}/include                             CACHE PATH "Path where find header files"                     )
set(HPP_DIR  ${CMAKE_SOURCE_DIR}/hpp                                 CACHE PATH "Path where find hpp files"                        )
set(EXAMPLE  ${CMAKE_SOURCE_DIR}/example                             CACHE PATH "Path where find main files"                       )
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test                                CACHE PATH "Path where find test files"                       )
set(BENC_DIR ${CMAKE_SOURCE_DIR}/benchmark                           CACHE PATH "Path where find benchmark files"                  )
set(LIB_DIR  ${CMAKE_SOURCE_DIR}/lib                                 CACHE PATH "Path where lib will be installed"            FORCE)
set(INST_DIR ${CMAKE_SOURCE_DIR}/share/dag                           CACHE PATH "Path where cmake configs will be installed"  FORCE)
set(OUT_DIR  ${CMAKE_SOURCE_DIR}/bin                                 CACHE PATH "Path where outputs will be installed"        FORCE)
set(OUT_TEST ${CMAKE_SOURCE_DIR}/test/bin                            CACHE PATH "Path where test outputs will be installed"   FORCE)

set(INSTALL_INCLUDE_DIR  "${CMAKE_CURRENT_LIST_DIR}/share/include/easyDAG"  CACHE PATH "Path where headers will be installed")
set(INSTALL_CMAKE_DIR    "${CMAKE_CURRENT_LIST_DIR}/share/easyDAG"          CACHE PATH "Path where cmake configs will be installed")

set(CMAKE_DEBUG_POSTFIX d)

set(DAGlib DAG)

file(GLOB SRC           "${SRC_DIR}/*.cpp" )
file(GLOB HEADER        "${INC_DIR}/*.h"   )
file(GLOB HPP           "${INC_DIR}/*.hpp" )
file(GLOB SCORER_HEADER "${INC_SCORER}/*.h")

include_directories(${INC_DIR} ${HPP_DIR} ${TEST_DIR})

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

string (REPLACE " " ";" CMAKE_CXX_FLAGS_LIST ${CMAKE_CXX_FLAGS})

#################################################################
#                          SUMMARY                              #
#################################################################

message(STATUS ""                                                                    )
message(STATUS "=================== EasyDAG configuration Summary ==============="   )
message(STATUS "   EasyDAG version: ${DAG_MAJOR}.${DAG_MINOR}.${DAG_REVISION}"       )
message(STATUS ""                                                                    )
message(STATUS "   Build type : ${CMAKE_BUILD_TYPE}"                                 )
message(STATUS "   C++ :"                                                            )
message(STATUS "      C++ Compiler : ${CMAKE_CXX_COMPILER}"                          )
message(STATUS "      C++ flags    :"                                                )
foreach(FLAG ${CMAKE_CXX_FLAGS_LIST})
  message(STATUS "                    * ${FLAG}"                                     )
endforeach(FLAG)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  message(STATUS "      C++ Debug flags:"                                            )
  foreach(FLAG ${CMAKE_CXX_FLAGS_DEBUG})
    message(STATUS "                    * ${FLAG}"                                   )
  endforeach(FLAG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "      C++ Release flags  :"                                        )
  foreach(FLAG ${CMAKE_CXX_FLAGS_RELEASE})
    message(STATUS "                    * ${FLAG}"                                   )
  endforeach(FLAG)
endif()
message(STATUS "      Linker flags : "                                               )
foreach(FLAG ${linked_libs})
  message(STATUS "                    * ${FLAG}"                                     )
endforeach(FLAG)
message(STATUS ""                                                                    )
message(STATUS "   BUILD_TEST      : ${BUILD_TEST}"                                  )
message(STATUS "   BUILD_BENCHMARK : ${BUILD_BENCHMARK}"                             )
message(STATUS ""                                                                    )


#################################################################
#                         MAIN RULES                            #
#################################################################

# add_library(${DAGlib} SHARED ${SRC} ${HEADER} ${HPP})
# set_property(TARGET ${DAGlib} PROPERTY POSITION_INDEPENDENT_CODE ON)
# target_link_libraries(${DAGlib} ${linked_libs})
#
# list (APPEND ALL_HEADER ${HEADER})
# list (APPEND ALL_HEADER ${HPP})
# set_target_properties(${DAGlib} PROPERTIES PUBLIC_HEADER "${ALL_HEADER}")

if (BUILD_TEST)
  add_subdirectory(${TEST_DIR})
endif ()

if (BUILD_BENCHMARK)
  add_subdirectory(${BENC_DIR})
endif ()

add_custom_target(examples)

add_executable(algebra ${EXAMPLE}/algebra.cpp ${HEADER} ${HPP})
target_link_libraries(algebra ${linked_libs})# ${DAGlib})

add_executable(graphviz ${EXAMPLE}/graphviz.cpp ${HEADER} ${HPP})
target_link_libraries(graphviz ${linked_libs})# ${DAGlib})

add_executable(cached ${EXAMPLE}/cached.cpp ${HEADER} ${HPP})
target_link_libraries(cached ${linked_libs})# ${DAGlib})

add_executable(condition ${EXAMPLE}/condition.cpp ${HEADER} ${HPP})
target_link_libraries(condition ${linked_libs})# ${DAGlib})

add_executable(mcc ${EXAMPLE}/mcc.cpp ${HEADER} ${HPP})
target_link_libraries(mcc ${linked_libs})# ${DAGlib})

add_executable(time_monitor ${EXAMPLE}/time_monitor.cpp ${HEADER} ${HPP})
target_link_libraries(time_monitor ${linked_libs})# ${DAGlib})

add_dependencies(examples algebra graphviz cached condition mcc time_monitor)


#################################################################
#                          INSTALLERS                           #
#################################################################

# install(TARGETS ${DAGlib}      EXPORT DAGTargets
#                                RUNTIME DESTINATION ${OUT_DIR}
#                                LIBRARY DESTINATION ${LIB_DIR}
#                                ARCHIVE DESTINATION ${LIB_DIR}
#                                PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDE_DIR}
#                                COMPONENT dev
#                                )

install(TARGETS algebra      DESTINATION ${OUT_DIR})
install(TARGETS graphviz     DESTINATION ${OUT_DIR})
install(TARGETS cached       DESTINATION ${OUT_DIR})
install(TARGETS condition    DESTINATION ${OUT_DIR})
install(TARGETS mcc          DESTINATION ${OUT_DIR})
install(TARGETS time_monitor DESTINATION ${OUT_DIR})

# #################################################################
# #                          EXPORT DAG                          #
# #################################################################
#
# install (EXPORT DAGTargets
#         FILE DAGTargets.cmake
#         NAMESPACE DAG::
#         DESTINATION "${INSTALL_CMAKE_DIR}"
#        )
#
# # Export the package for use from the build-tree (this registers the build-tree with a global CMake-registry)
# export (PACKAGE DAG)
#
# # Create the DAGConfig.cmake
# # First of all we compute the relative path between the cmake config file and the include path
# file (RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${LIB_DIR}/include")
# set (CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
# configure_file (DAGConfig.cmake.in "${PROJECT_BINARY_DIR}/DAGConfig.cmake" @ONLY)
# set (CONF_INCLUDE_DIRS "\${DAG_CMAKE_DIR}/${REL_INCLUDE_DIR}")
# configure_file (DAGConfig.cmake.in "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/DAGConfig.cmake" @ONLY)
#
# # Create the DAGConfigVersion.cmake
# include(CMakePackageConfigHelpers)
# write_basic_package_version_file ("${PROJECT_BINARY_DIR}/DAGConfigVersion.cmake"
#                                  COMPATIBILITY SameMajorVersion
#                                 )
#
# install (FILES
#         "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/DAGConfig.cmake"
#         "${PROJECT_BINARY_DIR}/DAGConfigVersion.cmake"
#         DESTINATION "${INSTALL_CMAKE_DIR}"
#         )
