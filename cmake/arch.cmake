if (CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64.*|AARCH64.*)")
    set (ARCH_AARCH64 1)
endif ()
if (ARCH_AARCH64 OR CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    set (ARCH_ARM 1)
endif ()
if (CMAKE_LIBRARY_ARCHITECTURE MATCHES "i386")
    set (ARCH_I386 1)
endif ()
if ((ARCH_ARM AND NOT ARCH_AARCH64) OR ARCH_I386)
    set (ARCH_32 1)
    message (FATAL_ERROR "32bit platforms are not supported")
endif ()

if (CMAKE_SYSTEM MATCHES "Linux")
    set (OS_LINUX 1)
endif ()
if (CMAKE_SYSTEM MATCHES "FreeBSD")
    set (OS_FREEBSD 1)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (COMPILER_GCC 1)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set (COMPILER_CLANG 1)
endif ()

if (CMAKE_SYSTEM_PROCESSOR MATCHES "^(ppc64le.*|PPC64LE.*)")
    set (ARCH_PPC64LE 1)
    if (COMPILER_CLANG OR (COMPILER_GCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8))
        message(FATAL_ERROR "Only gcc-8 is supported for powerpc architecture")
    endif ()
endif ()