#include <kfs_unlink.h>

int kfs_unlink(const char* path) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = unlink(fpath);
    if (res == -1) {
        return -errno;
    }
    return 0;
}


