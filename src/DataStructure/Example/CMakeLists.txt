include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )

add_library(example)
target_sources(example PRIVATE
        StackExample.cpp
        )
