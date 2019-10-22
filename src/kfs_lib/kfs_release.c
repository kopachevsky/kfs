#include "kfs_release.h"

int kfs_release(const char *path, struct fuse_file_info *fi) {
    char fpath[MAX];
    fullpath(fpath, path);
    (void) fpath;
    printf("kfs_release fd : %lu\n", fi->fh);
    int fd = close(fi->fh);
    printf("kfs_release execute result : %d\n", fd);
    if (fd == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int g_fd = xglfs_release(path, fi);
        if (g_fd == -1) {
            return -errno;
        }
    }
    return 0;
}