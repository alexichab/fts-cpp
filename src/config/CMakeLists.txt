set(target_name config)

add_library(${target_name} STATIC
  config.hpp
  config.cpp
)

set_compile_options(${target_name})

target_include_directories(
  ${target_name}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(
  ${target_name}
  PRIVATE
    libparser
)