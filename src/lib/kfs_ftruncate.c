#include <kfs_ftruncate.h>

int kfs_ftruncate(const char* original_path, off_t size, struct fuse_file_info *fi) {
    char *path = local_disk_cache_path(original_path);
    (void) path;
    int res = ftruncate(fi->fh ,size);
    if (res == -1) {
        return -errno;
    }
    free(path);
    return 0;
}

