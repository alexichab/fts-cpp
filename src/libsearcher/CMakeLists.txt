set(target_name libsearcher)

add_library(${target_name} STATIC
  libsearcher.hpp
  libsearcher.cpp
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
  ${target_name}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/_deps/picosha2-src
    ${CMAKE_SOURCE_DIR}/src/libparser
)

target_link_libraries(
  ${target_name}
  PRIVATE
    libparser
    config
)

include_directories(${PROJECT_SOURCE_DIR}/src/config)
