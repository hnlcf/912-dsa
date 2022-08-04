cmake_minimum_required(VERSION 3.16)
project(exercise)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/lib/fmt/include
)

add_subdirectory(bitmap)
add_subdirectory(stack)

