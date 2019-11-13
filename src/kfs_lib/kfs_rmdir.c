#include "kfs_rmdir.h"

int kfs_rmdir(const char *path) {
    log_info("kfs_rmdir start");
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_rmdir path : %s\n", fpath);
    set_current_user();
    int res = rmdir(fpath);
    set_default_user();
    if(res == -1) {
        log_errorf("Error kfs_rmdir : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_rmdir(path);
        if (ret == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_rmdir exit result : %d\n", res);
    return 0;
}

