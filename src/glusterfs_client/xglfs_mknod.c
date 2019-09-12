#include "xglfs_mknod.h"

int xglfs_mknod(const char* _path, mode_t _mode, dev_t _dev) {
    int ret = glfs_mknod(XGLFS_STATE->fs, _path, _mode, _dev);
    if (unlikely(ret < 0)) {
        ret = -errno;
    }
    return ret;
}

