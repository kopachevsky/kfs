#include "kfs_truncate.h"

int kfs_truncate(const char *path, off_t size) {
    log_debugf("kfs_truncate start  %s\n", path);
    int res = 0;
    char fpath[PATH_MAX_EXTENDED] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_truncate fullpath : %s\n", fpath);
    set_current_user();
    fuse_context_log();
    res = truncate(fpath, size);
    set_default_user();
    if (res == -1) {
        log_errorf("kfs_truncate execute result : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_sync) {
        xglfs_set_current_user();
        int ret = xglfs_truncate(path, size);
        set_default_user();
        if (ret == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_truncate exit result : %d\n", res);
    return res;
}
