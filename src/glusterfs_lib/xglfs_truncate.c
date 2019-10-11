#include "xglfs_truncate.h"

int xglfs_truncate(const char *path, off_t size) {
    int res = glfs_truncate(XGLFS_STATE->fs, path, size);
    printf("xglfs_truncate execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    return 0;
}

