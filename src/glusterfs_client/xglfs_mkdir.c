#include "xglfs_mkdir.h"

int xglfs_mkdir(const char* _path, mode_t _mode) {
    int ret = glfs_mkdir(XGLFS_STATE->fs, _path, _mode);
    if (ret == -1) {
        return -errno;
    }
    return 0;
}
