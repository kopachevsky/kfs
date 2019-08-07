#include <kfs_access.h>

int kfs_access(const char* original_path, int mode) {
    char *path = local_disk_cache_path(original_path);
    int res = access(path, mode);
    if (res == -1) {
        return -errno;
    }
    return 0;
}