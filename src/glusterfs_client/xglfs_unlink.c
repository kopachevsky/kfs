#include "xglfs_unlink.h"

int xglfs_unlink(const char* _path) {
    int ret = glfs_unlink(XGLFS_STATE->fs, _path);
    if (unlikely(ret < 0)) {
        ret = -errno;
    }
    return ret;
}


