#include "xglfs_getattr.h"

int xglfs_getattr(const char* _path, struct stat* _buffer) {
    int ret = glfs_lstat(XGLFS_STATE->fs, _path, _buffer);
    if (unlikely(ret < 0)) {
        ret = -errno;
    }
    return ret;
}

