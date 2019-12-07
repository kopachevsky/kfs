#include "kfs_chown.h"

int kfs_chown(const char *path, uid_t uid, gid_t gid) {
    log_debugf("kfs_chown start %s\n", path);
    char fpath[PATH_MAX_EXTENDED] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_chown fullpath : %s\n", fpath);
    set_current_user();
    fuse_context_log();
    int res = lchown(fpath, uid, gid);
    set_default_user();
    if (res == -1) {
        log_errorf("Error kfs_chown %s", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_sync) {
        int ret = xglfs_chown(path, uid, gid);
        if (ret == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_chown exit result : %d\n", res);
    return 0;
}
