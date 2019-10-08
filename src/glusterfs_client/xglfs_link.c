#include "xglfs_link.h"

int xglfs_link(const char* _path1, const char* _path2) {
    int res = glfs_link(XGLFS_STATE->fs, _path1, _path2);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
