#include "kfs_rmdir.h"

int kfs_rmdir(const char* path) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = rmdir(fpath);
    if(res == -1) {
        return -errno;
    }
    return 0;
}

