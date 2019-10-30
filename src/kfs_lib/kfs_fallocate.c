#include "kfs_fallocate.h"

int kfs_fallocate(const char *path, int mode, off_t offset, off_t length, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    if (mode) {
        return -EOPNOTSUPP;
    }
    int res = -posix_fallocate(fi->fh, offset, length);
    log_debugf("kfs_fallocate execute result : %d\n", res);
    if (res == -1) {
        log_errorf("Error kfs_fallocate : %s\n", strerror( errno ));
        return -errno;
    }
    return res;
}
