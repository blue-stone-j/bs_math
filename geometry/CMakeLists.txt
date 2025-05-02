
set(module_name geometry)
find_package(Eigen3 REQUIRED)
set(geometry_include ${EIGEN3_INCLUDE_DIRS})
set(geometry_lib "")

compile_module(${module_name} "${geometry_include}" "${geometry_lib}")
