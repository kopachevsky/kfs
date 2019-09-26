#include "kfs_rmdir.h"

int kfs_rmdir(const char* path) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = rmdir(fpath);
    if(res == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api != GLFS_DEFAULT_GLUSTER_API) {
        res = xglfs_rmdir(path);
        if (res == -1) {
            return -errno;
        }
    }
    return 0;
}

