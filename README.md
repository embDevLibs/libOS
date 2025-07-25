# libOS
A abstraction layer with implementations for basic OS operations, like time, but also mutexes.
It is meant to unify the API across several (RT)OSes and bare metal such that components can be written once, and then used on several platforms.
This could greatly reduce maintenance effort for specific ports for each platform.

With the OS abstraction also comes the benefit that it is much easier to develop a component on a desktop, since that is just another platform implementation.
This is why, besides bare metal, also desktop platform(s) should be supported.

# Documentation
Each API is extensively documented in it's header file.
This is in Doxygen format to support the automatic generation of documentation pages.

# Usage
This implementation can be used in two ways.
One is by using the pure CMake system.
This is by using FetchContent, or ExternalProject or just a plain git submodule with add_subdirectory to fetch the sources.
Make sure that if you need to setup any configuration (ie `LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION`), you pass this along using the correct mechanism.
Then, when added to cmake, you can just use the target 'libSO' to link against.
A copy of libOS will be downloaded using FetchContent if the libOS target isn't already present.

The second method is by the using the IDF Component manager from Espressif.
This method is aimed specifically as the ESP-IDF development ecosystem.
You can use the regular dependency system to get your copy of the library.
Configurations, like enable/disabling dynamic allocation can be done using menuconfig functionality of ESP-IDF.
Make sure that they are properly configured for the platform implementation that you are using.

# Implementation
The OS abstraction library implementation is meant to be link-time provided.
There is no native option to change the implementation during runtime.
Each platform implementation provides the C functions that are declared in the API's header, and if the API documents, any headers that might be needed.

# Testing
Some parts of the API can already be tested since they provide a default implementation (that can be augmented if platform specific optimisations exist).
These tests are written using the ctest framework.
The tests themselves live in the test directory.
Since the usage of API's require the presence of some headers, the 'inc' directory in the 'tests' directory also act as include directory specifically for the tests.
Any 'platform' specific header can be placed there.
The tests cannot depend on a platform specific implementation of the API, those tests should live in the implementations repository.

# Cross-buildsystem building
To facilitate cmake scripting for different build systems, the top-level cmake includes different '.cmake' files.
Generally, the `<platform>.cmake` provides 2 variables, 'LIBOS_PROJECT' to enable/disable the top level project statement, and
LIBOS_POST_INCLUDE, the variable that contains the name in the 'platform/cmake' directory to what file to include at the end of the top level cmake.
Currently, there is only very little in the 'common' cmake setup, but this might change in the future.
Each platform specific file should make sure that is can setup the defines and the targets for the proper functioning of the libOS library.
Look at the 'generic' or 'esp' (for ESP-IDF) for examples on how to do this.
