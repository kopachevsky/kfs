#include "xglfs_mkdir.h"

int xglfs_mkdir(const char* _path, mode_t _mode) {
    int res = glfs_mkdir(XGLFS_STATE->fs, _path, _mode);
    if (unlikely(res < 0)) {
        res = -errno;
    }
    return 0;
}
