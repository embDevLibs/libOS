# By default, all features on. This is what the most generic situation support usually.
option(LIBOS_ENABLE_TESTING "Enable unit tests" OFF)
option(LIBOS_MUTEX_ENABLE_RECURSIVE "Enable recursive mutexes" ON)
option(LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION "Enable dynamic allocation of structures using malloc/free" ON)
option(LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION "Enable static allocation of structures" ON)

set(LIBOS_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/error.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/time.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/log.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/concurrent/mutex.h"
)

add_library(${PROJECT_NAME} INTERFACE ${LIBOS_SRCS})
target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

if (NOT COMMAND libos_option_to_definition)
    function(libos_option_to_definition target cmake_var macro_name)
        if (${cmake_var})
            target_compile_definitions(${target} INTERFACE ${macro_name}=1)
        else()
            target_compile_definitions(${target} INTERFACE ${macro_name}=0)
        endif()
    endfunction()
endif()

libos_option_to_definition(${PROJECT_NAME} LIBOS_MUTEX_ENABLE_RECURSIVE LIBOS_MUTEX_ENABLE_RECURSIVE)
libos_option_to_definition(${PROJECT_NAME} LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION)
libos_option_to_definition(${PROJECT_NAME} LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION)

if (${LIBOS_ENABLE_TESTING})
    enable_testing()
    add_subdirectory(tests)
endif()
