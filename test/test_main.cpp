#include <test_header.hpp>

int
main(int argc, const char **argv) {
  int result = Catch::Session().run(argc, argv);

  return result;
}
