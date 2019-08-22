#include <kfs_access.h>

int kfs_access(const char* path, int mask) {
    int res = access(path, mask);
    if (res == -1) {
        return -errno;
    }
    return 0;
}