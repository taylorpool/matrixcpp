cmake_policy(SET CMP0048 NEW)
project(math-matrix VERSION 0.1)
cmake_minimum_required(VERSION 3.21)

add_library(math-matrix INTERFACE)
target_include_directories(math-matrix INTERFACE include/matrix)

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

        add_executable(matrix_tests
                        test/test_matrix.cpp)

        target_link_libraries(matrix_tests INTERFACE
                      math-matrix)
        target_link_libraries(matrix_tests PRIVATE gtest gtest_main)

        include(GoogleTest)
        gtest_discover_tests(matrix_tests)
endif()