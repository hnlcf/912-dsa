cmake_minimum_required(VERSION 3.16)
project(dsa-test)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/test
        ${CMAKE_SOURCE_DIR}/exercise
        ${CMAKE_SOURCE_DIR}/lib/catch2/src
        ${CMAKE_SOURCE_DIR}/lib/fmt/include
)

file(GLOB_RECURSE src_files "${CMAKE_SOURCE_DIR}/test/**.cc")
file(GLOB_RECURSE inc_files "${CMAKE_SOURCE_DIR}/test/**.h")

foreach (file ${src_files} ${inc_files})
    message("-- [${PROJECT_NAME}]: ${file}")
endforeach ()

add_executable(${PROJECT_NAME})
target_compile_options(${PROJECT_NAME} PUBLIC
        -Wall
        -Wextra
        -Wpedantic
        )
target_sources(${PROJECT_NAME} PRIVATE
        ${src_files}
        ${inc_files}
        )
target_link_libraries(${PROJECT_NAME} PRIVATE bitmap example Catch2::Catch2WithMain fmt::fmt)

## Global Test Case
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
