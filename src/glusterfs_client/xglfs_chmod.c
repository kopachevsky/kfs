#include "xglfs_chmod.h"

int xglfs_chmod(const char* _path, mode_t _mode) {
    int res = glfs_chmod(XGLFS_STATE->fs, _path, _mode);
    if (unlikely(res < 0)) {
        res = -errno;
    }
    return res;
}
