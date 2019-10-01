#include "kfs_create.h"

int kfs_create(const char* path, mode_t mode, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int fd = open(fpath, fi->flags, mode);
    if (fd == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        fd = xglfs_create(path, mode, fi);
        if (fd == -1) {
            return -errno;
        }
    }
    fi->fh = fd;
    return 0;
}
