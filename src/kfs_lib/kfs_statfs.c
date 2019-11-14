#include "kfs_statfs.h"

int kfs_statfs(const char *path, struct statvfs *stbuf) {
    char fpath[PATH_MAX] = {0};
    fullpath(fpath, path);
    log_debugf("kfs_statfs path: %s\n", fpath);
    int res = statvfs(fpath, stbuf);
    log_debugf("kfs_statfs execute result : %d\n", res);
    if (res == -1) {
        log_errorf("kfs_statfs execute result : %s\n", strerror( errno ));
        return -errno;
    }
    return 0;
}