set(STDLIB_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/time.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/log.c"
)

add_library(libOS-platform STATIC "${STDLIB_SRCS}")
target_include_directories(libOS-platform PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(libOS-platform libOS)
