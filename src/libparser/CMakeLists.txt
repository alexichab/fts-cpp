set(target_name libparser)

add_library(${target_name} STATIC
  libparser.hpp
  libparser.cpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
  ${target_name}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)