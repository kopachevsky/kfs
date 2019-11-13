#include "kfs_unlink.h"

int kfs_unlink(const char *path) {
    log_info("kfs_unlink start");
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_unlink path : %s\n", fpath);
    set_current_user();
    int res = unlink(fpath);
    set_default_user();
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
    log_debugf("kfs_unlink exit result : %d\n", res);
    return 0;
}

