cmake_minimum_required(VERSION 3.16)
project(912-dsa CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Wpedantic")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


###################################! Add Main Library !###################################

add_subdirectory(src)

###################################! Exec Test Target !###################################

add_executable(dsa_all_test)

target_compile_options(dsa_all_test PUBLIC
        "-Werror")

target_sources(dsa_all_test PRIVATE
        "test/test_main.cpp"
        "test/basic/test_vector.cpp"
        "test/basic/test_list.cpp"
        "test/basic/test_stack.cpp"
        "test/basic/test_queue.cpp"
        "test/tree/test_bintree.cpp"
        "test/tree/test_bst.cpp"
        "test/graph/test_graph.cpp"
        "test/graph/test_graph_martix.cpp"
)

target_include_directories(dsa_all_test PRIVATE
        "src/DataStructure"
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
