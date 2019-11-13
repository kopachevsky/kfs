#include "kfs_truncate.h"

int kfs_truncate(const char *path, off_t size) {
    log_info("kfs_truncate start");
    int res = 0;
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_truncate path : %s\n", fpath);
    set_current_user();
    res = truncate(fpath, size);
    set_default_user();
    if (res == -1) {
        log_errorf("kfs_truncate execute result : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_truncate(path, size);
        if (ret == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_truncate exit result : %d\n", res);
    return res;
}
