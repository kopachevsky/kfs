#include "kfs_create.h"

int kfs_create(const char* path, mode_t mode, struct fuse_file_info *fi) {
    logger("KFS_CREATE:");
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int fd = open(fpath, fi->flags, mode);
     if (fd == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int g_fd = xglfs_create(path, mode, fi);
        if (g_fd == -1) {
            return -errno;
        }
    }
//    fi->fh_old = fi->fh;
    fi->fh = fd;
    printf("kfs create local fd : %lu\n", fi->fh);
//    printf("gluster create fd : %lu\n", fi->fh_old);

    return 0;
}
