#include <kfs_open.h>

int kfs_open(const char* original_path, mode_t mode) {
    char *path = local_disk_cache_path(original_path);
    int fd = open(path, O_WRONLY|O_RDONLY|O_TRUNC, mode);
    if (fd == -1)
        return -errno;
    return 0;
}
