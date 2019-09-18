#include "kfs_write.h"

int kfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    int res = pwrite(fi->fh, buf, size, offset);
    if (res == -1) {
        return -errno;
    }
    res = xglfs_write(path, buf, size, offset, fi);
    if (res == -1) {
        return -errno;
    }
    return res;
}
