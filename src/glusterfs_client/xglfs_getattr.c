#include "xglfs_getattr.h"

int xglfs_getattr(const char* _path, struct stat* _buffer) {
    int res = glfs_lstat(XGLFS_STATE->fs, _path, _buffer);
    if (unlikely(res < 0)) {
        res = -errno;
    }
    return 0;
}

