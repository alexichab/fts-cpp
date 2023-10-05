set(target_name sum)

add_executable(
  ${target_name}
  main.cpp
)

set_compile_options(${target_name})

target_include_directories(
  ${target_name}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/external/cli11

)

target_link_libraries(
  ${target_name}
  PRIVATE
    libsum
)
