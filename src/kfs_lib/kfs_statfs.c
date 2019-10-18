#include "kfs_statfs.h"

int kfs_statfs(const char *path, struct statvfs *stbuf) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = statvfs(fpath, stbuf);
    printf("kfs_statfs execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    return 0;
}