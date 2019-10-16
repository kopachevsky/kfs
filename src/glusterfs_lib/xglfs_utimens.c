#include "xglfs_utimens.h"

int xglfs_utimens(const char* path, const struct timespec tv[2]) {
    int res = glfs_utimens(XGLFS_STATE->fs, path, tv);
    printf("xglfs_utimens execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    return 0;
}