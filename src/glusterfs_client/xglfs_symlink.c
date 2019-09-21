#include "xglfs_symlink.h"

int xglfs_symlink(const char* _path1, const char* _path2) {
    int ret = glfs_symlink(XGLFS_STATE->fs, _path1, _path2);
    if (unlikely(ret < 0)) {
        ret = -errno;
    }
    return ret;
}
