add_library(
   fuse_cache
        kfs_access.c
        kfs_getattr.c
        kfs_mkdir.c
        kfs_mknod.c
        kfs_open.c
        kfs_read.c
        kfs_readdir.c
        kfs_release.c
        kfs_rename.c
        kfs_rmdir.c
        kfs_truncate.c
        kfs_unlink.c
        kfs_write.c
        kfs_create.c
        kfs_chmod.c
        kfs_link.c
        kfs_symlink.c
        kfs_flush.c
)

target_include_directories(fuse_cache PUBLIC includes)

find_package(GlusterfsApi)

target_link_libraries(fuse_cache
        pthread
        rt
        ${GLUSTERFS-API_LIBRARIES}
)

install(TARGETS fuse_cache
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)

