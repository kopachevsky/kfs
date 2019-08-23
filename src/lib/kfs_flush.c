#include "kfs_flush.h"

int kfs_flush(const char* path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    int res = close(fi->fh);
    if (res == -1) {
        return -errno;
    }
    return 0;
}