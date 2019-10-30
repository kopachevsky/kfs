#include "kfs_create.h"

int kfs_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("kfs_create path : %s\n", fpath);
    int fd = open(fpath,  O_CREAT|O_WRONLY|O_TRUNC, mode);
    if (fd == -1) {
        log_errorf("Error kfs_create : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int g_fd = xglfs_create(path, mode, fi);
        printf("xglfs_create execute result : %d\n", g_fd);
        if (g_fd == -1) {
            return -errno;
        }
    }
    fi->fh = fd;
    log_debugf("kfs_create fd : %lu\n", fi->fh);
    return 0;
}
