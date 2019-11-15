#include "kfs_mkdir.h"

int kfs_mkdir(const char *path, const mode_t mode) {
    log_debugf("kfs_mkdir start  %s\n", path);
    char fpath[MAX_PATH] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_mkdir fullpath : %s\n", fpath);
    set_current_user();
    fuse_context_log();
    int res = mkdir(fpath, mode);
    set_default_user();
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
    log_debugf("kfs_mkdir exit result : %d\n", res);
    return 0;
}