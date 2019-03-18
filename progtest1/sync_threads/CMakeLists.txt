cmake_minimum_required(VERSION 3.10)
project(sync_threads)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -pedantic -lm")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

link_directories("${PROJECT_SOURCE_DIR}")
add_executable("${PROJECT_NAME}" solution.cpp common.h progtest_solver.h sample_tester.cpp sample_tester.h)

target_link_libraries("${PROJECT_NAME}" pthread progtest_solver)