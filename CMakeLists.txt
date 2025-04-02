cmake_minimum_required(VERSION 3.16.3)
project(bs_math)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -pthread")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED BS_MATH_VERSION)
  set(BS_MATH_VERSION_MAJOR 1)
  set(BS_MATH_VERSION_MINOR 0)
  set(BS_MATH_VERSION_PATCH 0)
  set(BS_MATH_VERSION ${BS_MATH_VERSION_MAJOR}.${BS_MATH_VERSION_MINOR}.${BS_MATH_VERSION_PATCH})
  set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install/${PROJECT_NAME}-${BS_MATH_VERSION})
endif()

enable_testing()

add_subdirectory(randomized-algorithm)

include(cmake/global_definition.cmake)

include(cmake/install_files.cmake)