#include "kfs_create.h"

int kfs_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    char fpath[MAX_PATH];
    fullpath(fpath, path);
    int fd = open(fpath, fi->flags, mode);
    printf("kfs_create execute result : %d\n", fd);
    if (fd == -1) {
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
    printf("kfs_create fd : %lu\n", fi->fh);
    return 0;
}
