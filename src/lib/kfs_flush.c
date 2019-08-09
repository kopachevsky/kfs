#include "kfs_flush.h"

int kfs_flush(const char* original_path, struct fuse_file_info *fi) {
    char *path = local_disk_cache_path(original_path);
    (void) path;
    int res = close(fi->fh);
    if (res == -1)
        return -errno;
    return 0;
}