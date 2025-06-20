if (PROJECT_IS_TOP_LEVEL)
    cmake_minimum_required(VERSION 3.20)
    project(libOS-api C)
endif()

# By default, all features off. This will very clearly signal to the user that something is wrong. In other words:
# they forgot to initialize the options of the libOS library.
option(LIBOS_MUTEX_ENABLE_RECURSIVE "Enable recursive mutexes" OFF)
option(LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION "Enable dynamic allocation of structures using malloc/free" OFF)
option(LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION "Enable static allocation of structures" OFF)

set(API_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/error.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/time.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/log.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/concurrency/mutex.h"
)

add_library(libOS-api INTERFACE ${API_SRCS})
target_include_directories(libOS-api INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

if (COMMAND convert_option_to_definition)
    # Hope they have the same signature....
else()
    function(convert_option_to_definition target cmake_var macro_name)
        if (${cmake_var})
            target_compile_definitions(${target} INTERFACE ${macro_name}=1)
        else()
            target_compile_definitions(${target} INTERFACE ${macro_name}=0)
        endif()
    endfunction()
endif()

convert_option_to_definition(libOS-api LIBOS_MUTEX_ENABLE_RECURSIVE LIBOS_MUTEX_ENABLE_RECURSIVE)
convert_option_to_definition(libOS-api LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION)
convert_option_to_definition(libOS-api LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION)

if (${BUILD_TESTING})
    enable_testing()
    add_subdirectory(tests)
endif()
