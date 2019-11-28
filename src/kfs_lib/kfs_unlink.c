#include "kfs_unlink.h"

int kfs_unlink(const char *path) {
    log_debugf("kfs_unlink start  %s\n", path);
    char fpath[PATH_MAX_EXTENDED] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_unlink fullpath : %s\n", fpath);
    set_current_user();
    fuse_context_log();
    int res = unlink(fpath);
    set_default_user();
    if (res == -1) {
        log_errorf("Error kfs_unlink : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_sync) {
        int ret = xglfs_unlink(path);
        if (ret == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_unlink exit result : %d\n", res);
    return 0;
}

