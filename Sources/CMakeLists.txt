cmake_minimum_required(VERSION 3.5)
project(cpp_playground)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_executable(src/fib_recursive fib_recursive.cpp)
add_executable(src/fib_iteration fib_iteration.cpp)
add_executable(src/fib_threads fib_threads.cpp)
add_executable(src/fib_compile-time fib_compile-time.cpp)
add_executable(src/fib_compile-time-array fib_compile-time-array.cpp)
## additional SFINAE examples
add_executable(src/template_type_parameter_sfinae_guard template_type_parameter_sfinae_guard.cpp)
add_executable(src/template_sfinae_basic template_sfinae_basic.cpp)
