cmake_minimum_required(VERSION 3.20)

#
# Common to all platforms code
#

if (ESP_PLATFORM)
    include(${CMAKE_CURRENT_LIST_DIR}/platform/cmake/esp.cmake)
else()
    include(${CMAKE_CURRENT_LIST_DIR}/platform/cmake/generic.cmake)
endif()


if (${LIBOS_PROJECT})
    project(libOS)
endif()

#
# Do the post setup
#

if (NOT ${LIBOS_POST_INCLUDE} STREQUAL "")
    include(${CMAKE_CURRENT_LIST_DIR}/platform/cmake/${LIBOS_POST_INCLUDE})
endif()
