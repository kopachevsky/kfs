#include "kfs_getattr.h"

int kfs_getattr(const char *path, struct stat *stbuf) {
    char fpath[MAX];
    fullpath(fpath, path);
    int res = lstat(fpath, stbuf);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
