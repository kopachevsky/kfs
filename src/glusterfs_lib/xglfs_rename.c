#include "xglfs_rename.h"

int xglfs_rename(const char *source_path, const char *target_path) {
    int res = glfs_rename(XGLFS_STATE->fs, source_path, target_path);
    printf("xglfs_rename execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    return 0;
}