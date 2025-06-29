
set(module_name sorting)

set(sorting_include ${EIGEN3_INCLUDE_DIRS})
set(sorting_lib "")
compile_module(${module_name} "${sorting_include}" "${sorting_lib}")
