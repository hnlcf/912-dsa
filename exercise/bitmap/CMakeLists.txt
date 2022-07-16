include_directories(
        "."
        )

add_library(bitmap)
target_include_directories(bitmap PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
)
target_sources(bitmap PRIVATE
        bitmap.cc
        bitmap_quickinit.cc
        )
