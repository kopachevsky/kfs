#include <kfs_mkdir.h>

int kfs_mkdir(const char* original_path, const mode_t mode) {
    char *path = local_disk_cache_path(original_path);
    int res = mkdir(path, mode);
    if (res == -1) {
        return -errno;
    }
    return 0;
}