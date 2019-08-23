#include <kfs_chmod.h>

int kfs_chmod(const char *path, mode_t mode) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = chmod(fpath, mode);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
