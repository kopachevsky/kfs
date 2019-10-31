#include "kfs_mknod.h"

int kfs_mknod(const char *path, mode_t mode, dev_t rdev) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("kfs_mknod path : %s\n", fpath);
    int res = 0;
    if (S_ISFIFO(mode)) {
        res = mkfifo(fpath, mode);
    } else {
        res = mknod(fpath, mode, rdev);
    }
    log_debugf("kfs_mknod execute result : %d\n", res);
    if (res == -1) {
        log_errorf("kfs_mknod execute result : %s\n", strerror( errno ));
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