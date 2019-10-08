#include "xglfs_unlink.h"

int xglfs_unlink(const char* _path) {
    int res = glfs_unlink(XGLFS_STATE->fs, _path);
    if (res == -1) {
        return  -errno;
    }
    return 0;
}


