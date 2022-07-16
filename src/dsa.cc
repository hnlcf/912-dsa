#include <ds/vector.h>

int main() {
  dsa::Vector<const char*> str = {"hello", "world", "912-dsa", "!!!"};

  for (auto& s : str) {
    std::cout << s << " ";
  }
  std::cout << '\n';

  return 0;
}
