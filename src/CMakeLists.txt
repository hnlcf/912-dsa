cmake_minimum_required(VERSION 3.16)
project(dsa)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/lib/fmt/include
)

file(GLOB_RECURSE src_files "${CMAKE_SOURCE_DIR}/src/**.cc")
file(GLOB_RECURSE inc_files "${CMAKE_SOURCE_DIR}/src/**.h")

foreach (file ${src_files} ${inc_files})
    message("-- [${PROJECT_NAME}]: ${file}")
endforeach ()

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PUBLIC
        ${src_files}
        ${inc_files}
        )
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
