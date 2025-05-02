
set(module_name stochastic)

set(stochastic_include ${EIGEN3_INCLUDE_DIRS})
set(stochastic_lib "")
compile_module(${module_name} "${stochastic_include}" "${stochastic_lib}")
