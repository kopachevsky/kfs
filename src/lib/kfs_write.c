#include <kfs_write.h>

int kfs_write(const char *original_path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    char *path = local_disk_cache_path(original_path);
    (void) path;
    int res = pwrite(fi->fh, buf, size, offset);
    if (res == -1) {
        return -errno;
    }
    free(path);
    return res;
}
