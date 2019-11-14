#include "kfs_release.h"

int kfs_release(const char *path, struct fuse_file_info *fi) {
    log_debugf("kfs_release start  %s\n", path);
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    log_debugf("    kfs_release fullpath : %s\n", fpath);
    log_debugf("    kfs_release fd : %lu\n", fi->fh);
    set_current_user();
    fuse_context_log();
    int fd = close(fi->fh);
    set_default_user();
    if (fd == -1) {
        log_errorf("Error kfs_release : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int g_fd = xglfs_release(path, fi);
        if (g_fd == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_release exit result : %d\n", fd);
    return 0;
}