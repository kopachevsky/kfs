#include "xglfs_mkdir.h"

int xglfs_mkdir(const char* _path, mode_t _mode) {
    int ret = glfs_mkdir(XGLFS_STATE->fs, _path, _mode);
    if (unlikely(ret < 0)) {
        ret = -errno;
    }
    return ret;
}
