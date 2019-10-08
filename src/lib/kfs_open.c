#include "kfs_open.h"

int kfs_open(const char* path, struct fuse_file_info *fi) {
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
            int g_fd = xglfs_open(path, fi);
            if (g_fd == -1) {
                return -errno;
            }
        }
        fi->fh = fd;
        printf("kfs_open local fd : %lu\n", fi->fh);
//        printf("xglfs_open fd : %lu\n", fi->fh_old);
    }
    return 0;
}
