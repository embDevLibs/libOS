# Library itself
add_library(libOS INTERFACE)
target_include_directories(libOS INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/api")

# Implementations
option(LIBOS_IMPLEMENTATION_ENABLED "Enable one of the build-in implementations of the API. If you don't enable one, you should provide one of your own." ON)

if (${LIBOS_IMPLEMENTATION_ENABLED})
    add_subdirectory(platforms)
endif()
