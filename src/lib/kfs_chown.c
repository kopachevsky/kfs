#include "kfs_chown.h"

int kfs_chown(const char *path, uid_t uid, gid_t gid) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = lchown(fpath, uid, gid);
    if (res == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api != GLFS_DEFAULT_GLUSTER_API) {
        res = xglfs_chown(path, uid, gid);
        if (res == -1) {
            return -errno;
        }
    }
    return 0;
}
