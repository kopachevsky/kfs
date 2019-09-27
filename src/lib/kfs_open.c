#include "kfs_open.h"

int kfs_open(const char* path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int fd = open(fpath, fi->flags);
    if (fd == -1) {
        return -errno;
    }
    fi ->fh = fd;
    if (XGLFS_STATE->gluster_api != GLFS_DEFAULT_GLUSTER_API) {
        fd = xglfs_open(path, fi);
        if (fd == -1) {
            return -errno;
        }
    }
    return 0;
}
