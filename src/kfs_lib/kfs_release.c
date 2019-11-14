#include "kfs_release.h"

int kfs_release(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX] = {0};
    fullpath(fpath, path);
    (void) fpath;
    log_debugf("kfs_release path : %s\n", fpath);
    set_current_user();
    int fd = close(fi->fh);
    set_default_user();
    log_debugf("kfs_release execute result : %d\n", fd);
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
    return 0;
}