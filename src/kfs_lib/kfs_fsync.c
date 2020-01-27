#include "kfs_fsync.h"

int kfs_fsync(const char *path, int datasync, struct fuse_file_info *fi) {
    log_debugf("kfs_fsync start  %s\n", path);
    char fpath[PATH_MAX_EXTENDED] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_fsync fullpath : %s\n", fpath);
    log_debugf("    kfs_fsync fd : %lu\n", fi->fh);
    (void) fpath;
    int res;
    set_current_user();
    fuse_context_log();
    if (datasync != 0) {
        res = fdatasync(fi->fh);
    } else {
        res = fsync(fi->fh);
    }
    set_default_user();
    if (res == -1) {
        log_errorf("Error kfs_fsync : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_sync) {
        xglfs_set_current_user();
        int ret = xglfs_fsync(path, datasync, fi);
        set_default_user();
        if (ret == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_fsync exit result : %d\n", res);
    return 0;
}
