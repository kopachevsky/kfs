#include "kfs_truncate.h"

int kfs_truncate(const char *path, off_t size) {
    char fpath[MAX_PATH];
    fullpath(fpath, path);
    int res = truncate(fpath, size);
    printf("kfs_truncate execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_truncate(path, size);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;
}
