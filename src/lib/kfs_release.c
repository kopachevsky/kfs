#include "kfs_release.h"

int kfs_release(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    printf("kfs_release local fd : %lu\n", fi->fh);
    int fd = close(fi->fh);
    if (fd == -1) {
        return -errno;
    }
    int tmp = fi->fh;
    fi->fh = fi->fh_old;
    if (XGLFS_STATE->gluster_api) {
        int g_fd = xglfs_release(path, fi);
        if (g_fd == -1) {
            return -errno;
        }
    }
    fi->fh = tmp;
    return 0;
}