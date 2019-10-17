#include "xglfs_statfs.h"

int xglfs_statfs(const char *path, struct statvfs *buf) {
    int res = glfs_statvfs(XGLFS_STATE->fs, path, buf);
    printf("xglfs_statfs execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    return 0;
}