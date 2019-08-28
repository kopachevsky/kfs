#include <kfs_truncate.h>

int kfs_truncate(const char* path, off_t size) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = truncate(fpath, size);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
