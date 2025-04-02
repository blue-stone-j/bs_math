
set(module_name statistics)
find_package(Eigen3 REQUIRED)
set(statistics_include ${EIGEN3_INCLUDE_DIRS})
set(statistics_lib)

# Set the source folder
set(source_dir ./src)
# Get all .cpp files in the source folder
file(GLOB_RECURSE cpp_files ${source_dir}/*.cpp)


add_library(${module_name} SHARED ${cpp_files})
target_link_libraries(${module_name} ${statistics_lib})
target_include_directories(${module_name} PUBLIC ./include  ${statistics_include})
install(TARGETS ${module_name} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/)


if(BUILD_TEST)
  foreach(cpp_file ${cpp_files})
    # Get the filename without extension
    get_filename_component(function_name ${cpp_file} NAME_WE)

    add_executable(${function_name}_test test/${function_name}_test.cpp src/${function_name}.cpp)
    target_link_libraries(${function_name}_test ${statistics_lib} gtest gtest_main)
    target_include_directories(${function_name}_test PUBLIC ./include ${statistics_include})
    # Register test
    add_test(NAME ${function_name}Test COMMAND ${function_name}_test)
  endforeach()
endif()
