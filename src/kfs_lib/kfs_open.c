#include "kfs_open.h"

int kfs_open(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int fd = open(fpath, fi->flags);
    printf("kfs_open execute result : %d\n", fd);
    if (fd == -1) {
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
    printf("kfs_open fd : %lu\n", fi->fh);
    return 0;
}
