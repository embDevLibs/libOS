# Library itself
add_subdirectory(api)

# Implementations
option(LIBOS_IMPLEMENTATION_ENABLED "Enable one of the build-in implementations of the API. If you don't enable one, you should provide one of your own." ON)

add_library(libOS INTERFACE)

if(${LIBOS_IMPLEMENTATION_ENABLED})
    add_subdirectory(platforms)
    target_link_libraries(libOS INTERFACE libOS-platform)
endif()

target_link_libraries(libOS INTERFACE libOS-api)
