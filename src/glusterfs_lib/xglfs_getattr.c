#include "xglfs_getattr.h"

int xglfs_getattr(const char *path, struct stat *stbuf) {
    int res = glfs_lstat(XGLFS_STATE->fs, path, stbuf);
    if (res == -1) {
        return -errno;
    }
    return 0;
}

