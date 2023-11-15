set(target_name libindex)

add_library(${target_name} STATIC
  libindex.hpp
  libindex.cpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
  ${target_name}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/_deps/picosha2-src
)

target_link_libraries(
  ${target_name}
  PRIVATE
    libparser
)