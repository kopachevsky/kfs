add_library(
    gluster_client
        xglfs_access.c
        xglfs_chmod.c
        xglfs_chown.c
        xglfs_create.c
        xglfs_destroy.c
        xglfs_fgetattr.c
        xglfs_getattr.c
        xglfs_getxattr.c
        xglfs_init.c
        xglfs_link.c
        xglfs_listxattr.c
        xglfs_lock.c
        xglfs_mkdir.c
        xglfs_mknod.c
        xglfs_open.c
        xglfs_opendir.c
        xglfs_readdir.c
        xglfs_readlink.c
        xglfs_release.c
        xglfs_releasedir.c
        xglfs_removexattr.c
        xglfs_rename.c
        xglfs_rmdir.c
        xglfs_setxattr.c
        xglfs_statfs.c
        xglfs_symlink.c
        xglfs_unlink.c
        xglfs_utimens.c
)

target_include_directories(gluster_client PUBLIC includes)

find_package(GlusterfsApi)
target_link_libraries(gluster_client
        pthread
        rt
        zlog
        ${GLUSTERFS-API_LIBRARIES}
        ${FUSE_LIBRARIES}
        ${GB_LD_EXTRA}
)

install(TARGETS gluster_client
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)
