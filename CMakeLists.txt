cmake_policy(SET CMP0048 NEW)
project(matrixcpp VERSION 0.1)
cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

add_library(arithmetic INTERFACE)
set_property(TARGET arithmetic PROPERTY CXX_STANDARD 20)
target_include_directories(arithmetic INTERFACE include)

add_library(math-matrix INTERFACE)
set_property(TARGET math-matrix PROPERTY CXX_STANDARD 20)
target_include_directories(math-matrix INTERFACE include)

option(ENABLE_TESTING "Enable Testing" ON)
if(${ENABLE_TESTING})
        include(FetchContent)
        FetchContent_Declare(
          googletest
          URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
        )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
        enable_testing()

        add_executable(arithmetic_tests
                        test/test_arithmetic.cpp)

        target_link_libraries(arithmetic_tests PRIVATE arithmetic gtest gtest_main)

        add_executable(matrix_tests
                        test/test_base.cpp
                        test/test_operators.cpp
                        test/test_indexing.cpp
                        test/test_products.cpp
                        test/test_decompositions.cpp
                        test/test_dynamic.cpp)

        target_link_libraries(matrix_tests PRIVATE math-matrix gtest gtest_main)

        include(GoogleTest)
        gtest_discover_tests(matrix_tests)
endif()
