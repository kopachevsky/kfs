#include "kfs_mkdir.h"

int kfs_mkdir(const char* path, const mode_t mode) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = mkdir(fpath, mode);
    printf("KFS_MKDIR execute result : %d  ", res);
    if (res == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_mkdir(path, mode);
        printf("XGLFS_MKDIR execute result : %d  ", ret);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;
}