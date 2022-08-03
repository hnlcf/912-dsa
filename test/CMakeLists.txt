set(DSA_TEST_NAME dsa_test)

add_executable(${DSA_TEST_NAME})
target_compile_options(${DSA_TEST_NAME} PUBLIC
        "-Werror")
target_sources(${DSA_TEST_NAME} PRIVATE
        "test_header.h"
        "test_main.cc"
        "basic/test_vector.cc"
        "basic/test_list.cc"
        "basic/test_stack.cc"
        "basic/test_queue.cc"
        "tree/test_avl.cc"
        "tree/test_bintree.cc"
        "tree/test_bst.cc"
        "tree/test_btree.cc"
        "tree/test_splaytree.cc"
        "graph/test_graph.cc"
        "graph/test_graph_matrix.cc"
        )
target_include_directories(${DSA_TEST_NAME} PRIVATE
        "${CMAKE_SOURCE_DIR}/test"
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/exercise"
        "${CMAKE_SOURCE_DIR}/lib/catch2"
        )
target_link_libraries(${DSA_TEST_NAME} PRIVATE bitmap example Catch2::Catch2WithMain)

## Global Test Case
add_test(NAME ${DSA_TEST_NAME} COMMAND ${DSA_TEST_NAME})
