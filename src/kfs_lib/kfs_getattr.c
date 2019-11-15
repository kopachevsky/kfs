#include "kfs_getattr.h"

int kfs_getattr(const char *path, struct stat *stbuf) {
    log_debugf("kfs_getattr start  %s\n", path);
    int res = 0;
    char fpath[MAX_PATH] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_getattr fullpath: %s\n", fpath);
    set_current_user();
    fuse_context_log();
    res = lstat(fpath, stbuf);
    set_default_user();
    if (res == -1) {
        log_errorf("Error kfs_getattr : %s\n", strerror( errno ));
        return -errno;
    }
    log_debugf("kfs_getattr exit result : %d\n", res);
    return res;
}
