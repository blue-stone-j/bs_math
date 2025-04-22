cmake_minimum_required(VERSION 3.16.3)
project(bmath)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -pthread")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED BMATH_VERSION)
  set(BMATH_VERSION_MAJOR 1)
  set(BMATH_VERSION_MINOR 0)
  set(BMATH_VERSION_PATCH 0)
  set(BMATH_VERSION ${BMATH_VERSION_MAJOR}.${BMATH_VERSION_MINOR}.${BMATH_VERSION_PATCH})
  set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install/${PROJECT_NAME}-${BMATH_VERSION})
endif()

enable_testing()

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(statistics)
add_subdirectory(stochastic)
add_subdirectory(geometry)

include(cmake/global_definition.cmake)

include(cmake/install_files.cmake)