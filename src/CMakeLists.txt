
cmake_minimum_required(VERSION 3.16)
project(dsa CXX)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
)

add_executable(dsa)
target_include_directories(dsa PUBLIC
        ${CMAKE_SOURCE_DIR}/src)
target_sources(dsa PUBLIC
        "dsa.cc"
        )
