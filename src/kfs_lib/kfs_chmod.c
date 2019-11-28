#include "kfs_chmod.h"

int kfs_chmod(const char *path, mode_t mode) {
    log_debugf("kfs_chmod start %s\n", path);
    char fpath[PATH_MAX_EXTENDED] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_chmod fullpath : %s\n", fpath);
    set_current_user();
    fuse_context_log();
    int res = chmod(fpath, mode);
    set_default_user();
    if (res == -1) {
        log_errorf("Error kfs_chmod : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_sync) {
        int ret = xglfs_chmod(path, mode);
        if (ret == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_chmod exit result : %d\n", res);
    return 0;
}
