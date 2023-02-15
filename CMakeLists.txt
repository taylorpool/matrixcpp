cmake_policy(SET CMP0048 NEW)
cmake_minimum_required(VERSION 3.16)
project(matrixcpp VERSION 0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(arithmetic
  INTERFACE)
target_include_directories(arithmetic
  INTERFACE include)

add_library(math-matrix
  src/dynamic.cpp
)
set_property(TARGET math-matrix
  PROPERTY CXX_STANDARD 20)
target_include_directories(math-matrix
  PUBLIC include)

option(ENABLE_TESTING "Enable Testing" ON)
if(${ENABLE_TESTING})
  find_package(GTest REQUIRED)

  add_executable(arithmetic_tests
    test/test_arithmetic.cpp)

  target_link_libraries(arithmetic_tests PRIVATE
    arithmetic GTest::GTest GTest::Main)

  add_executable(matrix_tests
    test/test_static.cpp
    test/test_operators.cpp
    test/test_indexing.cpp
    test/test_products.cpp
    test/test_metrics.cpp
    test/test_decompositions.cpp
    test/test_dynamic.cpp)

  target_link_libraries(matrix_tests PRIVATE math-matrix GTest::GTest GTest::Main)

  include(GoogleTest)
  gtest_discover_tests(matrix_tests)
endif()
