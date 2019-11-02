#include "kfs_mkdir.h"

int kfs_mkdir(const char *path, const mode_t mode) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("kfs_mkdir path : %s\n", fpath);
    set_current_user();
    int res = mkdir(fpath, mode);
    set_default_user();
    log_debugf("kfs_mkdir execute result : %d\n", res);
    if (res == -1) {
        log_errorf("Error kfs_mkdir : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_mkdir(path, mode);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;
}