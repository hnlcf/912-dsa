#define CATCH_CONFIG_MAIN
#include "Vector.hpp"
#include "catch2/catch_test_macros.hpp"

using dsa::Iterator;
using dsa::Vector;

TEST_CASE("Vector: constructor", "[vector]") {
    SECTION("Default constructor with empty initialization") {
        Vector<int> v;
        REQUIRE(v.isEmpty());
        REQUIRE(v.size() == 0);
        REQUIRE(v.capacity() == 3);
    }

    SECTION("Constructor with initializer list") {
        Vector<int> v{ 0, 1, 2, 3 };
        REQUIRE_FALSE(v.isEmpty());
        REQUIRE(v.size() == 4);
        REQUIRE(v.capacity() == 8);
        REQUIRE(v.front() == 0);
        REQUIRE(v.back() == 3);
    }

    SECTION("Constructor by specifying size and default value") {
        Vector<int> v(3, -1);
        REQUIRE(!v.isEmpty());
        REQUIRE(v.size() == 3);
        REQUIRE(v.capacity() == 6);
        REQUIRE(v.front() == -1);
        REQUIRE(v.back() == -1);
    }

    SECTION("Constructor by specifying  capacity, size and default value") {
        Vector<int> v(6, 3, 1);
        REQUIRE(!v.isEmpty());
        REQUIRE(v.size() == 3);
        REQUIRE(v.capacity() == 6);
        REQUIRE(v.front() == 1);
        REQUIRE(v.back() == 1);
    }

    SECTION("Construct with a raw array") {
        int         arr[] = { 5, 4, 3, 2, 1 };
        Vector<int> v1(arr, 5);
        REQUIRE(!v1.isEmpty());
        REQUIRE(v1.size() == 5);
        REQUIRE(v1.capacity() == 10);
        REQUIRE(v1.front() == 5);
        REQUIRE(v1.back() == 1);

        Vector<int> v2(arr, 1, 5);
        REQUIRE(!v2.isEmpty());
        REQUIRE(v2.size() == 4);
        REQUIRE(v2.capacity() == 8);
        REQUIRE(v2.front() == 4);
        REQUIRE(v2.back() == 1);
    }

    SECTION("Copy constructor") {
        Vector<int> v1{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

        Vector<int> v2(v1);
        REQUIRE(v1 == v2);
        REQUIRE(!v2.isEmpty());
        REQUIRE(v2.size() == 10);
        REQUIRE(v2.capacity() == 20);
        REQUIRE(v2.front() == 9);
        REQUIRE(v2.back() == 0);

        Vector<int> v3(v1, 2, 8);
        REQUIRE(!v3.isEmpty());
        REQUIRE(v3.size() == 6);
        REQUIRE(v3.capacity() == 12);
        REQUIRE(v3.front() == 7);
        REQUIRE(v3.back() == 2);
    }
}

TEST_CASE("Vector: iterator", "[vector]") {
    SECTION("Begin and end") {
        Vector<int> v{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

        Iterator<int> it = v.begin();
        REQUIRE(*it == 9);

        *it = 99;
        REQUIRE(v[0] == 99);
        REQUIRE(!v.isEmpty());
        REQUIRE(v.size() == 10);
        REQUIRE(v.capacity() == 20);
        REQUIRE(v.front() == 99);
        REQUIRE(v.back() == 0);

        it = v.end() - 1;
        REQUIRE(*it == 0);
    }
}

TEST_CASE("Vector: add, remove and get element operations", "[vector]") {
    SECTION("Append an element from tail, push_back") {
        Vector<int> v;
        REQUIRE(v.isEmpty());
        REQUIRE(v.size() == 0);
        REQUIRE(v.capacity() == 3);

        v.push_back(1);
        REQUIRE(!v.isEmpty());
        REQUIRE(v.size() == 1);
        REQUIRE(v.capacity() == 3);

        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        REQUIRE(!v.isEmpty());
        REQUIRE(v.size() == 4);
        REQUIRE(v.capacity() == 6);
    }

    SECTION("Remove an element from tail, pop_back") {
        Vector<int> v{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
        REQUIRE(!v.isEmpty());
        REQUIRE(v.size() == 10);
        REQUIRE(v.capacity() == 20);
        REQUIRE(v.front() == 9);
        REQUIRE(v.back() == 0);

        auto tmp = v.pop_back();
        REQUIRE(tmp == 0);
        REQUIRE(!v.isEmpty());
        REQUIRE(v.size() == 9);
        REQUIRE(v.capacity() == 20);
        REQUIRE(v.front() == 9);
        REQUIRE(v.back() == 1);

        for (std::size_t i = 0; i < 3; ++i) {
            v.pop_back();
        }
        REQUIRE(!v.isEmpty());
        REQUIRE(v.size() == 6);
        REQUIRE(v.capacity() == 20);
        REQUIRE(v.front() == 9);
        REQUIRE(v.back() == 4);

        v.pop_back();
        REQUIRE(!v.isEmpty());
        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() == 10);
        REQUIRE(v.front() == 9);
        REQUIRE(v.back() == 5);
    }

    SECTION("Get the element in head, front") {
        Vector<int> v{ 4, 3, 2, 1, 0 };
        REQUIRE(!v.isEmpty());
        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() == 10);

        v.front() = 99;
        REQUIRE(v.at(0) == 99);
        REQUIRE(v.at(v.size() - 1) == 0);
    }

    SECTION("Get the element in tail, back") {
        Vector<int> v{ 4, 3, 2, 1, 0 };
        REQUIRE(!v.isEmpty());
        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() == 10);

        v.back() = 99;
        REQUIRE(v.at(0) == 4);
        REQUIRE(v.at(v.size() - 1) == 99);
    }

    SECTION("Get the element in any pos, at") {
        Vector<int> v{ 4, 3, 2, 1, 0 };
        REQUIRE(!v.isEmpty());
        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() == 10);

        v.at(0) = 0;
        v.at(1) = 1;
        v.at(2) = 2;
        v.at(3) = 3;
        v.at(4) = 4;
        REQUIRE(v[0] == 0);
        REQUIRE(v[1] == 1);
        REQUIRE(v[2] == 2);
        REQUIRE(v[3] == 3);
        REQUIRE(v[4] == 4);
    }

    SECTION("Insert an element in any pos, insert") {
        Vector<int> v{ 4, 3, 2, 1, 0 };
        REQUIRE(!v.isEmpty());
        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() == 10);
        REQUIRE(v.front() == 4);
        REQUIRE(v.back() == 0);

        v.insert(0, 99);
        REQUIRE(v.size() == 6);
        REQUIRE(v.capacity() == 10);
        REQUIRE(v.at(0) == 99);
        REQUIRE(v.at(1) == 4);
        REQUIRE(v.at(5) == 0);

        v.insert(4, 22);
        REQUIRE(v.size() == 7);
        REQUIRE(v.capacity() == 10);
        REQUIRE(v[4] == 22);
        REQUIRE(v[5] == 1);
        REQUIRE(v[6] == 0);

        v.insert(6, -1);
        REQUIRE(v.size() == 8);
        REQUIRE(v.capacity() == 10);
        REQUIRE(v[6] == -1);
        REQUIRE(v[7] == 0);

        v.insert(8, -99);
        REQUIRE(v.size() == 9);
        REQUIRE(v.capacity() == 10);
        REQUIRE(v[8] == -99);

        Vector<int> v2{ 99, 4, 3, 2, 22, 1, -1, 0, -99 };
        REQUIRE(v == v2);
    }
}
