#include "kfs_unlink.h"

int kfs_unlink(const char *path) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("kfs_unlink path : %s\n", fpath);
    int res = unlink(fpath);
    log_debugf("kfs_unlink execute result : %d\n", res);
    if (res == -1) {
        log_errorf("Error kfs_unlink : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_unlink(path);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;
}

