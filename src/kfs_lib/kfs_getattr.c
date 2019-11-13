#include "kfs_getattr.h"

int kfs_getattr(const char *path, struct stat *stbuf) {
    log_info("kfs_getattr start");
    int res = 0;
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_getattr path: %s\n", fpath);
    set_current_user();
    res = lstat(fpath, stbuf);
    set_default_user();
    if (res == -1) {
        log_errorf("Error kfs_getattr : %s\n", strerror( errno ));
        return -errno;
    }
    log_debugf("kfs_getattr exit result : %d\n", res);
    return res;
}
