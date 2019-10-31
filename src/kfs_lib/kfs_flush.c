#include "kfs_flush.h"

int kfs_flush(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    int res = close(dup(fi->fh));
    log_debugf("kfs_flush execute result : %d\n", res);
    if (res == -1) {
        log_debugf("Error kfs_flush : %s\n", strerror( errno ));
        return -errno;
    }
    return 0;
}