cmake_minimum_required(VERSION 3.16.3)
project(randomized_algorithm)

set(CMAKE_BUILD_TYPE "Release")
add_compile_options(-std=c++17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(knuth_shuffle knuth_shuffle/knuth_shuffle.cpp)
target_link_libraries(knuth_shuffle ${TARGET_LIBRARIES} gflags)

# ---------------------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------------------
# install(TARGETS camera_node undistort_node
# ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
# LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
# RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

# install(DIRECTORY
# launch
# config
# DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )