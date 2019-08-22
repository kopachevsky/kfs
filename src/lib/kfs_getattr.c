#include <kfs_getattr.h>

int kfs_getattr(const char *path, struct stat *stbuf) {
    int res = lstat(path, stbuf);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
