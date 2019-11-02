#include "kfs_rmdir.h"

int kfs_rmdir(const char *path) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("kfs_rmdir path : %s\n", fpath);
    set_current_user();
    int res = rmdir(fpath);
    set_default_user();
    log_debugf("kfs_rmdir execute result : %d\n", res);
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
    return 0;
}

