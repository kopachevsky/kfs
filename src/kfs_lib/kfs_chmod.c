#include "kfs_chmod.h"

int kfs_chmod(const char *path, mode_t mode) {
    int res = 0;
    char fpath[PATH_MAX] = {0};
    fullpath(fpath, path);
    log_debugf("kfs_chmod path : %s\n", fpath);
    res = chmod(fpath, mode);
    log_debugf("kfs_chmod execute result : %d\n", res);
    if (res == -1) {
        log_errorf("Error kfs_chmod : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_chmod(path, mode);
        if (ret == -1) {
            return -errno;
        }
    }
    return res;
}
