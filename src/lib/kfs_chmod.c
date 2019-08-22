#include <kfs_chmod.h>

int kfs_chmod(const char *path, mode_t mode) {
    int res = chmod(path, mode);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
