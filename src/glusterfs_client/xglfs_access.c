#include "xglfs_access.h"

int xglfs_access(const char* _path, int _mask) {
    int res = glfs_access(XGLFS_STATE->fs, _path, _mask);
    if (unlikely(res < 0)) {
        res = -errno;
    }
    return 0;
}
