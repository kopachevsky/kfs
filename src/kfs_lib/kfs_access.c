#include "kfs_access.h"

int kfs_access(const char *path, int mask) {
    log_info("kfs_access start");
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_access path %s\n", fpath);
    set_current_user();
    int res = access(fpath, mask);
    set_default_user();
    if (res == -1) {
        log_errorf("Error kfs_access : %s\n", strerror( errno ));
        return -errno;
    }
    log_debugf("kfs_access exit result : %d\n", res);
    return 0;
}