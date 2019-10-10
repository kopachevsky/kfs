#include "xglfs_mknod.h"

int xglfs_mknod(const char *path, mode_t mode, dev_t rdev) {
    int res = glfs_mknod(XGLFS_STATE->fs, path, mode, rdev);
    if (res == -1) {
        return -errno;
    }
    return 0;
}

