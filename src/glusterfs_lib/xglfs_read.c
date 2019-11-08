#include "xglfs_read.h"

int xglfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    (void) path;
    int res = glfs_pread(FH_TO_FD(XGLFS_STATE->g_fh), buf, size, offset, fi->flags);
    if (res == -1) {
        return  -errno;
    }
    return res;
}

