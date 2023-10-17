set(target_name parser)

add_executable(
  ${target_name}
  main.cpp
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
