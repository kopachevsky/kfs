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
add_executable(kfs_fuse test_main.c kfs_access_test.c kfs_read_test.c)
target_link_libraries(kfs_fuse fuse_cache ${CHECK_LIBRARIES} pthread)

add_test(NAME kfs_fuse COMMAND kfs_fuse WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
# Create testing target and redirect its output to `Testing` folder
set_tests_properties(kfs_fuse PROPERTIES TIMEOUT 30)
