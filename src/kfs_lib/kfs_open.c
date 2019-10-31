#include "kfs_open.h"

int kfs_open(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("kfs_open path : %s\n", fpath);
    int fd = open(fpath, fi->flags);
    if (fd == -1) {
        log_errorf("Error kfs_open : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int g_fd = xglfs_open(path, fi);
        printf("xglfs_open execute result : %d\n", g_fd);
            if (g_fd == -1) {
                return -errno;
            }
        }
    fi->fh = fd;
    log_debugf("kfs_open fd : %lu\n", fi->fh);
    return 0;
}
