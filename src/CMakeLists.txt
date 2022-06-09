cmake_minimum_required(VERSION 3.16)
project(dsa_lib CXX)

include_directories(
        ${CMAKE_SOURCE_DIR}/src/DataStructure
)

add_subdirectory(DataStructure/Bitmap)
add_subdirectory(DataStructure/Example)

add_executable(dsa dsa.cpp)

target_link_libraries(dsa bitmap)
target_link_libraries(dsa example)
