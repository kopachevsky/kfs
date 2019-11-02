#include "kfs_readlink.h"

int kfs_readlink(const char *path, char *buf, size_t size) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = 0;
    log_debugf("kfs_readLINK path : %s\n", fpath);
    set_current_user();
    res = readlink(fpath, buf, size-1);
    set_default_user();
    log_debugf("kfs_readLINK execute result : %d\n", res);
    if (res == -1) {
        log_errorf("Error kfs_readLINK : %s\n", strerror( errno ));
        return -errno;
    }
    buf[res] = '\0';
    return res;
}
