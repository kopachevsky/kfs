#include "xglfs_rmdir.h"

int xglfs_rmdir(const char* _path) {
    int res = glfs_rmdir(XGLFS_STATE->fs, _path);
    if (res == -1) {
        return  -errno;
    }
    return 0;
}

