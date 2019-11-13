#include "kfs_flush.h"

int kfs_flush(const char *path, struct fuse_file_info *fi) {
    log_debugf("kfs_flush start  %s\n", path);
    fuse_context_log();
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    log_debugf("    kfs_flush fullpath : %s\n", fpath);
    log_debugf("    kfs_flush fd : %lu\n", fi->fh);
    int res = close(dup(fi->fh));
    if (res == -1) {
        log_debugf("Error kfs_flush : %s\n", strerror( errno ));
        return -errno;
    }
    log_debugf("kfs_flush exit result : %d\n", res);
    return 0;
}