#include "xglfs_rmdir.h"

int xglfs_rmdir(const char *path) {
    int res = glfs_rmdir(XGLFS_STATE->fs, path);
    printf("xglfs_rmdir execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    return 0;
}

