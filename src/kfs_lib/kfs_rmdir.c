#include "kfs_rmdir.h"

int kfs_rmdir(const char *path) {
    log_debugf("kfs_rmdir start  %s\n", path);
    char fpath[PATH_MAX_EXTENDED] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_rmdir fullpath : %s\n", fpath);
    set_current_user();
    fuse_context_log();
    int res = rmdir(fpath);
    set_default_user();
    if(res == -1) {
        log_errorf("Error kfs_rmdir : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_sync) {
        xglfs_set_current_user();
        int ret = xglfs_rmdir(path);
        set_default_user();
        if (ret == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_rmdir exit result : %d\n", res);
    return 0;
}

