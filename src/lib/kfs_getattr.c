#include "kfs_getattr.h"

int kfs_getattr(const char *path, struct stat *stbuf) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = lstat(fpath, stbuf);
    if (res == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api != GLFS_DEFAULT_GLUSTER_API) {
        res = xglfs_getattr(path, stbuf);
        if (res == -1) {
            return -errno;
        }
    }
    return 0;
}
