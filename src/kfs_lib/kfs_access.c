#include "kfs_access.h"

int kfs_access(const char *path, int mask) {
    log_debugf("kfs_access start %s\n", path);
    fuse_context_log();
    char fpath[PATH_MAX_EXTENDED] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_access fullpath %s\n", fpath);
    set_current_user();
    fuse_context_log();
    int res = access(fpath, mask);
    set_default_user();
    if (res == -1) {
        log_errorf("Error kfs_access : %s\n", strerror( errno ));
        return -errno;
    }
    log_debugf("kfs_access exit result : %d\n", res);
    return 0;
}