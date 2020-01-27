#include "kfs_create.h"

int kfs_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    log_debugf("kfs_create start  %s\n", path);
    char fpath[PATH_MAX_EXTENDED] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_create fullpath : %s\n", fpath);
    set_current_user();
    fuse_context_log();
    int fd = open(fpath,  O_CREAT|O_WRONLY|O_TRUNC, mode);
    set_default_user();
    if (fd == -1) {
        log_errorf("Error kfs_create : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_sync) {
//        xglfs_set_current_user();
        int g_fd = xglfs_create(path, mode, fi);
//        set_default_user();
        printf("xglfs_create execute result : %d\n", g_fd);
        if (g_fd == -1) {
            return -errno;
        }
    }
    fi->fh = fd;
    log_debugf("kfs_create exit result : %lu\n", fi->fh);
    return 0;
}
