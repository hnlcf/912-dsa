include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )

add_library(bitmap)
target_sources(bitmap PRIVATE
        Bitmap.cpp
        BitmapQuickInit.cpp
        )
