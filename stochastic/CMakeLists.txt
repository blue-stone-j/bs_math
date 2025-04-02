project(randomized_algorithm)

# include_directories(include)

set(MODULE_NAME randomized_algorithm)

# Set the source folder
set(SOURCE_DIR ./src)
message(STATUS "Source directory: ${SOURCE_DIR}")
# Get all .cpp files in the source folder
file(GLOB_RECURSE CPP_FILES ${SOURCE_DIR}/*.cpp)


add_library(${MODULE_NAME} SHARED ${CPP_FILES})
target_link_libraries(${MODULE_NAME} ${common_lib})
target_include_directories(${MODULE_NAME} PUBLIC ./include)
install(TARGETS ${MODULE_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/)


if(BUILD_TEST)
  foreach(CPP_FILE ${CPP_FILES})
    # Get the filename without extension
    get_filename_component(FILENAME_NO_EXT ${CPP_FILE} NAME_WE)

    add_executable(${FILENAME_NO_EXT}_test test/${FILENAME_NO_EXT}_test.cpp src/${FILENAME_NO_EXT}.cpp)
    target_link_libraries(${FILENAME_NO_EXT}_test ${common_lib} gtest gtest_main)
    target_include_directories(${FILENAME_NO_EXT}_test PUBLIC ./include)
    # Register test
    add_test(NAME ${FILENAME_NO_EXT}Test COMMAND ${FILENAME_NO_EXT}_test)
  endforeach()
endif()
