#include <kfs_write.h>

int kfs_write(const char *original_path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    int res = pwrite(fi->fh, buf, size, offset);
    if (res == -1)
        return -errno;
    return res;
}
