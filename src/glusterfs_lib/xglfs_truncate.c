#include "xglfs_truncate.h"

int xglfs_truncate(const char *path, off_t size) {
    int res = glfs_truncate(XGLFS_STATE->fs, path, size);
    if (res == -1) {
        return -errno;
    }
    return 0;
}

