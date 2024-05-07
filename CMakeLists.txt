cmake_minimum_required(VERSION 3.20)
project(libOS-api C)

set(API_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/error.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/time.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/log.h"
)

add_library(libOS-api INTERFACE ${API_SRCS})
target_include_directories(libOS-api INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
