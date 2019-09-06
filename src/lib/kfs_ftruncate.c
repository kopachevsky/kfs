#include "kfs_ftruncate.h"

int kfs_ftruncate(const char* path, off_t size, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    int res = ftruncate(fi->fh ,size);
    if (res == -1) {
        return -errno;
    }
    return 0;
}

