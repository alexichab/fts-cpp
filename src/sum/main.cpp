#include <CLI/CLI.hpp>
#include <iostream>
#include <libsum/libsum.hpp>

int main(int argc, char **argv) {
  CLI::App app{"sum"};
  double a = 0;
  double b = 0;
  app.add_option("-a", a, "Double");
  app.add_option("-b", b, "Double");
  CLI11_PARSE(app, argc, argv);
  std::cout << sum::sum(a, b) << '\n';
  return 0;
}
