#include <test_header.h>

using dsa::Iterator;
using dsa::Vector;

TEST_CASE("Vector: constructor", "[vector]") {
  SECTION("Default constructor with empty initialization") {
    Vector<int> v;
    REQUIRE(v.IsEmpty());
    REQUIRE(v.Size() == 0);
    REQUIRE(v.Capacity() == 3);
  }

  SECTION("Constructor with initializer list") {
    Vector<int> v{0, 1, 2, 3};
    REQUIRE_FALSE(v.IsEmpty());
    REQUIRE(v.Size() == 4);
    REQUIRE(v.Capacity() == 8);
    REQUIRE(v.Front() == 0);
    REQUIRE(v.Back() == 3);
  }

  SECTION("Constructor by specifying Size and default value") {
    Vector<int> v(3, -1);
    REQUIRE(!v.IsEmpty());
    REQUIRE(v.Size() == 3);
    REQUIRE(v.Capacity() == 6);
    REQUIRE(v.Front() == -1);
    REQUIRE(v.Back() == -1);
  }

  SECTION("Constructor by specifying  Capacity, Size and default value") {
    Vector<int> v(6, 3, 1);
    REQUIRE(!v.IsEmpty());
    REQUIRE(v.Size() == 3);
    REQUIRE(v.Capacity() == 6);
    REQUIRE(v.Front() == 1);
    REQUIRE(v.Back() == 1);
  }

  SECTION("Construct with a raw array") {
    int arr[] = {5, 4, 3, 2, 1};
    Vector<int> v1(arr, 5);
    REQUIRE(!v1.IsEmpty());
    REQUIRE(v1.Size() == 5);
    REQUIRE(v1.Capacity() == 10);
    REQUIRE(v1.Front() == 5);
    REQUIRE(v1.Back() == 1);

    Vector<int> v2(arr, 1, 5);
    REQUIRE(!v2.IsEmpty());
    REQUIRE(v2.Size() == 4);
    REQUIRE(v2.Capacity() == 8);
    REQUIRE(v2.Front() == 4);
    REQUIRE(v2.Back() == 1);
  }

  SECTION("Copy constructor") {
    Vector<int> v1{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    Vector<int> v2(v1);
    REQUIRE(v1 == v2);
    REQUIRE(!v2.IsEmpty());
    REQUIRE(v2.Size() == 10);
    REQUIRE(v2.Capacity() == 20);
    REQUIRE(v2.Front() == 9);
    REQUIRE(v2.Back() == 0);

    Vector<int> v3(v1, 2, 8);
    REQUIRE(!v3.IsEmpty());
    REQUIRE(v3.Size() == 6);
    REQUIRE(v3.Capacity() == 12);
    REQUIRE(v3.Front() == 7);
    REQUIRE(v3.Back() == 2);
  }
}

TEST_CASE("Vector: iterator", "[vector]") {
  SECTION("Begin and end") {
    Vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    Iterator<int> it = v.begin();
    REQUIRE(*it == 9);

    *it = 99;
    REQUIRE(v[0] == 99);
    REQUIRE(!v.IsEmpty());
    REQUIRE(v.Size() == 10);
    REQUIRE(v.Capacity() == 20);
    REQUIRE(v.Front() == 99);
    REQUIRE(v.Back() == 0);

    it = v.end() - 1;
    REQUIRE(*it == 0);
  }
}

TEST_CASE("Vector: add, Remove and Get element operations", "[vector]") {
  SECTION("Append an element from tail, PushBack") {
    Vector<int> v;
    REQUIRE(v.IsEmpty());
    REQUIRE(v.Size() == 0);
    REQUIRE(v.Capacity() == 3);

    v.PushBack(1);
    REQUIRE(!v.IsEmpty());
    REQUIRE(v.Size() == 1);
    REQUIRE(v.Capacity() == 3);

    v.PushBack(2);
    v.PushBack(3);
    v.PushBack(4);
    REQUIRE(!v.IsEmpty());
    REQUIRE(v.Size() == 4);
    REQUIRE(v.Capacity() == 6);
  }

  SECTION("Remove an element from tail, PopBack") {
    Vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    REQUIRE(!v.IsEmpty());
    REQUIRE(v.Size() == 10);
    REQUIRE(v.Capacity() == 20);
    REQUIRE(v.Front() == 9);
    REQUIRE(v.Back() == 0);

    auto tmp = v.PopBack();
    REQUIRE(tmp == 0);
    REQUIRE(!v.IsEmpty());
    REQUIRE(v.Size() == 9);
    REQUIRE(v.Capacity() == 20);
    REQUIRE(v.Front() == 9);
    REQUIRE(v.Back() == 1);

    for (std::size_t i = 0; i < 3; ++i) {
      v.PopBack();
    }
    REQUIRE(!v.IsEmpty());
    REQUIRE(v.Size() == 6);
    REQUIRE(v.Capacity() == 20);
    REQUIRE(v.Front() == 9);
    REQUIRE(v.Back() == 4);

    v.PopBack();
    REQUIRE(!v.IsEmpty());
    REQUIRE(v.Size() == 5);
    REQUIRE(v.Capacity() == 10);
    REQUIRE(v.Front() == 9);
    REQUIRE(v.Back() == 5);
  }

  SECTION("Get the element in head, Front") {
    Vector<int> v{4, 3, 2, 1, 0};
    REQUIRE(!v.IsEmpty());
    REQUIRE(v.Size() == 5);
    REQUIRE(v.Capacity() == 10);

    v.Front() = 99;
    REQUIRE(v.At(0) == 99);
    REQUIRE(v.At(v.Size() - 1) == 0);
  }

  SECTION("Get the element in tail, Back") {
    Vector<int> v{4, 3, 2, 1, 0};
    REQUIRE(!v.IsEmpty());
    REQUIRE(v.Size() == 5);
    REQUIRE(v.Capacity() == 10);

    v.Back() = 99;
    REQUIRE(v.At(0) == 4);
    REQUIRE(v.At(v.Size() - 1) == 99);
  }

  SECTION("Get the element in any pos, At") {
    Vector<int> v{4, 3, 2, 1, 0};
    REQUIRE(!v.IsEmpty());
    REQUIRE(v.Size() == 5);
    REQUIRE(v.Capacity() == 10);

    v.At(0) = 0;
    v.At(1) = 1;
    v.At(2) = 2;
    v.At(3) = 3;
    v.At(4) = 4;
    REQUIRE(v[0] == 0);
    REQUIRE(v[1] == 1);
    REQUIRE(v[2] == 2);
    REQUIRE(v[3] == 3);
    REQUIRE(v[4] == 4);
  }

  SECTION("Insert an element in any pos, Insert") {
    Vector<int> v{4, 3, 2, 1, 0};
    REQUIRE(!v.IsEmpty());
    REQUIRE(v.Size() == 5);
    REQUIRE(v.Capacity() == 10);
    REQUIRE(v.Front() == 4);
    REQUIRE(v.Back() == 0);

    v.Insert(0, 99);
    REQUIRE(v.Size() == 6);
    REQUIRE(v.Capacity() == 10);
    REQUIRE(v.At(0) == 99);
    REQUIRE(v.At(1) == 4);
    REQUIRE(v.At(5) == 0);

    v.Insert(4, 22);
    REQUIRE(v.Size() == 7);
    REQUIRE(v.Capacity() == 10);
    REQUIRE(v[4] == 22);
    REQUIRE(v[5] == 1);
    REQUIRE(v[6] == 0);

    v.Insert(6, -1);
    REQUIRE(v.Size() == 8);
    REQUIRE(v.Capacity() == 10);
    REQUIRE(v[6] == -1);
    REQUIRE(v[7] == 0);

    v.Insert(8, -99);
    REQUIRE(v.Size() == 9);
    REQUIRE(v.Capacity() == 10);
    REQUIRE(v[8] == -99);

    Vector<int> v2{99, 4, 3, 2, 22, 1, -1, 0, -99};
    REQUIRE(v == v2);
  }
}
