project(dsa_lib CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${CMAKE_SOURCE_DIR}/src/DataStructure
)
add_executable(dsa dsa.cpp)
