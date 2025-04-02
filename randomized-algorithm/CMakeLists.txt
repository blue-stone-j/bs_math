cmake_minimum_required(VERSION 3.16.3)
project(randomized_algorithm)

# set(CMAKE_BUILD_TYPE "Release")
# add_compile_options(-std=c++17)
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(include)

include(cmake/build_libraries.cmake)

include(cmake/build_test.cmake)
