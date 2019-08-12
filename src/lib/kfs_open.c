#include <kfs_open.h>

int kfs_open(const char* original_path, struct fuse_file_info *fi) {
    char *path = local_disk_cache_path(original_path);
    int fd = open(path, fi->flags);
    if (fd == -1) {
        return -errno;
    }
    fi ->fh = fd;
    free(path);
    return 0;
}
