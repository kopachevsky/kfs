#include "kfs_create.h"

int kfs_create(const char* original_path, mode_t mode, struct fuse_file_info *fi) {
    char *path = local_disk_cache_path(original_path);
    int fd = open(path, fi->flags, mode);
    if (fd == -1)
        return -errno;
    fi->fh =fd;
    return 0;
}
