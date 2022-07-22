
set(DSA_LIB_NAME dsa)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
)

add_executable(${DSA_LIB_NAME})
target_include_directories(${DSA_LIB_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/src)
target_sources(${DSA_LIB_NAME} PUBLIC
        "dsa.cc"
        )
