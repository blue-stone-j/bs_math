cmake_minimum_required(VERSION 3.16.3)
project(edge_dection)

set(CMAKE_BUILD_TYPE "Release")
add_compile_options(-std=c++17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# find_package(OpenCV REQUIRED QUIET)
# include_directories(${OpenCV_INCLUDE_DIRS})

# find_package(Eigen3 REQUIRED)
# include_directories(${EIGEN3_INCLUDE_DIRS})

# include_directories(include ./common)

# set(TARGET_LIBRARIES "")
# list(APPEND TARGET_LIBRARIES ${GLOG_LIBRARIES})
# list(APPEND TARGET_LIBRARIES ${OpenCV_LIBRARIES})
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