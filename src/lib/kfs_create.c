#include "kfs_create.h"

int kfs_create(const char* original_path, mode_t mode) {
    char *path = local_disk_cache_path(original_path);
    int fd = open(path, O_CREAT|O_EXCL, mode);
    if (fd == -1)
        return -errno;
    return 0;
}
