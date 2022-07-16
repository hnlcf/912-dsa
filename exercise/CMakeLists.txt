cmake_minimum_required(VERSION 3.16)
project(exercise CXX)

include_directories(
        ${CMAKE_SOURCE_DIR}/src/ds
)

add_subdirectory(bitmap)
add_subdirectory(stack)

