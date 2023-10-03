set(test_name libsum.test)
add_executable(
  ${test_name}
  ${test_name}.cpp
)

set_compile_options(${test_name})

target_include_directories(
  ${test_name}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(
  ${test_name}
  GTest::gtest_main
  libsum
)

include(GoogleTest)
gtest_discover_tests(${test_name})
