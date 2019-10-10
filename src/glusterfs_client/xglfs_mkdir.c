#include "xglfs_mkdir.h"

int xglfs_mkdir(const char *path, mode_t mode) {
    int res = glfs_mkdir(XGLFS_STATE->fs, path, mode);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
