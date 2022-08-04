include_directories(
        "."
        )

add_library(example)
target_include_directories(example PRIVATE
        ${CMAKE_SOURCE_DIR}/exercise
)
target_sources(example PRIVATE
        stackexample.cc
        )
