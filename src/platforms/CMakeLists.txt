# Implemenation options
option(LIBOS_IMPLEMENATION_STDLIB "Enable the standard library implementation for the OS library." ON)
# option(LIBOS_IMPLEMENATION_PLATFORM1 "Enable the second library implementation for the OS library." OFF)

# Actual implementation selection
if (${LIBOS_IMPLEMENATION_STDLIB})
    add_subdirectory(stdlib)
endif()
