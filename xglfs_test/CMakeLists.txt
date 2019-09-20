find_package(Check REQUIRED)

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

# Since Check uses Threads to paralelize the tests, it's mandatory
# add pthread as a dependency, alongside the Check libraries.
add_executable(
        xglfs_fuse
            xglfs_test_main.c
            xglfs_mkdir_test.c

)
target_include_directories(xglfs_fuse PUBLIC includes)

target_link_libraries(xglfs_fuse gluster_client ${CHECK_LIBRARIES} pthread)

add_test(NAME xglfs_fuse COMMAND xglfs_fuse WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
# Create testing target and redirect its output to `Testing` folder
set_tests_properties(xglfs_fuse PROPERTIES TIMEOUT 30)


# Fuse specific params
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=26")