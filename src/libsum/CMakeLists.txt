set(target_name libsum)

add_library(${target_name} STATIC
  libsum.hpp
  libsum.cpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
  ${target_name}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}  
)