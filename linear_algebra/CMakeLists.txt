
set(module_name linear_algebra)
set(${module_name}_include ${EIGEN3_INCLUDE_DIRS})
set(${module_name}_lib "")

compile_module(${module_name} "${${module_name}_include}" "${${module_name}_lib}")
