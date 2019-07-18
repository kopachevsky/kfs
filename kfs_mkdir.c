#include "kfs_mkdir.h"

int kfs_mkdir(const char* path, mode_t mode) {
    int res = mkdir(path, mode);
    if (res == -1)
        return -errno;
    return 0;
}