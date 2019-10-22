#include "kfs_chmod.h"

int kfs_chmod(const char *path, mode_t mode) {
    char fpath[MAX];
    fullpath(fpath, path);
    int res = chmod(fpath, mode);
    printf("kfs_chmod execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_chmod(path, mode);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;
}
