cmake_minimum_required(VERSION 3.16)
project(test CXX)

set(
        TEST_SRC
        test_vector.cpp
        test_list.cpp
        test_stack.cpp
        test_queue.cpp
)

include_directories(
        ${CMAKE_SOURCE_DIR}/src/DataStructure
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)

add_executable(test ${TEST_SRC})

target_link_libraries(test bitmap)
target_link_libraries(test example)
target_link_libraries(test ${CONAN_LIBS})
