cmake_minimum_required(VERSION 3.16)
project(912-dsa CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/internal_utils.cmake)
enable_testing()


add_subdirectory(lib/catch2)
add_subdirectory(lib/fmt)

add_subdirectory(exercise)
add_subdirectory(src)
add_subdirectory(test)