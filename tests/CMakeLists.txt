
if(NOT TARGET ctest) # Prevent multiple instances if other libraries already provide the ctest library
    include(FetchContent)
    FetchContent_Declare(
        ctestsrc
        GIT_REPOSITORY git@github.com:bvdberg/ctest
        GIT_TAG master
        
        # The CMakeLists.txt in the root is for building the example.
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
    )
    FetchContent_MakeAvailable(ctestsrc)
    add_library(ctest STATIC ${ctestsrc_SOURCE_DIR}/main.c)
    target_include_directories(ctest PUBLIC ${ctestsrc_SOURCE_DIR})
    target_compile_options(ctest PUBLIC -DCTEST_COLOR_OK)

endif()

set(SRCS
    "bits.c"
)

add_executable(libos-testing ${SRCS})
target_include_directories(libos-testing PUBLIC ./inc/)
target_link_libraries(libos-testing PUBLIC libOS-api)
target_link_libraries(libos-testing PRIVATE ctest)