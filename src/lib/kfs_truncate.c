#include <kfs_truncate.h>

int kfs_truncate(const char* path, off_t size) {
    int res = truncate(path, size);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
