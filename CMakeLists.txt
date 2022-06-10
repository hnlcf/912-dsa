cmake_minimum_required(VERSION 3.16)
project(912-dsa CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Werror")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

set(
        TEST_SRC
        test/test_vector.cpp
        test/test_list.cpp
        test/test_stack.cpp
        test/test_queue.cpp
        test/test_tree.cpp
        test/test_graph.cpp
        test/test_graph_martix.cpp
)

add_executable(dsa_all_test ${TEST_SRC})

target_include_directories(dsa_all_test PUBLIC
        src/DataStructure
        lib/catch2
        )

target_link_libraries(dsa_all_test PRIVATE bitmap)
target_link_libraries(dsa_all_test PRIVATE example)

add_subdirectory(lib/catch2)

target_link_libraries(dsa_all_test PRIVATE Catch2::Catch2WithMain)

enable_testing()

function(dsa_test test_file)
    get_filename_component(test_target_name "${test_file}" NAME_WE)

    add_executable("${test_target_name}" "")
    target_sources("${test_target_name}"
            PRIVATE
            "${test_file}"
            )
    target_include_directories("${test_target_name}"
            PUBLIC
            "${CMAKE_SOURCE_DIR}/src/DataStructure"
            "${CMAKE_SOURCE_DIR}/src/DataStructure/Bitmap"
            "${CMAKE_SOURCE_DIR}/src/DataStructure/Example"
            )
    target_link_libraries("${test_target_name}" PRIVATE bitmap example Catch2::Catch2WithMain)
    add_test(NAME "${test_target_name}" COMMAND "${test_target_name}")
endfunction(dsa_test)

add_test(NAME dsa_all_test COMMAND dsa_all_test)
dsa_test("test/test_vector.cpp")
