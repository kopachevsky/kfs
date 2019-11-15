#include "kfs_readlink.h"

int kfs_readlink(const char *path, char *buf, size_t size) {
    log_debugf("kfs_readlink start  %s\n", path);
    char fpath[MAX_PATH] = {0};
    fullpath(fpath, path);
    int res = 0;
    log_debugf("    kfs_readlink fullpath : %s\n", fpath);
    set_current_user();
    fuse_context_log();
    res = readlink(fpath, buf, size-1);
    set_default_user();
    if (res == -1) {
        log_errorf("Error kfs_readlink : %s\n", strerror( errno ));
        return -errno;
    }
    buf[res] = '\0';
    log_debugf("kfs_readlink exit result : %d\n", res);
    return res;
}
