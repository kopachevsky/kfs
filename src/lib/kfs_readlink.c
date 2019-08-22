#include <kfs_readlink.h>

int kfs_readlink(const char* path, char* buf, size_t size) {
    int res = readlink(path, buf, size-1);
    if (res == -1) {
        return -errno;
    }
    buf[res] = '\0';
    return 0;
}
