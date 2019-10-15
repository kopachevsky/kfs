#include "kfs_access.h"

int kfs_access(const char *path, int mask) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = access(fpath, mask);
    printf("kfs_access execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    return 0;
}