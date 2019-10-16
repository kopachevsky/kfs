#include "xglfs_link.h"

int xglfs_link(const char *source_path, const char *target_path) {
    int res = glfs_link(XGLFS_STATE->fs, source_path, target_path);
    printf("xglfs_link execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
