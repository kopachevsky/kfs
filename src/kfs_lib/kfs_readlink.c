#include "kfs_readlink.h"

int kfs_readlink(const char *path, char *buf, size_t size) {
    char fpath[MAX_PATH];
    fullpath(fpath, path);
    int res = readlink(fpath, buf, size-1);
    if (res == -1) {
        return -errno;
    }
    buf[res] = '\0';
    return 0;
}
