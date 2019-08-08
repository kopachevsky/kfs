#include <kfs_readlink.h>

int kfs_readlink(const char* original_path, char* buf, size_t size) {
    char *path = local_disk_cache_path(original_path);
    int res = readlink(path, buf, size-1);
    if (res == -1) {
        return -errno;
    }
    buf[res] = '\0';
    return 0;
}
