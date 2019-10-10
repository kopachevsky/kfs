add_executable(kfs kfs.c)

find_package(Fuse)
add_subdirectory(lib)
add_subdirectory(glusterfs_lib)

# Fuse specific params
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=26")

target_link_libraries(kfs fuse_cache ${FUSE_LIBRARIES})
target_link_libraries(kfs glusterfs_lib ${FUSE_LIBRARIES})