#include "xglfs_rmdir.h"

int xglfs_rmdir(const char* _path) {
    int ret = glfs_rmdir(XGLFS_STATE->fs, _path);
    if (unlikely(ret < 0)) {
        ret = -errno;
    }
    return ret;
}

