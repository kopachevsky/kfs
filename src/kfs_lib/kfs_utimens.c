#include "kfs_utimens.h"

int kfs_utimens(const char *path, const struct timespec tv[2], struct fuse_file_info *fi) {
    char fpath[PATH_MAX] = {0};
    fullpath(fpath, path);
    log_debugf("kfs_utimens path: %s\n", fpath);
    set_current_user();
    int res = utimensat(fi->fh, fpath, tv, AT_SYMLINK_NOFOLLOW);
    set_default_user();
    log_debugf("kfs_utimens execute result : %d\n", res);
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
    return 0;
}
