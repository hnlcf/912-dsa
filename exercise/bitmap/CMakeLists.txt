include_directories(
        "."
        )

add_library(bitmap)
target_sources(bitmap PRIVATE
        bitmap.cc
        bitmap_quickinit.cc
        )
