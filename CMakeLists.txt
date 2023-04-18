cmake_policy(SET CMP0048 NEW)
cmake_minimum_required(VERSION 3.16)
project(sabai VERSION 0.2)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(sabai INTERFACE)
target_include_directories(sabai
  INTERFACE
  include
)

option(BUILD_Sabai_TESTS "Build Sabai Tests" ON)
if(BUILD_Sabai_TESTS)
  find_package(GTest REQUIRED)

  add_executable(sabai_tests
    test/test_static.cpp
    test/test_operators.cpp
    test/test_indexing.cpp
    test/test_products.cpp
    test/test_metrics.cpp
    test/test_decompositions.cpp
    test/test_dynamic.cpp)

  target_link_libraries(sabai_tests PRIVATE sabai GTest::GTest GTest::Main)

  include(GoogleTest)
  gtest_discover_tests(sabai_tests)
endif()
