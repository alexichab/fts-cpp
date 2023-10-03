set(target_name libsum)

add_library(${target_name} STATIC
  libsum.hpp
  libsum.cpp
)

include(CompileOptions)
set_compile_options(${target_name})