#include "kfs_unlink.h"

int kfs_unlink(const char *path) {
    char fpath[MAX_PATH];
    fullpath(fpath, path);
    int res = unlink(fpath);
    printf("kfs_release execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_unlink(path);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;
}

