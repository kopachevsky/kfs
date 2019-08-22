#include "kfs_read.h"

int kfs_read(const char* path, char* buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    (void) path;
    int res = pread(fi->fh, buf, size, offset);
    if (res == -1) {
        return -errno;
    }
    return res;
}