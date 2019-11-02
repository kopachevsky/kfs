#include "kfs_getattr.h"

int kfs_getattr(const char *path, struct stat *stbuf) {
    int res = 0;
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("kfs_getattr path: %s\n", fpath);
    set_current_user();
    res = lstat(fpath, stbuf);
    set_default_user();
    log_debugf("kfs_getattr execute result : %d\n", res);
    if (res == -1) {
        log_errorf("Error kfs_getattr : %s\n", strerror( errno ));
        return -errno;
    }
    return res;
}
