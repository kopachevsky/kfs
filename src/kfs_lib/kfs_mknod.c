#include "kfs_mknod.h"

int kfs_mknod(const char *path, mode_t mode, dev_t rdev) {
    char fpath[MAX];
    fullpath(fpath, path);
    int res = 0;
    if (S_ISFIFO(mode)) {
        res = mkfifo(fpath, mode);
    } else {
        res = mknod(fpath, mode, rdev);
        printf("kfs_mknod execute result : %d\n", res);
    }
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