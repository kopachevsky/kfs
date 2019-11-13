#include "kfs_fallocate.h"

int kfs_fallocate(const char *path, int mode, off_t offset, off_t length, struct fuse_file_info *fi) {
    log_info("kfs_fallocate start");
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_fallocate path : %s\n", fpath);
    (void) fpath;
    if (mode) {
        return -EOPNOTSUPP;
    }
    log_debugf("    kfs_fallocate fd : %lu\n", fi->fh);
    int res = -posix_fallocate(fi->fh, offset, length);
    if (res == -1) {
        log_errorf("Error kfs_fallocate : %s\n", strerror( errno ));
        return -errno;
    }
    log_debugf("kfs_fallocate exit result : %d\n", res);
    return res;
}
