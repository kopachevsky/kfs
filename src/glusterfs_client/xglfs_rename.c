#include "xglfs_rename.h"

int xglfs_rename(const char* _oldpath, const char* _newpath) {
    int ret = glfs_rename(XGLFS_STATE->fs, _oldpath, _newpath);
    if (unlikely(ret < 0)) {
        ret = -errno;
    }
    return ret;
}

