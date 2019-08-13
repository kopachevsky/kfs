#include <kfs_mknod.h>

int kfs_mknod(const char* original_path, mode_t mode, dev_t rdev) {
    char *path = local_disk_cache_path(original_path);
    int res = S_ISFIFO(mode) ? mkfifo(path, mode) : mknod(path, mode, rdev);
    if (res == -1) {
        return - errno;
    }
    free(path);
    return 0;
}