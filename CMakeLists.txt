cmake_minimum_required(VERSION 3.3)
project(TestPOCO)

#foreach(policy
#        CMP0023
#        CMP0074 # CMake 3.12
#        )
#    if(POLICY ${policy})
#        cmake_policy(SET ${policy} NEW)
#    endif()
#endforeach()
#
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
#set(CMAKE_EXPORT_COMPILE_COMMANDS 1) # Write compile_commands.json
#set(CMAKE_LINK_DEPENDS_NO_SHARED 1) # Do not relink all depended targets on .so
#set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo;Debug;Release;MinSizeRel" CACHE STRING "" FORCE)
#set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Generate debug library name with a postfix.")    # To be consistent with CMakeLists from contrib libs.
#
#include (cmake/arch.cmake)
#
#option(ENABLE_IPO "Enable inter-procedural optimization (aka LTO)" OFF) # need cmake 3.9+
#if(ENABLE_IPO)
#    cmake_policy(SET CMP0069 NEW)
#    include(CheckIPOSupported)
#    check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT IPO_NOT_SUPPORTED)
#    if(IPO_SUPPORTED)
#        message(STATUS "IPO/LTO is supported, enabling")
#        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
#    else()
#        message(STATUS "IPO/LTO is not supported: <${IPO_NOT_SUPPORTED}>")
#    endif()
#else()
#    message(STATUS "IPO/LTO not enabled.")
#endif()
#
#if (COMPILER_GCC)
#    # Require at least gcc 7
#    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7 AND NOT CMAKE_VERSION VERSION_LESS 2.8.9)
#        message (FATAL_ERROR "GCC version must be at least 7. For example, if GCC 7 is available under gcc-7, g++-7 names, do the following: export CC=gcc-7 CXX=g++-7; rm -rf CMakeCache.txt CMakeFiles; and re run cmake or ./release.")
#    endif ()
#elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#    # Require at least clang 6
#    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6)
#        message (FATAL_ERROR "Clang version must be at least 6.")
#    endif ()
#else ()
#    message (WARNING "You are using an unsupported compiler. Compilation has only been tested with Clang 6+ and GCC 7+.")
#endif ()
#

#
#set (USE_INTERNAL_POCO_LIBRARY 1)
#set (USE_INTERNAL_ZLIB_LIBRARY 1)
#
#
#add_subdirectory (contrib EXCLUDE_FROM_ALL)
#
#include (cmake/find_zlib.cmake)
#include (cmake/find_poco.cmake)
#
#
#add_executable(TestPOCO main.cpp)


set(CMAKE_CXX_STANDARD 11)
set (USE_INTERNAL_POCO_LIBRARY 1)
set (USE_INTERNAL_ZLIB_LIBRARY 1)
include (cmake/find_zlib.cmake)
include (cmake/find_poco.cmake)
add_subdirectory (contrib EXCLUDE_FROM_ALL)
add_executable(testpoco main.cpp)
#add_library (testpoco main.cpp)
target_link_libraries (testpoco
        PUBLIC
        ${ZLIB_LIBRARIES}
        ${Poco_Net_LIBRARY}
        ${Poco_Util_LIBRARY}
        ${Poco_Foundation_LIBRARY}
        )
