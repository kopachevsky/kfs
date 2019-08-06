#include "kfs_flush.h"

int kfs_flush(const char* path, struct fuse_file_info *fi) {
    int res = close(fi->fh);
    if (res == -1)
        return -errno;
    return 0;
}