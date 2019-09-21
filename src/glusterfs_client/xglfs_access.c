#include "xglfs_access.h"

int xglfs_access(const char* _path, int _mask) {
    int ret = glfs_access(XGLFS_STATE->fs, _path, _mask);
    if (unlikely(ret < 0)) {
        ret = -errno;
    }
    return ret;
}
