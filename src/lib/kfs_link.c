#include "kfs_link.h"

int kfs_link(const char* first_path, const char* second_path) {
    char *path1 = local_disk_cache_path(first_path);
    char *path2 = local_disk_cache_path(second_path);
    int fd = link(path1, path2);
    if (fd ==-1)
        return -errno;
    return 0;
}