#include "xglfs_chmod.h"

int xglfs_chmod(const char* _path, mode_t _mode) {
    int ret = 0;

    ret = glfs_chmod(XGLFS_STATE->fs, _path, _mode);
    if (unlikely(ret < 0))
        ret = -errno;

    return ret;
}
