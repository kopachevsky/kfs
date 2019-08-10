#include <kfs_truncate.h>

int kfs_truncate(const char* original_path, off_t size) {
    char *path = local_disk_cache_path(original_path);
    int res = truncate(path, size);
    if (res == -1) {
        return -errno;
    }
    free(path);
    return 0;
}
