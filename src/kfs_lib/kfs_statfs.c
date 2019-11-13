#include "kfs_statfs.h"

int kfs_statfs(const char *path, struct statvfs *stbuf) {
    log_info("kfs_statfs start");
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_statfs path: %s\n", fpath);
    int res = statvfs(fpath, stbuf);
    if (res == -1) {
        log_errorf("kfs_statfs execute result : %s\n", strerror( errno ));
        return -errno;
    }
    log_debugf("kfs_statfs exit result : %d\n", res);
    return 0;
}