#include "kfs_utimens.h"

int kfs_utimens(const char *path, const struct timespec tv[2], struct fuse_file_info *fi) {
    log_debugf("kfs_utimens start  %s\n", path);
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_utimens fullpath: %s\n", fpath);
    set_current_user();
    fuse_context_log();
    int res = utimensat(fi->fh, fpath, tv, AT_SYMLINK_NOFOLLOW);
    set_default_user();
    if (res == -1) {
        log_errorf("Error kfs_utimens : %s", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_utimens(path, tv);
        if (ret == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_utimens exit result : %d\n", res);
    return 0;
}
