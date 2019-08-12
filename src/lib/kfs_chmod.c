#include <kfs_chmod.h>

int kfs_chmod(const char *original_path, mode_t mode) {
    char *path = local_disk_cache_path(original_path);
    int res = chmod(path, mode);
    if (res == -1) {
        return -errno;
    }
    free(path);
    return 0;
}
