#include "xglfs_rename.h"

int xglfs_rename(const char* _oldpath, const char* _newpath) {
    int res= glfs_rename(XGLFS_STATE->fs, _oldpath, _newpath);
    if (unlikely(res < 0)) {
        res = -errno;
    }
    return 0;
}