#include "kfs_mknod.h"

int kfs_mknod(const char* path, mode_t mode, dev_t rdev) {
    int res = 0;
    res = mknod(path, mode, rdev);
    if(res == -1)
        return -errno;
    return 0;
}