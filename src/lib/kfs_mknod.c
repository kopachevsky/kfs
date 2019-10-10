#include "kfs_mknod.h"

int kfs_mknod(const char *path, mode_t mode, dev_t rdev) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = S_ISFIFO(mode) ? mkfifo(fpath, mode) : mknod(fpath, mode, rdev);
    if (res == -1) {
        return - errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_mknod(path, mode, rdev);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;
}