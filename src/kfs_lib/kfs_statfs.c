#include "kfs_statfs.h"

int kfs_statfs(const char *path, struct statvfs *stbuf) {
    log_debugf("kfs_statfs start  %s\n", path);
    fuse_context_log();
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_statfs fullpath: %s\n", fpath);
    int res = statvfs(fpath, stbuf);
    if (res == -1) {
        log_errorf("kfs_statfs execute result : %s\n", strerror( errno ));
        return -errno;
    }
    log_debugf("kfs_statfs exit result : %d\n", res);
    return 0;
}