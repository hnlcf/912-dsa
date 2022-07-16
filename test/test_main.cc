#include <test_header.h>

int main(int argc, const char** argv) {
  int result = Catch::Session().run(argc, argv);

  return result;
}
