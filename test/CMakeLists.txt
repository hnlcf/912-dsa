project(test)

enable_testing()

set(
        TEST_SRC
        test_main.cpp
)

include_directories(
        ${CMAKE_SOURCE_DIR}/src/DataStructure
)
add_executable(test ${TEST_SRC})

target_link_libraries(test gtest gtest_main)

add_test(NAME test COMMAND test)
