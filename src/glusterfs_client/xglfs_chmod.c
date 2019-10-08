#include "xglfs_chmod.h"

int xglfs_chmod(const char* _path, mode_t _mode) {
    int res = glfs_chmod(XGLFS_STATE->fs, _path, _mode);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
