#include <catch2/catch_session.hpp>      // Catch2 with custom main
#include <catch2/catch_test_macros.hpp>  // Catch2 test macros

int
main(int argc, const char **argv) {
  int result = Catch::Session().run(argc, argv);

  return result;
}

TEST_CASE("912-DSA Catch2 Test", "[912]") {
  REQUIRE(1 + 1 == 2);
}
