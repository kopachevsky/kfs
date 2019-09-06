#include "kfs_mkdir.h"

int kfs_mkdir(const char* path, const mode_t mode) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = mkdir(fpath, mode);
    if (res == -1) {
        return -errno;
    }
    return 0;
}