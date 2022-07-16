include_directories(
        "."
        )

add_library(example)
target_sources(example PRIVATE
        stackexample.cc
        )
