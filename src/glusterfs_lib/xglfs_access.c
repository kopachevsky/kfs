#include "xglfs_access.h"

int xglfs_access(const char *path, int mask) {
    int res = glfs_access(XGLFS_STATE->fs, path, mask);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
