cmake_minimum_required(VERSION 3.16)
project(912-dsa CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Wpedantic")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


###################################! Add Main Library !###################################

add_subdirectory(exercise)

###################################! Exec Test Target !###################################

add_executable(dsa_all_test)

target_compile_options(dsa_all_test PUBLIC
        "-Werror")

target_sources(dsa_all_test PRIVATE
        "test/test_header.h"
        "test/test_main.cc"
        "test/basic/test_vector.cc"
        "test/basic/test_list.cc"
        "test/basic/test_stack.cc"
        "test/basic/test_queue.cc"
        "test/tree/test_bintree.cc"
        "test/tree/test_bst.cc"
        "test/tree/test_avl.cc"
        "test/graph/test_graph.cc"
        "test/graph/test_graph_martix.cc"
        )

target_include_directories(dsa_all_test PRIVATE
        "test"
        "src/ds"
        "exercise"
        "lib/catch2"
        )

target_link_libraries(dsa_all_test PRIVATE bitmap example)

add_subdirectory(lib/catch2)
target_link_libraries(dsa_all_test PRIVATE Catch2::Catch2WithMain)


###################################! Enable CMake Test !###################################

enable_testing()

## Global Test Case
add_test(NAME dsa_all_test COMMAND dsa_all_test)

## Custom Test Function
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
