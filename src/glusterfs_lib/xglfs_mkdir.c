#include "xglfs_mkdir.h"

int xglfs_mkdir(const char *path, mode_t mode) {
    int res = glfs_mkdir(XGLFS_STATE->fs, path, mode);
    printf("xglfs_mkdir execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
