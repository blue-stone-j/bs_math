
set(module_name statistics)
find_package(Eigen3 REQUIRED)
set(statistics_include ${EIGEN3_INCLUDE_DIRS})
set(statistics_lib)

compile_module(${module_name} "${statistics_include}" "${statistics_lib}")