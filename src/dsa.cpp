//
// Created by changfeng on 2022/4/18.
//

#include "Vector.hpp"
#include <iostream>

int
main(int argc, char **argv) {
    dsa::Vector<int> v{ 1, 2, 3, 4, 5, 6 };
    v.insert(6, 99);
    auto s = v.size();
    std::cout << s << std::endl;
    return 0;
}
