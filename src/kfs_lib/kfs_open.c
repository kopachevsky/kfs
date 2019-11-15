#include "kfs_open.h"

int kfs_open(const char *path, struct fuse_file_info *fi) {
    log_debugf("kfs_open start  %s\n", path);
    char fpath[PATH_MAX_EXTENDED] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_open fullpath : %s\n", fpath);
    set_current_user();
    fuse_context_log();
    int fd = open(fpath, fi->flags);
    set_default_user();
    if (fd == -1) {
        log_errorf("Error kfs_open : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int g_fd = xglfs_open(path, fi);
        printf("xglfs_open execute result : %d\n", g_fd);
            if (g_fd == -1) {
                return -errno;
            }
        }
    fi->fh = fd;
    log_debugf("kfs_open exit result : %lu\n", fi->fh);
    return 0;
}
