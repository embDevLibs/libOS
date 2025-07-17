set(LIBOS_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/error.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/time.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/log.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/libos/concurrent/mutex.h"
)

idf_component_register(SRCS ${LIBOS_SRCS}
                       INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

if (NOT COMMAND convert_config_to_target)
    function(convert_config_to_target var_name)
        if ("${CONFIG_${var_name}}" STREQUAL "y")
            target_compile_definitions(${COMPONENT_LIB} PUBLIC ${var_name}=1)
        else()
            target_compile_definitions(${COMPONENT_LIB} PUBLIC ${var_name}=0)
        endif()
    endfunction()
endif()

convert_config_to_target(LIBOS_MUTEX_ENABLE_RECURSIVE)
convert_config_to_target(LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION)
convert_config_to_target(LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION)

if (${CONFIG_LIBOS_ENABLE_TESTING})
    enable_testing()
    add_subdirectory(tests)
endif()
