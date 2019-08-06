#include <kfs_unlink.h>

int kfs_unlink(const char* original_path) {
    char *path = local_disk_cache_path(original_path);
    int res = unlink(path);
    if (res == -1) {
        return -errno;
    }
    return 0;
}


