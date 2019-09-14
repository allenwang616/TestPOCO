# Third-party libraries may have substandard code.

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++1z")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++1z")
endif ()

set_property(DIRECTORY PROPERTY EXCLUDE_FROM_ALL 1)

if (USE_INTERNAL_POCO_LIBRARY)
    set (POCO_VERBOSE_MESSAGES 0 CACHE INTERNAL "")
    set (save_CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    set (save_CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
    set (_save ${ENABLE_TESTS})
    set (ENABLE_TESTS 0)
    set (POCO_ENABLE_TESTS 0)
    set (CMAKE_DISABLE_FIND_PACKAGE_ZLIB 1)
    if (MSVC OR NOT USE_POCO_DATAODBC)
        set (ENABLE_DATA_ODBC 0 CACHE INTERNAL "") # TODO (build fail)
    endif ()
    add_subdirectory (poco)
    unset (CMAKE_DISABLE_FIND_PACKAGE_ZLIB)
    set (ENABLE_TESTS ${_save})
    set (CMAKE_CXX_FLAGS ${save_CMAKE_CXX_FLAGS})
    set (CMAKE_C_FLAGS ${save_CMAKE_C_FLAGS})

    if (OPENSSL_FOUND AND TARGET Crypto AND (NOT DEFINED ENABLE_POCO_NETSSL OR ENABLE_POCO_NETSSL))
        # Bug in poco https://github.com/pocoproject/poco/pull/2100 found on macos
        target_include_directories(Crypto SYSTEM PUBLIC ${OPENSSL_INCLUDE_DIR})
    endif ()
endif ()


if (USE_INTERNAL_ZLIB_LIBRARY)
    set (ZLIB_ENABLE_TESTS 0 CACHE INTERNAL "")
    set (SKIP_INSTALL_ALL 1 CACHE INTERNAL "")
    set (ZLIB_COMPAT 1 CACHE INTERNAL "") # also enables WITH_GZFILEOP
    set (WITH_NATIVE_INSTRUCTIONS ${ARCH_NATIVE} CACHE INTERNAL "")
    if (OS_FREEBSD OR ARCH_I386)
        set (WITH_OPTIM 0 CACHE INTERNAL "") # Bug in assembler
    endif ()
    if (ARCH_AARCH64)
        set(WITH_NEON 1 CACHE INTERNAL "")
        set(WITH_ACLE 1 CACHE INTERNAL "")
    endif ()

    add_subdirectory (${INTERNAL_ZLIB_NAME})
    # todo: make pull to Dead2/zlib-ng and remove:
    # We should use same defines when including zlib.h as used when zlib compiled
    target_compile_definitions (zlib PUBLIC ZLIB_COMPAT WITH_GZFILEOP)
    target_compile_definitions (zlibstatic PUBLIC ZLIB_COMPAT WITH_GZFILEOP)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64" OR CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64")
        target_compile_definitions (zlib PUBLIC X86_64 UNALIGNED_OK)
        target_compile_definitions (zlibstatic PUBLIC X86_64 UNALIGNED_OK)
    endif ()

    #set_target_properties(example PROPERTIES EXCLUDE_FROM_ALL 1)
    #if (TARGET example64)
    #    set_target_properties(example64 PROPERTIES EXCLUDE_FROM_ALL 1)
    #endif ()

    #set_target_properties(minigzip PROPERTIES EXCLUDE_FROM_ALL 1)
    #if (TARGET minigzip64)
    #    set_target_properties(minigzip64 PROPERTIES EXCLUDE_FROM_ALL 1)
    #endif ()
endif ()

#add_subdirectory (zlib-ng)
#add_subdirectory (poco)
