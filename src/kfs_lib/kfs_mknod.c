#include "kfs_mknod.h"

int kfs_mknod(const char *path, mode_t mode, dev_t rdev) {
    log_debugf("kfs_mknod start  %s\n", path);
    char fpath[PATH_MAX_EXTENDED] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_mknod fullpath : %s\n", fpath);
    int res = 0;
    set_current_user();
    fuse_context_log();
    if (S_ISFIFO(mode)) {
        res = mkfifo(fpath, mode);
    } else {
        res = mknod(fpath, mode, rdev);
    }
    set_default_user();
    if (res == -1) {
        log_errorf("kfs_mknod execute result : %s\n", strerror( errno ));
        return - errno;
    }
    if (XGLFS_STATE->gluster_sync) {
        xglfs_set_current_user();
        int ret = xglfs_mknod(path, mode, rdev);
        set_default_user();
        if (ret == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_mknod exit result : %d\n", res);
    return 0;
}