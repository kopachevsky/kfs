cmake_minimum_required(VERSION 3.10.2)

project(KFS C)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("This is DEBUG build")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

include(FindPkgConfig)
if (PKG_CONFIG_FOUND)
    pkg_check_modules(GLUSTERFS-API glusterfs-api)
    if(NOT GLUSTERFS-API_FOUND EQUAL 1)
        message(SEND_ERROR "pkg-config for glusterfs-api is missing.")
    endif(NOT GLUSTERFS-API_FOUND EQUAL 1)
    pkg_check_modules(FUSE fuse)
    if(NOT FUSE_FOUND EQUAL 1)
        message(SEND_ERROR "pkg-config for fuse is missing.")
    endif(NOT FUSE_FOUND EQUAL 1)
    if(NOT CMAKE_BUILD_TYPE MATCHES Debug)
        pkg_check_modules(LIBTCMALLOC_MINIMAL libtcmalloc_minimal)
        if(LIBTCMALLOC_MINIMAL_FOUND EQUAL 1)
            set(GB_LD_EXTRA "${LIBTCMALLOC_MINIMAL_LIBRARIES}")
        endif (LIBTCMALLOC_MINIMAL_FOUND EQUAL 1)
    endif(NOT CMAKE_BUILD_TYPE MATCHES Debug)
endif (PKG_CONFIG_FOUND)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS
        "-std=c99 -D_DEFAULT_SOURCE -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=26 -W -Wall -Wextra -pedantic -Wwrite-strings -Winit-self -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-declarations -Wmissing-include-dirs -Wno-unused-parameter -Wuninitialized -Wold-style-definition -Wstrict-prototypes -Wmissing-prototypes")

set(CMAKE_C_FLAGS_DEBUG "-O0 -g -ggdb -DMODE_DEBUG")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -w3 -wd2552 -wd981")
endif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")

set(CMAKE_C_FLAGS_RELEASE "-O3 -march=native -DMODE_NORMAL")
add_executable(KFS
        kfs.c
        kfs_getattr.c
        kfs_access.c
        kfs_open.c
        kfs_read.c
        kfs_write.c
        kfs_truncate.c
        kfs_release.c)

target_link_libraries(KFS
        pthread
        rt
        ${GLUSTERFS-API_LIBRARIES}
        ${FUSE_LIBRARIES}
        ${GB_LD_EXTRA})

set_target_properties(KFS
        PROPERTIES
        COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64")