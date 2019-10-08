#include "kfs_create.h"

int kfs_create(const char* path, mode_t mode, struct fuse_file_info *fi) {
    logger("KFS_CREATE:");
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int fd = open(fpath, fi->flags, mode);
     if (fd == -1) {
        return -errno;
    }
    printf("kfs create local fd : %lu\n", fi->fh);
//    if (XGLFS_STATE->gluster_api) {
    int ret = xglfs_create(path, mode, fi);
        if (ret == -1) {
            return -errno;
        }
//    }
    fi->fh = fd;
    return ret;
}
