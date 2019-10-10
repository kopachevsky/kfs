#include "kfs_open.h"

int kfs_open(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    if (fi->flags == O_CREAT) {
        int res = kfs_create(path, 0, fi);
        if (res == -1) {
            return -errno;
        }
    } else {
        int fd = open(fpath, fi->flags);
        if (fd == -1) {
            return -errno;
        }
        if (XGLFS_STATE->gluster_api) {
            int ret = xglfs_open(path, fi);
            if (ret == -1) {
                return -errno;
            }
        }
        fi->fh = fd;
        printf("kfs_open local fd : %lu\n", fi->fh);
    }
    return 0;
}
