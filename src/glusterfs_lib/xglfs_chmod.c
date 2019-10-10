#include "xglfs_chmod.h"

int xglfs_chmod(const char *path, mode_t mode) {
    int res = glfs_chmod(XGLFS_STATE->fs, path, mode);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
