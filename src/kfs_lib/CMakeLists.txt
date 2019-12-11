add_library(
   fuse_cache
        kfs_init.c
        kfs_access.c
        kfs_getattr.c
        kfs_fgetattr.c
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
        kfs_ftruncate.c
        kfs_readlink.c
        kfs_fsync.c
        kfs_common.c
        kfs_opendir.c
        kfs_releasedir.c
        kfs_chown.c
        kfs_destroy.c
        kfs_utimens.c
        kfs_statfs.c
        kfs_fallocate.c
        copy_remote_storage_content.c
)

target_include_directories(fuse_cache PUBLIC includes)

find_package(GlusterfsApi)
target_link_libraries(
        fuse_cache
        glusterfs_lib
        pthread
        rt
        zlog
        ${GLUSTERFS-API_LIBRARIES}
)

install(TARGETS fuse_cache
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)

