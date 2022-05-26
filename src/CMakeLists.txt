project(dsa_lib CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${CMAKE_SOURCE_DIR}/src/DataStructure
)

add_subdirectory(DataStructure/Bitmap)
add_subdirectory(DataStructure/Example)

add_executable(dsa dsa.cpp)

target_link_libraries(dsa bitmap)
target_link_libraries(dsa example)
