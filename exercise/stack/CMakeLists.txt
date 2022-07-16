include_directories(
        "."
        )

add_library(example)
target_include_directories(example PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
)
target_sources(example PRIVATE
        stackexample.cc
        )
